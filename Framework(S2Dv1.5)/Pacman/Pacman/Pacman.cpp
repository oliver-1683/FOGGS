#include "Pacman.h"

#include <sstream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{
	_Pacman = new player();
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i] = new collectable();
		collectables[i]->currentframetime = 0;
		collectables[i]->_frameCount = 0;
	}
	//local veriable
	start_menu = new menu();
	start_menu->_paused = false;

	//initonalise inportant game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _Pacman->texture;
	delete _Pacman->sourcerect;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		delete collectables[i]->_munchieBlueTexture;
		delete collectables[i]->_munchieInvertedTexture;
		delete collectables[i]->_munchieRect;
	}

	int ncount = 0;
	for (ncount = 0; ncount < MUNCHIECOUNT; ncount++) 
	{
	    delete collectables[0]->collectabletex;
		delete collectables[ncount]->position;
		delete collectables[ncount]->_munchieRect;
		delete collectables[ncount];
	}
	delete collectables;
}


void Pacman::LoadContent()
{
	// Load Pacman
	_Pacman->texture = new Texture2D();
	_Pacman->texture->Load("Textures/Pacman.tga", false);
	_Pacman->position = new Vector2(350.0f, 350.0f);
	_Pacman->sourcerect = new Rect(0.0f, 0.0f, 32, 32);

	int i;
	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		//collectables[i] = new collectable();
		collectables[i]->currentframetime = 0;
		collectables[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	}

	Texture2D* collectabletex = new Texture2D();
	collectabletex->Load("Textures/Munchie.png", false);

	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i]->_munchieBlueTexture = collectabletex;
		collectables[i]->_munchieBlueTexture = new Texture2D();
		collectables[i]->_munchieBlueTexture->Load("Textures/Munchie.tga", true);

		// crate a munchie sprite sheet 12 by 12  pixils for eash sprite
		collectables[i]->_munchieInvertedTexture = new Texture2D();
		
		collectables[i]->_munchieRect = new Rect(100.0f, 450.0f, 12, 12);
	}


	// Load Munchie
	/*collectables[i]->_munchieBlueTexture = new Texture2D();
	collectables[i]->_munchieBlueTexture->Load("Textures/Munchie.tga", true);
	collectables[i]->_munchieInvertedTexture = new Texture2D();
	collectables[i]->_munchieInvertedTexture->Load("Textures/MunchieInverted.tga", true);
	collectables[i]->_munchieRect = new Rect(100.0f, 450.0f, 12, 12);*/

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	//set menu peramaters
	start_menu->_menuBackround = new Texture2D();
	start_menu->_menuBackround->Load("Textures/Transparency.png", false);
	start_menu->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	start_menu->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


}

void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();


	/*int i;
	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i] = new collectable();
		collectables[i]->currentframetime = 0;
	}*/
	/*for (int i = 0; i < MUNCHIECOUNT; i++) 
	{
		Updatecollectable;  (collectables[i], elapsedTime);
	}*/

	if (keyboardState->IsKeyDown(Input::Keys::P))
	{
		start_menu->_paused = !start_menu->_paused;
	}

	if ( !start_menu->_paused)
	{
	
		// Checks if D key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::D))
			_Pacman->position->X += _Pacman->_cpacmanSpeed * elapsedTime;

		if (_Pacman->position->X > Graphics::GetViewportWidth())
		{

			_Pacman->position->X = -_Pacman->sourcerect->Width;
		}

	}

	// redo pacman anamations
	int direction = 0;

	// Checks if D key is pressed
	if (keyboardState->IsKeyDown(Input::Keys::D)) {
		_Pacman->position->X += _Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across X axis
		player_direction = 1
	}

	if (keyboardState->IsKeyDown(Input::Keys::A)) {

		_Pacman->position->X += -_Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across X axis
	}

	if (keyboardState->IsKeyDown(Input::Keys::W)) {

		_Pacman->position->Y += -_Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis
	}

	if (keyboardState->IsKeyDown(Input::Keys::S)) {
		_Pacman->position->Y += _Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis

	}


	if (_Pacman->position->X + _Pacman->sourcerect->Width > Graphics::GetViewportWidth())
	{
		_Pacman->position->X = 0;
	}

	if (_Pacman->position->X < 0)
	{
		_Pacman->position->X = Graphics::GetViewportWidth() - _Pacman->sourcerect->Width ;
	}


	if (_Pacman->position->Y + _Pacman->sourcerect->Height > Graphics::GetViewportHeight())
	{
		_Pacman->position->Y = 0;
	}

	if (_Pacman->position->Y  < 0)
	{
		_Pacman->position->Y = Graphics::GetViewportHeight() - _Pacman->sourcerect->Height;
	} 
}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _Pacman->position->X << " Y: " << _Pacman->position->Y;


	/*for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i] = new collectable();
		collectables[i]->currentframetime = 0;
	}*/

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_Pacman->texture, _Pacman->position, _Pacman->sourcerect); // Draws Pacman
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		if (collectables[i]->_frameCount < 30)
		{
			// Draws Red Munchie
			SpriteBatch::Draw(collectables[i]->_munchieInvertedTexture, collectables[i]->_munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

			collectables[i]->_frameCount++;
		}
		else
		{
			// Draw Blue Munchie
			SpriteBatch::Draw(collectables[i]->_munchieBlueTexture, collectables[i]->_munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

			collectables[i]->_frameCount++;

			if (collectables[i]->_frameCount >= 60)
				collectables[i]->_frameCount = 0;


		}
	}
	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
		if (start_menu->_paused)
		{
			std::stringstream menuStream;
			menuStream << "Paused!"; 

			SpriteBatch::Draw(start_menu->_menuBackround, start_menu->_menuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), start_menu->_menuStringPosition, Color::Red);
		}
	SpriteBatch::EndDraw(); // Ends Drawing
}