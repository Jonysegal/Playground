#include "Animation.h"



Animation::Animation(std::string dir, int tileSize)
{
	currentTime = 0;
	currentFrame = 0;

	texture.loadFromFile(dir);

	for (int i = 0; i < texture.getSize().x / tileSize; i++) {

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(i*tileSize, 0, tileSize, tileSize));
		sprites.push_back(sprite);
	}
}


Animation::~Animation()
{
}

void Animation::setTexture(sf::Texture texture) {
	Animation::texture = texture;
}

sf::Sprite * Animation::getSprite(float speed, bool loop) {

	float frameTime = 1 / speed;
	
	float dt = ((float)(clock() - t)) / CLOCKS_PER_SEC;
	t = clock();
	currentTime += dt;

	if (currentTime >= frameTime) {
		currentTime = 0;
		currentFrame++;
		if (currentFrame >= sprites.size()) {
			currentFrame = 0;
		}

	}


return &sprites.at(currentFrame);

}
