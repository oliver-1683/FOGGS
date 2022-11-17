#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif
#define MUNCHIECOUNT 50


// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

struct player 
{
	float speedmultiplier;
	int currentframetime;
	int direction;
	int frame;
	Rect* sourcerect;
	Texture2D* texture;
	Vector2* position;
	const float _cpacmanSpeed;
	player() : _cpacmanSpeed(1.00f)
	{};
};

struct munchie
{
	Vector2* position;
	int currentframetime;
	int _frameCount;
	Rect* _munchieRect;
	Texture2D* _munchieBlueTexture;
	Texture2D* _munchieInvertedTexture;
	Texture2D* collectabletex;
};

struct menu
{
	Texture2D* _menuBackround;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
	bool _paused;

};
// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	// Data to represent Pacman
	player* _Pacman;

	// Data to represent Munchie
	munchie* collectable[MUNCHIECOUNT];
	// Position for String
	Vector2* _stringPosition;

	

	//data for menu
	menu* start_menu;

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};