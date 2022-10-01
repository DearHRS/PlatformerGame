#include "Platform.h"
#include <iostream>

Platform::Platform(std::string texturePath, sf::Vector2f size, sf::Vector2f position)
{
    texture.loadFromFile(texturePath);
    body.setTexture(&texture);
    body.setSize(size);    
    body.setPosition(position);
    body.setOrigin(size/2.0f);
}

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setTexture(texture);
    body.setSize(size);
    body.setPosition(position);
    body.setOrigin(size / 2.0f);
}

Platform::Platform()
{
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow& gameWindow)
{
    gameWindow.draw(body);
}

Collision Platform::GetCollision()
{
    return Collision(body);
}
