# Playground
Repository for a 2D platformer in SFML. There's not really a concrete plan for it yet, it's in its early stages. Feel free to contribute!


Playground (a temporary name) is a 2D game made with SFML and C++. As I have ideas for the game, I'll list them here, and anyone can help out if they'd like!


Ideas:

- The player's gun is used to move him in some way (crazy recoil)


IMPORTANT INFORMATION IF YOU WANT TO CLONE OR FORK THIS REPOSITORY:

I use Visual Studio for this project, but you may notice that there are no Visual studio files in this repository. I purposely leave these out so that contributors can fork the repository and choose to use Visual Studio or a different IDE. All that you get are the projects resources and code. That being said, if you want to use Visual Studio, here's how:

1. Fork the repository.
2. Make a clone of your fork on your computer.
3. In the same directory as the repository, create an empty Visual C++ project named "Playground"
4. Add all of the .cpp and .h files by right clicking in the Solution Explorer and navigating to Add -> Existing Item...
5. Setup SFML in your project settings (https://www.sfml-dev.org/tutorials/2.4/start-vc.php)
6. Start contributing!
7. After you make changes, fetch and merge from the upstream repo (this one).
8. Push to your forked repo.
9. Make a pull-request!

To give you an idea of the progress made,

Some features that are implemented:
- Basic box collision
- Sprite animation
- Abstracted GameObject and Entity classes
- Level class which can load level files (which needs to be redone)
- Basic fullscreen GLSL shader functionality
- Player movement
- View tracks the player
