#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"

class GameObject : public sf::Transformable, public sf::Drawable
{
public:
	GameObject();
	GameObject(std::string dir);
	GameObject(sf::Texture & texture, sf::IntRect & textureRect);
	~GameObject();

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Color color;

	sf::FloatRect collider;

	sf::Transformable * parent = 0;
	sf::Vector2f localPosition;
	sf::Vector2f localScale;

	virtual void update();
	virtual void setColor(sf::Color color);
	virtual void setParent(sf::Transformable * target);
	virtual void removeParent();
	virtual sf::Vector2i boundCollision(GameObject * g);
	

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

