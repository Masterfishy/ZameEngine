#include "entity.hpp"

//-----
ZameEngine::Entity::Entity(std::size_t id) : mId(id)
{
}

//-----
ZameEngine::Entity::~Entity()
{
}

//-----
std::size_t ZameEngine::Entity::getId() const
{
    return mId;
}
