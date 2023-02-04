#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif
#define MUNCHIECOUNT 50
#define GHOSTCOUNT 1



// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

struct movingenemy 
{
	Vector2* position;
	Texture2D* texture;
	Rect* souceRect;
	int direction;
	float speed;
};


struct player 
{
	bool dead;
	int player_frame;
	int currentframetime;
	float speedmultiplier;
	int  player_direction;
	int frame;
	Rect* sourcerect;
	Texture2D* texture;
	Vector2* position;
	 float _cpacmanSpeed = 0.30f;
	const int player_frame_time;
	player() : player_frame_time(250)
	{};
};

struct collectable
{
	Vector2* position;
	int munchieframe;
	int munchiecurrentframetime;
	Rect* _munchieRect;
	Texture2D* _munchieBlueTexture;
	int _frameCount;
	int currentframetime;
	const int Ccollectableframetime;
	collectable() : Ccollectableframetime(500)
	{};
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

	movingenemy* ghost[GHOSTCOUNT];

	// Data to represent Pacman
	player* _Pacman;
	player _pacman;
	SoundEffect* _pop;
	SoundEffect* _coin;
	SoundEffect* _ghost;
	SoundEffect* _run;
	SoundEffect* _pause;
	// Data to represent Munchie
	collectable* collectables[MUNCHIECOUNT];
	// Position for String
	Vector2* _stringPosition;

	//data for menu
	menu* start_menu;

	void ceckghostcollisions();
	void updateghosts(movingenemy*, int elapsedTime);


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

	bool collisioncheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

	//void Input(elapsedTime, keyboardState, mouseState, Input::Keys::R);
};