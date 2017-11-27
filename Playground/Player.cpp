#include "Player.h"



Player::Player()
{

	this->setPosition(sf::Vector2f(400, -200));
	this->setScale(sf::Vector2f(10, 10));
	this->setOrigin(4, 4);

	animations.push_back(new Animation("testcharacter8bit.png", 8));
	animations.push_back(new Animation("testcharacter8bitflipped.png", 8));

	animationState = WalkLeft;
	Player::sprite = *(*animations.at(animationState)).getSprite(10, true);

	collider = sprite.getLocalBounds();
	

}


Player::~Player()
{
}

void Player::update(float dt) {


	//Update sprite for current animation
	Player::sprite = *(*animations.at(animationState)).getSprite(10, true);

	if (jumping && state == Grounded) {
		velocity.y = -900;
		state = Jumping;
	}


	if (velocity.x > 500) {
		velocity.x = 500;
	}
	else if (velocity.x < -500) {
		velocity.x = -500;
	}

	Entity::update(dt);


}

void Player::handleInput(sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Right) {
			this->acceleration.x = 3000;
			animationState = WalkRight;
			movingRight = true;
		}
		else if (e.key.code == sf::Keyboard::Left) {
			this->acceleration.x = -3000;
			animationState = WalkLeft;
			movingLeft = true;
		}

		if (e.key.code == sf::Keyboard::Up) {
			jumping = true;
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::Right) {
			if (movingLeft) {
				this->acceleration.x = -3000;
				animationState = WalkLeft;
			}
			else {
				this->acceleration.x = 0;
				this->velocity.x = 0;
			}
			movingRight = false;
		}
		else if (e.key.code == sf::Keyboard::Left) {
			if (movingRight) {
				this->acceleration.x = 3000;
				animationState = WalkRight;
			}
			else {
				this->acceleration.x = 0;
				this->velocity.x = 0;
			}
			movingLeft = false;
		}
		if (e.key.code == sf::Keyboard::Up) {
			jumping = false;
		}
	}

}
