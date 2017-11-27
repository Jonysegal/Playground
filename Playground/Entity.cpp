#include "Entity.h"



Entity::Entity()
{
	acceleration = gravity;
}


Entity::~Entity()
{
}

void Entity::update(float dt) {

	applyGravity(dt);

	if (parent != 0) {
		localPosition -= velocity * dt;
	}
	else {
		//printf("acceleration: %f  %f  velocity: %f  %f\n", acceleration.x, acceleration.y, velocity.x, velocity.y);

		this->move(velocity * dt);
	}

	state = Jumping;
	
	GameObject::update();


}

sf::Vector2i Entity::boundCollision(GameObject * g) {
	sf::Vector2i collision = this->GameObject::boundCollision(g);


	if (collision.y == 1) {
		state = Grounded;
		velocity.y = 0;
	}
	else if (collision.y == -1 && velocity.y < 0) {
		velocity.y = 0;
	}
	if ((collision.x == 1 && velocity.x <= 0) || (collision.x == -1 && velocity.x >= 0)) {

		velocity.x = 0;
	}

	return collision;


}

void Entity::applyGravity(float dt) {

	velocity += acceleration * dt;

}
