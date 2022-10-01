#include "Animation.h"

Animation::~Animation() {
}

Animation::Animation() {};

Animation::Animation(sf::Texture* texture, sf::Vector2u spriteCount, float spriteLifeTime) {
	this-> spriteCount = spriteCount;
	this->spriteLifeTime = spriteLifeTime;            //how long one sprite lasts on screen
	spriteCurrentTime = 0.0f;						  //animation cycle counter
	spriteCurrent.x = 0;							  //current selected sprite

	textureRect.width = texture->getSize().x / float(spriteCount.x);
	textureRect.height = texture->getSize().y / float(spriteCount.y);
}


void Animation::Update(int spriteRow, float deltaTime, bool isFacingRight) {
	spriteCurrent.y = spriteRow;						//which animation cycle
	spriteCurrentTime += deltaTime;				//increaing Current animation cycle by second by sf::clock

	if (spriteLifeTime <= spriteCurrentTime) { //if sprites lifetime is exceeded then switch to next
		spriteCurrentTime -= spriteLifeTime;
		spriteCurrent.x++;


		if (spriteCurrent.x >= spriteCount.x) {  //resetting sprites if outside of animation cycle
			spriteCurrent.x = 0;
		}


		//adding texture on rectangle shape object
		textureRect.top = spriteCurrent.y * textureRect.height;
		
		if (isFacingRight) {
			textureRect.left = spriteCurrent.x * textureRect.width;
			textureRect.width = abs(textureRect.width);
		}
		else {
			textureRect.left = (spriteCurrent.x + 1) * abs(textureRect.width);
			textureRect.width = -abs(textureRect.width);
		}
	}
}