#include "Item.hpp"

int Item::_count = 0;

Item::Item(const Configuration::Textures& idTexture)
{
    _sprite.setTexture(Configuration::textures.get(idTexture));
    _id = _count;
    ++_count;
}

Item::Item(const Configuration::Textures& idTexture, const sf::IntRect& rect) 
    : Item(idTexture)
{
    _sprite.setTextureRect(rect);
}

Item::Item(const Item& other)
{
    _sprite = other._sprite;
    _id = other._id;
    ++_count;
}

Item::Item(Item&& other) noexcept
{
    _sprite = other._sprite;

    _id = other._id;
    ++_count;
}

Item& Item::operator=(const Item& other)
{
    if (this != &other) {
        _sprite = other._sprite;
        _id = other._id;
        ++_count;
    }

    return *this;
}

Item::~Item()
{
    --_count;
}

sf::Sprite& Item::getSprite()
{
    return _sprite;
}

int Item::getId()
{
    return _id;
}

void Item::render(sf::RenderTarget* target)
{
    target->draw(_sprite);
}
