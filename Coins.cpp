#include "Coins.h"

Coins::Coins()
{
}

Coins::Coins(float value, unsigned int valueSize, sf::Vector2f offSet, std::string fontPath, sf::Vector2f position, sf::Vector2f hitBoxSize, std::string texturePath, sf::Vector2u spriteCount, float spriteLifeTime)
{
	this->value = value;

	textureImage.loadFromFile(texturePath);
	textureImage.createMaskFromColor(sf::Color(255, 174, 201));
	texture.loadFromImage(textureImage);
	animation = Animation(&texture, spriteCount, spriteLifeTime);

	hitBox.setSize(hitBoxSize);
	hitBox.setOrigin(hitBox.getSize() / 2.0f);
	hitBox.setPosition(position);
	animationArea.setSize(sf::Vector2f(82.0f, 82.0f));
	animationArea.setOrigin(hitBox.getPosition());
	animationArea.setPosition(hitBox.getPosition());

	font.loadFromFile(fontPath);
	text.setFont(font);
	text.setFillColor(sf::Color(204, 158, 0));
	text.setCharacterSize(valueSize);
	text.setPosition(sf::Vector2f(hitBox.getPosition().x - offSet.x, hitBox.getPosition().y - offSet.y));
	text.setString(std::to_string(this->value));
}

Coins::Coins(float value, unsigned int valueSize, sf::Vector2f offSet, sf::Font* font, sf::Vector2f position, sf::Vector2f hitBoxSize, sf::Texture* texture, sf::Vector2u spriteCount, float spriteLifeTime)
{
	this->value = value;
	animation = Animation(texture, spriteCount, spriteLifeTime);

	hitBox.setTexture(nullptr);
	hitBox.setSize(hitBoxSize);
	hitBox.setOrigin(hitBox.getSize() / 2.0f);
	hitBox.setPosition(position);
	animationArea.setSize(sf::Vector2f(82.0f, 82.0f));
	animationArea.setOrigin(animationArea.getPosition() / 2.0f);
	animationArea.setTexture(texture);
	animationArea.setPosition(sf::Vector2f(hitBox.getPosition().x - 42.0f, hitBox.getPosition().y - 42.0f));

	text.setFont(*font);
	text.setFillColor(sf::Color(204, 158, 0));
	text.setCharacterSize(valueSize);
	text.setPosition(sf::Vector2f(hitBox.getPosition().x - offSet.x, hitBox.getPosition().y - offSet.y));
	text.setString(std::to_string((int)this->value));
}

Coins::~Coins()
{
}

void Coins::Update(float deltatime)
{
	animation.Update(0, deltatime, true);
	animationArea.setTextureRect(animation.textureRect);
}

void Coins::Draw(sf::RenderWindow& gameWindow)
{
	if (!isCollected) {
		gameWindow.draw(animationArea);
		//gameWindow.draw(hitBox);
		gameWindow.draw(text);
	}
}

float Coins::GetScore()
{
	if (!isCollected) {
		return value;
	}
	return 0.0f;
}

void Coins::Collected(bool yes)
{
	isCollected = yes;
}

Collision Coins::GetCollision()
{
	return hitBox;
}
