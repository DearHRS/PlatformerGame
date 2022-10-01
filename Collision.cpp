#include "Collision.h"
#include <iostream>

Collision::Collision(sf::RectangleShape& body):
    body(body)
{
}

Collision::~Collision()
{
}

void Collision::Move(float dx, float dy)
{
    body.move(dx, dy);
}

bool Collision::CheckCollision(Collision otherBody, sf::Vector2f& direction, float pushOutFactor)
{
    sf::Vector2f otherPosition = otherBody.GetPosition();
    sf::Vector2f otherHalfSize = otherBody.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float xDelta = otherPosition.x - thisPosition.x;
    float yDelta = otherPosition.y - thisPosition.y;
    float xIntersection = abs(xDelta) - (otherHalfSize.x + thisHalfSize.x);
    float yIntersection = abs(yDelta) - (otherHalfSize.y + thisHalfSize.y);

    if (xIntersection < 0.0f && yIntersection < 0.0f) {
        pushOutFactor = std::min(std::max(pushOutFactor, 0.0f), 1.0f);

        if (xIntersection > yIntersection) {
            if (xDelta > 0.0f) {
                Move(xIntersection * (1.0f - pushOutFactor), 0.0f);
                otherBody.Move(-xIntersection * pushOutFactor, 0.0f);

                direction.x = 1.0f;
                direction.y = 0.0f;
            }
            else {
                otherBody.Move(xIntersection * pushOutFactor, 0.0f);
                Move(-xIntersection * (1.0f - pushOutFactor), 0.0f);

                direction.x = -1.0f;
                direction.y = 0.0f;
            }
        }
        else {
            if (yDelta > 0.0f) {
                Move(0.0f, yIntersection * (1.0f - pushOutFactor));
                otherBody.Move(0.0f, -yIntersection * pushOutFactor);

                direction.x = 0.0f;
                direction.y = 1.0f;
            }
            else {
                otherBody.Move(0.0f, yIntersection *  pushOutFactor);
                Move(0.0f, -yIntersection * (1.0f - pushOutFactor));

                direction.x = 0.0f;
                direction.y = -1.0f;
            }
        }
        return true;
    }

    return false;
}

sf::Vector2f Collision::GetPosition()
{
    return body.getPosition();
}

sf::Vector2f Collision::GetHalfSize()
{
    return body.getSize() / 2.0f;
}
