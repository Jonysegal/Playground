#include "GameObject.h"
#include <cmath>


GameObject::GameObject()
{
}
GameObject::GameObject(std::string dir) {
	texture.loadFromFile(dir);
	sprite.setTexture(texture);

	collider = sprite.getLocalBounds();

}
GameObject::GameObject(sf::Texture & texture, sf::IntRect & textureRect) {
	sprite.setTexture(texture);
	sprite.setTextureRect(textureRect);

	collider = sprite.getLocalBounds();
}

GameObject::~GameObject()
{
}

void GameObject::update() {
	
	if (parent != 0) {
		this->setPosition(parent->getPosition() - localPosition);
		this->setScale(parent->getScale() - localScale);
	}
	
}

void GameObject::setColor(sf::Color color) {
	GameObject::color = color;
}

void GameObject::setParent(sf::Transformable * target) {

	localPosition = target->getPosition() - this->getPosition();
	localScale = target->getScale() - this->getScale();

	GameObject::parent = target;
}

void GameObject::removeParent() {
	parent = 0;
}


void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}

//maybe testCollision and testTrigger
sf::Vector2i GameObject::boundCollision(GameObject * g) {

	sf::Vector2i collision = sf::Vector2i(0, 0); //-1 = left, bottom, 1 = right, top (of g) 

	sf::Vector2f position = (parent != 0) ? parent->getPosition() - localPosition : this->getPosition();
	sf::Vector2f scale = (parent != 0) ? parent->getScale() - localScale : this->getScale();
	sf::Vector2f origin = this->getOrigin();

	sf::FloatRect col1 = collider;
	col1.left *= scale.x; col1.top *= scale.y;
	col1.left += position.x - origin.x * scale.x; col1.top += position.y - origin.y * scale.y;
	col1.width *= scale.x; col1.height *= scale.y;

	position = g->getPosition();
	scale = g->getScale();
	origin = g->getOrigin();

	sf::FloatRect col2 = g->collider;
	col2.left *= scale.x; col2.top *= scale.y;
	col2.left += position.x - origin.x; col2.top += position.y - origin.y;
	col2.width *= scale.x; col2.height *= scale.y;

	bool left = col1.left <= col2.left && col2.left <= col1.left + col1.width; //collide on the left
	bool right = col2.left <= col1.left && col1.left <= col2.left + col2.width; //collide on the right

	bool top = col1.top <= col2.top && col2.top <= col1.top + col1.height; //collide on the top
	bool bottom = col2.top <= col1.top && col1.top <= col2.top + col2.height; //collide on the bottom
	

	if ((left || right) && (top || bottom)) {

		float overlapX;
		float overlapY;

		if (left) {
			overlapX = col2.left - (col1.left + col1.width);
			collision.x = -1;
		}
		else {
			overlapX = (col2.left + col2.width) - col1.left;
			collision.x = 1;
		}

		if (top) {
			overlapY = col2.top - (col1.top + col1.height);
			collision.y = 1;
		}
		else {
			overlapY = (col2.top + col2.height) - col1.top;
			collision.y = -1;
		}


		if (abs(overlapX) < abs(overlapY)) {
			overlapY = 0;
			collision.y = 0;
		}
		else {
			overlapX = 0;
			collision.x = 0;
		}

		if (parent != 0) {
			localPosition -= sf::Vector2f(overlapX, overlapY);
			this->setPosition(parent->getPosition() - localPosition);
		}
		else {
			move(sf::Vector2f(overlapX, overlapY));
		}

	}


	return collision;
}

