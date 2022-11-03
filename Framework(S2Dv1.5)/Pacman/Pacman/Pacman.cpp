#include "Pacman.h"

#include <sstream>
 

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cpacmanSpeed(1.00f)
{

	_frameCount = 0;
	_paused = false;

	//initonalise inportant game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "pacman", 60);
	Input::Initialise();

	//start the game loop - this calls update and draw in game loop
	Graphics::StartGameLoop();
	_frameCount = 0;

	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _pacmanTexture;
	delete _pacmanSourceRect;
	delete _munchieBlueTexture;
	delete _munchieInvertedTexture;
	delete _munchieRect;
}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacmanTexture = new Texture2D();
	_pacmanTexture->Load("Textures/Pacman.tga", false);
	_pacmanPosition = new Vector2(350.0f, 350.0f);
	_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);

	// Load Munchie
	_munchieBlueTexture = new Texture2D();
	_munchieBlueTexture->Load("Textures/Munchie.tga", true);
	_munchieInvertedTexture = new Texture2D();
	_munchieInvertedTexture->Load("Textures/MunchieInverted.tga", true);
	_munchieRect = new Rect(100.0f, 450.0f, 12, 12);

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	//set menu peramaters
	_menuBackround = new Texture2D();
	_menuBackround->Load("Textures/Transparency.png", false);
	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


}

void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (keyboardState->IsKeyDown(Input::Keys::P))
	{
		_paused = !_paused;
	}

	if ( !_paused)
	{
	
		// Checks if D key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::D))
			_pacmanPosition->X += _cpacmanSpeed * elapsedTime;

		if (_pacmanPosition->X > Graphics::GetViewportWidth())
		{

			_pacmanPosition->X = -_pacmanSourceRect->Width;
		}

	}

	// Checks if D key is pressed
	if (keyboardState->IsKeyDown(Input::Keys::D))
		_pacmanPosition->X += _cpacmanSpeed * elapsedTime; //Moves Pacman across X axis

	if (keyboardState->IsKeyDown(Input::Keys::A))
		_pacmanPosition->X += -_cpacmanSpeed * elapsedTime; //Moves Pacman across X axis

	if (keyboardState->IsKeyDown(Input::Keys::W))
		_pacmanPosition->Y += -_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis

	if (keyboardState->IsKeyDown(Input::Keys::S))
		_pacmanPosition->Y += _cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis


	if (_pacmanPosition->X + _pacmanSourceRect->Width > Graphics::GetViewportWidth()) 
	{
		_pacmanPosition->X = 0;
	}

	if (_pacmanPosition->X < 0)
	{
		_pacmanPosition->X = Graphics::GetViewportWidth() - _pacmanSourceRect->Width ;
	}


	if (_pacmanPosition->Y + _pacmanSourceRect->Height > Graphics::GetViewportHeight())
	{
		_pacmanPosition->Y = 0;
	}

	if (_pacmanPosition->Y  < 0)
	{
		_pacmanPosition->Y = Graphics::GetViewportHeight() - _pacmanSourceRect->Height;
	}

}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacmanPosition->X << " Y: " << _pacmanPosition->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_pacmanTexture, _pacmanPosition, _pacmanSourceRect); // Draws Pacman

	if (_frameCount < 30)
	{
		// Draws Red Munchie
		SpriteBatch::Draw(_munchieInvertedTexture, _munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

		_frameCount++;
	}
	else
	{
		// Draw Blue Munchie
		SpriteBatch::Draw(_munchieBlueTexture, _munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
		
		_frameCount++;

		if (_frameCount >= 60)
			_frameCount = 0;


	}
	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
		if (_paused) 
		{
			std::stringstream menuStream;
			menuStream << "Paused!"; 

			SpriteBatch::Draw(_menuBackround, _menuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::Red);
		}
	SpriteBatch::EndDraw(); // Ends Drawing
}