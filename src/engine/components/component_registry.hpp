#pragma once

#include "entity.hpp"

#include <iostream>      // std::cout, std::endl
#include <memory>        // std::unique_ptr
#include <mutex>         // std::unique_lock
#include <shared_mutex>  // std::shared_lock, std::shared_mutex
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace ZameEngine
{
const unsigned int MAX_ENTITIES = 32;

template <typename TComponent> class ComponentRegistry
{
  public:
    ComponentRegistry(const ComponentRegistry &other) = delete;
    void operator=(const ComponentRegistry &other) = delete;

    static ComponentRegistry &instance()
    {
        static ComponentRegistry registry;

        // std::cout << "Access registry: " << &registry << std::endl;

        return registry;
    }

    static bool add(const Entity &entity)
    {
        // std::cout << "Add component of type: " << typeid(TComponent).name() << " to entity: " << entity.getId()
        //           << std::endl;

        return instance().addImplementation(entity);
    }

    static bool add(const Entity &entity, TComponent &&component)
    {
        return instance().addImplementation(entity, std::forward<TComponent>(component));
    }

    static bool add(const Entity &entity, const TComponent &component)
    {
        return instance().addImplementation(entity, component);
    }

    static TComponent *get(const Entity &entity)
    {
        // std::cout << "Get component of type: " << typeid(TComponent).name() << " from entity: " << entity.getId()
        //           << std::endl;

        return instance().getImplementation(entity);
    }

  private:
    ComponentRegistry() : mCount(0), mComponents(), mEntityIdToComponentIndex()
    {
    }

    bool addImplementation(const Entity &entity)
    {
        if (mEntityIdToComponentIndex.find(entity.getId()) != mEntityIdToComponentIndex.end())
        {
            return false;
        }

        if (mCount >= MAX_ENTITIES)
        {
            return false;
        }

        mEntityIdToComponentIndex.emplace(entity.getId(), mCount);
        mComponents[mCount] = TComponent{};
        mCount++;

        return true;
    }

    template <typename TComponentArg> bool addImplementation(const Entity &entity, TComponentArg &&component)
    {

        if (mEntityIdToComponentIndex.find(entity.getId()) != mEntityIdToComponentIndex.end())
        {
            return false;
        }

        if (mCount >= MAX_ENTITIES)
        {
            return false;
        }

        mEntityIdToComponentIndex.emplace(entity.getId(), mCount);
        mComponents[mCount] = std::forward<TComponentArg>(component);
        mCount++;

        return true;
    }

    TComponent *getImplementation(const Entity &entity) const
    {

        auto componentIter = mEntityIdToComponentIndex.find(entity.getId());
        if (componentIter == mEntityIdToComponentIndex.end())
        {
            return nullptr;
        }

        unsigned int index = componentIter->second;
        if (index >= mCount)
        {
            return nullptr;
        }

        return &mComponents.at(index);
    }

    unsigned int mCount;
    mutable std::array<TComponent, MAX_ENTITIES> mComponents;
    std::unordered_map<std::size_t, unsigned int> mEntityIdToComponentIndex;
};
} // namespace ZameEngine
