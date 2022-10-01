//AABB type   axis aligned bounding boxes
#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision(sf::RectangleShape& body);
	~Collision();

	void Move(float dx, float dy);
	bool CheckCollision(Collision otherBody, sf::Vector2f& direction, float newPos);
	sf::Vector2f GetPosition();
	sf::Vector2f GetHalfSize();


private:
	sf::RectangleShape& body;
};

