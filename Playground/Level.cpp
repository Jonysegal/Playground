#include "Level.h"
#include <fstream>

int parseInt(std::ifstream & level) {
	char c;
	std::string s;

	level.get(c);

	do {
		s += c;

		level.get(c);
	} while (c != '|' && c != ',' && c != ';');
	level.putback(c);

	return std::stoi(s);
}
sf::Vector2f parseVector2f(std::ifstream & level) {

	sf::Vector2f v;
	v.x = parseInt(level);
	level.get();
	v.y = parseInt(level);

	//printf("%f  %f", v.x, v.y);

	return v;
}
sf::Color parseColor(std::ifstream & level) {

	sf::Color c;
	c.r = parseInt(level);
	level.get();
	c.g = parseInt(level);
	level.get();
	c.b = parseInt(level);
	level.get();
	c.a = parseInt(level);

	return c;
}

enum ObjectType {_Player, _Enemy, _Collision, _Trigger, _Environment};


Level::Level(sf::RenderWindow & window) : window(window)
{
	gameState = Uninitialized;
}


Level::~Level()
{
}

void Level::init() {
	renderTexture.create(window.getSize().x, window.getSize().y);

	if (sf::Shader::isAvailable()) {
		fullScreenShader.loadFromFile("test.frag", sf::Shader::Fragment);
		fullScreenShader.setUniform("texture", sf::Shader::CurrentTexture);
		fullScreenShader.setUniform("windowSize", sf::Vector2f(window.getSize().x, window.getSize().y));
	}

	view.setCenter(player->getPosition());
	view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	renderTexture.setView(view);
}

void Level::load(std::string tileSetDir, int tileSize, std::string levelDir) {

	//Load tileSet texture
	if (!tileSet.loadFromFile(tileSetDir)) {
		printf("Failed to load tileset.");
	}

	//Load .level file

	std::ifstream level(levelDir);

	char c;
	while (level.get(c)) {
		GameObject * g;
		ObjectType type;

		if (c == 't') {
			level.get(c); level.get(c); level.get(c);
			g = new GameObject(tileSet, sf::IntRect(parseInt(level)*tileSize, 0, tileSize, tileSize));
		}
		else if (c == 'e') {
			g = new Entity();
			type = _Enemy;
		}
		else if (c == 'p') {
			g = new Player();
			type = _Player;
		}
		else {
			g = new GameObject();
		}

		do {

			if (c == 'P') {
				level.get(c);
				g->setPosition(parseVector2f(level));
			}
			else if (c == 'c') {
				level.get(c);

				if (parseInt(level) == 1) {
					type = _Collision;

				}
				else {
					type = _Environment;
				}
			}
			else if (c == 'C') {
				level.get(c);
				g->setColor(parseColor(level));
			}
			else if (c == 's') {

				level.get(c);
				g->setScale(parseVector2f(level));
			}
			else if (c == 'b') {
				level.get(c);

				sf::Vector2f pos = parseVector2f(level);
				level.get(c);
				sf::Vector2f size = parseVector2f(level);

				g->collider = sf::FloatRect(pos.x, pos.y, size.x, size.y);
			}
			level.get(c);
		} while (c != ';');
		level.get(c);

		switch (type) {

		case(_Environment):
			environmentObjects.push_back(g);
			break;
		case(_Collision):
			collisionObjects.push_back(g);
			break;
		case(_Trigger):
			triggerObjects.push_back(g);
			break;
		case(_Enemy):
			//enemies.push_back(g);
			break;
		case(_Player):

			player = new Player();

			player->setPosition(g->getPosition());
			player->setScale(g->getScale());
			player->setColor(g->color);
			player->collider = g->collider;


		}
	}

	init();
}

int Level::play() {
	gameState = Running;
	t = clock();
	while (gameState != Finishing) {
		update();

		if (gameState == Exiting) {
			return 1;
		}
	}

}

void Level::update() {

	//Calculate dt
	float dt = ((float)(clock() - t)) / CLOCKS_PER_SEC;
	t = clock();
	elapsedTime += dt;

	//Loop through events
	sf::Event e;
	while (window.pollEvent(e)) {

		switch (gameState) {

		case Running:

			//If the user hits the X button, close the game
			if (e.type == sf::Event::Closed) {

				gameState = Exiting;
			}
			///////////////////////////////////////////////////////////////////////

			player->handleInput(e);

			///////////////////////////////////////////////////////////////////////

			break;

		}
	}


	renderTexture.clear(sf::Color(200, 200, 200));

	view.setCenter(player->getPosition());
	renderTexture.setView(view);
	
	updateGameObjects(dt);
	updateCollisions();
	drawGameObjects();

	
	renderTexture.display();

	sf::Sprite sprite(renderTexture.getTexture());
	if (sf::Shader::isAvailable() && shaderEnabled)
	{
		fullScreenShader.setUniform("time", elapsedTime);
		window.draw(sprite, &fullScreenShader);
	}
	else {
		window.draw(sprite);
	}

	window.display();

}

void Level::updateGameObjects(float dt) {

	player->update(dt);

	for (int i = 0; i < environmentObjects.size(); i++) {
		environmentObjects.at(i)->update();
	}
	for (int i = 0; i < collisionObjects.size(); i++) {
		collisionObjects.at(i)->update();
	}
	for (int i = 0; i < triggerObjects.size(); i++) {
		triggerObjects.at(i)->update();
	}
}

void Level::updateCollisions() {

	for (int i = 0; i < collisionObjects.size(); i++) {

		sf::Vector2i v = player->boundCollision(collisionObjects.at(i));

	}
}

void Level::drawGameObjects() {

	for (int i = 0; i < environmentObjects.size(); i++) {
		renderTexture.draw(*environmentObjects.at(i));
	}
	for (int i = 0; i < collisionObjects.size(); i++) {
		renderTexture.draw(*collisionObjects.at(i));
	}
	for (int i = 0; i < triggerObjects.size(); i++) {
		renderTexture.draw(*triggerObjects.at(i));
	}

	renderTexture.draw(*player);

}