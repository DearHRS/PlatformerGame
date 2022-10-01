#include "player.h"
#include <iostream>

Player::~Player()
{
}

Player::Player(float hitPoints, std::string texturePath, sf::Vector2u spriteCount, float spriteLifeTime, float speed, float jumpHeight)
{
	sf::Image playerSpriteSheet;
	playerSpriteSheet.loadFromFile(texturePath);
	playerSpriteSheet.createMaskFromColor(sf::Color(255, 174, 201));
	texture.loadFromImage(playerSpriteSheet);
	animation = Animation(&texture, spriteCount, spriteLifeTime);

	score = 0.0f;
	life = 4;
	this->hitPoints = hitPoints;
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	spriteRow = 0;
	isFacingRight = true;

	hitBox.setSize(sf::Vector2f(34.0f, 140.0f));
	hitBox.setOrigin(hitBox.getSize() / 2.0f);
	hitBox.setPosition(200.0f, 200.0f);
	hitBox.setTexture(nullptr);

	animationArea.setSize(sf::Vector2f(155.0f, 160.0f));
	animationArea.setOrigin(animationArea.getSize() / 2.0f);
	animationArea.setTexture(&texture);
	animationArea.setPosition(200.0f, 200.0f);	
}

void Player::Draw(sf::RenderWindow& gameWindow)
{
	//std::cout << "can jump = " << canJump << "\n";
	//gameWindow.draw(hitBox);							//draws hitbox
	animationArea.setPosition(hitBox.getPosition());
	gameWindow.draw(animationArea);
}

void Player::AllowJump(bool allow)
{
	canJump = allow;
}

void Player::TakesDamage(float amountTaken)
{
	hitPoints = hitPoints - amountTaken;
}

void Player::SetLife(int lifeAmount)
{
	life = lifeAmount;
}

int Player::GetLife()
{
	return life;
}

float Player::GetScore()
{
	return score;
}

void Player::SetScore(float score)
{
	this->score = score;
}

void Player::SetPosition(sf::Vector2f position)
{
	hitBox.setPosition(position);
}

void Player::Update(float deltatime)
{
	//std::cout << " x = " << GetPosition().x << ", y = " << GetPosition().y << "\n";
	if (hitPoints <= 0) {
		hitPoints = 10.0f;
		SetPosition(sf::Vector2f(200.0f, 200.0f));
		life -= 1;
	}

	velocity.x = 0.0f;  //how long it takes to stop
	velocity.y += 9.81f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump) {
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)){
		std::cout << " x = " << GetPosition().x << ", y = " << GetPosition().y << "\n";
	}


	//jumping
	if (velocity.y < 0.0f && !canJump) {
		spriteRow = 2;
		if (velocity.x > 0.0f) {
			isFacingRight = true;
		}
		else if(velocity.x < 0.0f)
		{
			isFacingRight = false;
		}
	}
	//falling
	else if (velocity.y > 0.0f && !canJump) {
		spriteRow = 3;
		if (velocity.x > 0.0f) {
			isFacingRight = true;
		}
		else if (velocity.x < 0.0f)
		{
			isFacingRight = false;
		}
	}
	//standing still
	else if (velocity.x == 0.0f) {
		spriteRow = 0;
	}
	//walking
	else {
		spriteRow = 1;

		if (velocity.x > 0.0f) {
			isFacingRight = true;
		}
		else if (velocity.x < 0.0f)
		{
			isFacingRight = false;
		}
	}

	animation.Update(spriteRow, deltatime, isFacingRight);
	animationArea.setTextureRect(animation.textureRect);
	hitBox.move(velocity * deltatime);
}

sf::Vector2f  Player::GetPosition() {
	return hitBox.getPosition();
}

Collision Player::GetCollision()
{
	return Collision(hitBox);
}


void Player::OnColliosion(sf::Vector2f direction)
{
	//colliding on the left
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	//colliding on the right
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	//colliding on the bottom
	if (direction.y < 0.0f) {;
		velocity.y = 0.0f;
	}
	//colliding on the top
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;
		canJump = false;
	}
}


