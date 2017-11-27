#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{

public:
	//Called when the game starts
	static void Start();

	static sf::RenderWindow window;

private:

	//Called once to show the main menu
	static void ShowMenu();


};
