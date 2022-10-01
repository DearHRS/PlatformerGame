#include "TextBoard.h"

TextBoard::TextBoard(std::string text, unsigned int textSize, std::string fontPath, std::string texturePath, sf::Color color, sf::Vector2f textOffSet, sf::Vector2f position, sf::Vector2f size)
{
	sf::Image spritesheetTextBoard;
	spritesheetTextBoard.loadFromFile(texturePath);
	spritesheetTextBoard.createMaskFromColor(sf::Color(255, 174, 201));
	texture.loadFromImage(spritesheetTextBoard);
	body.setTexture(&texture);
	body.setPosition(position);
	body.setSize(size);

	font.loadFromFile(fontPath);
	this->text.setFont(font);
	this->text.setFillColor(color);
	this->text.setPosition(position.x + textOffSet.x, position.y + textOffSet.y);
	this->text.setCharacterSize(textSize);
	this->text.setString(text);
}

TextBoard::TextBoard(std::string text, unsigned int textSize, sf::Font* font, sf::Texture* texture, sf::Color color, sf::Vector2f textOffSet, sf::Vector2f position, sf::Vector2f size)
{
	body.setTexture(texture);
	body.setPosition(position);
	body.setSize(size);

	
	this->text.setFont(*font);
	this->text.setFillColor(color);
	this->text.setPosition(position.x + textOffSet.x, position.y + textOffSet.y);
	this->text.setCharacterSize(textSize);
	this->text.setString(text);
}

void TextBoard::SetFont(sf::Font* font) {
	text.setFont(*font);
}

TextBoard::TextBoard() {
}

TextBoard::~TextBoard()
{
}

void TextBoard::SetText(std::string text)
{
	this->text.setString(text);
}

void TextBoard::SetPosition(sf::Vector2f textOffSet) {
	text.setPosition(body.getPosition().x - textOffSet.x, body.getPosition().y - textOffSet.y);
}

void TextBoard::Draw(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(body);
	gameWindow.draw(text);
}
