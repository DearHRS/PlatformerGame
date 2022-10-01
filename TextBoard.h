#pragma once
#include <SFML/Graphics.hpp>

class TextBoard
{
public:
	TextBoard(std::string text, unsigned int textSize, std::string fontPath, std::string texturePath, sf::Color color, sf::Vector2f textOffSet, sf::Vector2f position, sf::Vector2f size);
	TextBoard(std::string text, unsigned int textSize, sf::Font* font, sf::Texture* texture, sf::Color color, sf::Vector2f textOffSet, sf::Vector2f position, sf::Vector2f size);
	TextBoard();
	~TextBoard();
	void SetFont(sf::Font* font);
	void SetText(std::string text);
	void SetPosition(sf::Vector2f textOffSet);
	void Draw(sf::RenderWindow& gameWindow);

private:
	sf::Texture texture;
	sf::RectangleShape body;
	sf::Font font;
	sf::Text text;
};

