#pragma once

#include "Object.hpp"
#include "../Helpers/AnimationHelper.hpp"

class Entity :
    public Object
{
public:
    Entity();
    virtual ~Entity();

    Entity(const float x, const float y, sf::Texture& texture);
    Entity(const Entity& other);
    Entity(Entity&& other) noexcept;
    Entity& operator=(const Entity& other);

    void createAnimationComponent(sf::Sprite* sprite, sf::Texture& textureSheet);

    virtual void update();
    virtual void render(sf::RenderTarget* target) override;

protected:
    AnimationHelper* _animationComponent;
};

