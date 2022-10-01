#include "Button.h"
#include <iostream>

Button::~Button()
{
}

//empty constructor made so i could use vector to load all buttons but game crashes if vector used
Button::Button() {

}

Button::Button(std::string texturePath, std::string fontPath, std::string text, unsigned int textSize, sf::Vector2f textOffSet, sf::Vector2f buttonSize, sf::Vector2f buttonPosition, sf::Vector2u spriteCount, float spriteCurrentTime)	
{
	sf::Image buttonSpriteSheet;
	buttonSpriteSheet.loadFromFile(texturePath);
	buttonSpriteSheet.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(buttonSpriteSheet);

	animation = Animation(&texture, spriteCount, spriteCurrentTime);


	font.loadFromFile(fontPath);
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(textSize);
	this->text.setOrigin(body.getSize() / 2.0f);
	this->text.setPosition(buttonPosition.x - textOffSet.x, buttonPosition.y - textOffSet.y);
	this->text.setFillColor(sf::Color(255, 255, 255));

	body.setSize(buttonSize);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(&texture);
	body.setPosition(buttonPosition);	
}

void Button::Update(float deltaTime, sf::Vector2i mousePosition, float& gamemode, float destination)
{
	int spriteRow = 0;

	if ((mousePosition.x > (body.getPosition().x - body.getSize().x / 2.0f) && mousePosition.x < (body.getPosition().x + body.getSize().x / 2.0f)) && ((mousePosition.y > body.getPosition().y - body.getSize().y / 2.0f) && mousePosition.y < (body.getPosition().y + body.getSize().y / 2.0f))) {
		spriteRow = 1;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			gamemode = destination;
		}
	}


	animation.Update(spriteRow, deltaTime, true);
	body.setTextureRect(animation.textureRect);
}

void Button::Draw(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(body);
	gameWindow.draw(text);
}

sf::Vector2f Button::GetPosition()
{
	return body.getPosition();
}
