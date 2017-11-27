#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Level.h"

sf::RenderWindow Game::window;

int width = 960;
int height = 540;

///////////////////////////////////////TEST//////////////////////////////////////////

Level * level;

/////////////////////////////////////////////////////////////////////////////////////


void Game::Start() {


	//Create the window
	window.create(sf::VideoMode(width, height, 32), "Playground", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	///////////////////////////////////////TEST//////////////////////////////////////////

	level = new Level(window);
	level->load("tileset.png", 8, "test.level");

	/////////////////////////////////////////////////////////////////////////////////////


	if (level->play() == 1) {
		window.close();
	}

	window.close();
}

void Game::ShowMenu() {

}
