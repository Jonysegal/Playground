#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void update(float dt);
	void handleInput(sf::Event e);

	float speed = 500;

	bool movingRight, movingLeft, jumping;

};

