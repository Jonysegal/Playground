#pragma once
#include "GameObject.h"
class Entity :
	public GameObject
{
public:
	Entity();
	~Entity();

	sf::Vector2f acceleration;
	sf::Vector2f velocity;

	sf::Vector2f gravity = sf::Vector2f(0, 2400);
	float health;

	std::vector<Animation*> animations;

	enum AnimationState { WalkLeft, WalkRight };
	AnimationState animationState;

	enum State { Grounded, Jumping };
	State state;

	virtual void update(float dt);
	virtual sf::Vector2i boundCollision(GameObject * g);

protected:

	virtual void applyGravity(float dt);

};

