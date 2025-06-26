#include "render_system.hpp"
#include "component_registry.hpp"
#include "sprite_component.hpp"
#include "transform_component.hpp"

// GLM includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// System includes
#include <iostream>

//-----
ZameEngine::RenderSystem::RenderSystem(std::unique_ptr<Window> window, std::unique_ptr<ShaderProgram> program)
    : mWindow(std::move(window)), mShaderProgram(std::move(program)), VAO(), VBO(), EBO()
{
    float vertices[] = {
        // positions        // colors         // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

//-----
ZameEngine::RenderSystem::~RenderSystem()
{
}

//-----
void ZameEngine::RenderSystem::render(std::vector<ZameEngine::Entity> &entities)
{
    mWindow->startDraw();
    mShaderProgram->use();

    glBindVertexArray(VAO);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), mWindow->getWindowRatio(), 0.1f, 100.0f);

    for (Entity &entity : entities)
    {
        TransformComponent *transform = ComponentRegistry<TransformComponent>::get(entity);
        SpriteComponent *sprite = ComponentRegistry<SpriteComponent>::get(entity);

        if (transform != nullptr && sprite != nullptr)
        {
            // std::cout << "Drawing entity: " << entity.getId() << std::endl;

            glm::mat4 model = glm::translate(glm::mat4(1.0f), transform->position);
            model = projection * view * model;
            mShaderProgram->setMat4("model", model);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sprite->textureId);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }

    mWindow->endDraw();
}

//-----
unsigned int ZameEngine::RenderSystem::loadTexture(const std::string &texturePath)
{
    Texture texture = Texture(texturePath.c_str());
    unsigned int id = texture.ID;

    mTextures.insert({texture.ID, std::move(texture)});

    return id;
}
