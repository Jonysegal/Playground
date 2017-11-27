#pragma once
#include "Player.h"

class Level
{
public:
	Level(sf::RenderWindow & window);
	~Level();

	enum GameState { Uninitialized, Running, Paused, Finishing, Exiting };
	GameState gameState;

	void load(std::string tileSetDir, int tileSize, std::string levelDir);
	void init();
	int play();
	void update();



private:

	sf::RenderWindow & window;
	sf::RenderTexture renderTexture;
	sf::View view;

	sf::Shader fullScreenShader;
	const bool shaderEnabled = false;

	float elapsedTime = 0;

	//Clock used for calculating dt
	clock_t t;

	sf::Texture tileSet;
	std::vector<sf::Sprite> tileSprites;

	Player * player;
	//std::vector<Enemy*> enemies;
	std::vector<GameObject*> collisionObjects;
	std::vector<GameObject*> triggerObjects;
	std::vector<GameObject*> environmentObjects;

	void updateGameObjects(float dt);
	void updateCollisions();
	void drawGameObjects();

};

