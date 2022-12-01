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
	
	_Pacman->currentframetime = 0;
	_Pacman->frame = 0;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
	collectables[i]->munchiecurrentframetime = 0;

	}


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

	int ncount = 0;
	/*for (ncount = 0; ncount < MUNCHIECOUNT; ncount++)
	{
		delete collectables[ncount]->position;
		delete collectables[ncount]->_munchieRect;
		delete collectables[ncount];
	}*/
}


void Pacman::LoadContent()
{
	// Load Pacman
	_Pacman->texture = new Texture2D();
	_Pacman->texture->Load("Textures/Pacman.tga", false);
	_Pacman->position = new Vector2(350.0f, 350.0f);
	_Pacman->sourcerect = new Rect(0.0f, 0.0f, 32, 32);

	
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i]->currentframetime = 0;
		collectables[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	}

	Texture2D* collectabletex = new Texture2D();
	collectabletex->Load("Textures/Munchie.png", false);

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i]->_munchieBlueTexture = new Texture2D();
		collectables[i]->_munchieBlueTexture = collectabletex;
		
		//collectables[i]->_munchieBlueTexture->Load("Textures/Munchie.tga", true);

		// crate a munchie sprite sheet 12 by 12  pixils for eash sprite
		//collectables[i]->_munchieInvertedTexture = new Texture2D();
		
		collectables[i]->_munchieRect = new Rect(0.0f, 0.0f, 12, 12);
	}


	// Load Munchie
	/*collectables[MUNCHIECOUNT]->_munchieBlueTexture = new Texture2D();
	collectables[MUNCHIECOUNT]->_munchieBlueTexture->Load("Textures/Munchie.tga", true);
	collectables[MUNCHIECOUNT]->_munchieInvertedTexture = new Texture2D();
	collectables[MUNCHIECOUNT]->_munchieInvertedTexture->Load("Textures/MunchieInverted.tga", true);
	collectables[MUNCHIECOUNT]->_munchieRect = new Rect(100.0f, 450.0f, 12, 12);*/

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

	_Pacman->currentframetime += elapsedTime;


	if (_Pacman->currentframetime > _Pacman->player_frame_time) 
	{
		_Pacman->frame++;

		if (_Pacman->frame >= 2)
			_Pacman->frame = 0;

		_Pacman->currentframetime = 0;
	}

	_Pacman->sourcerect->Y = _Pacman->sourcerect->Height * _Pacman->player_direction;
	_Pacman->sourcerect->X = _Pacman->sourcerect->Width * _Pacman->frame;

	for (int i = 0; i < MUNCHIECOUNT; i++)
		collectables[i]->_munchieRect->X = collectables[i]->_munchieRect->Width * collectables[i]->_frameCount;

	
	


	/*int i;
	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[MUNCHIECOUNT] = new collectable();
		collectables[MUNCHIECOUNT]->currentframetime = 0;
	}*/
	/*for (int i = 0; i < MUNCHIECOUNT; i++) 
	{
		Updatecollectable;  (collectables[MUNCHIECOUNT], elapsedTime);
	}*/

	if (keyboardState->IsKeyDown(Input::Keys::P))
	{
		start_menu->_paused = !start_menu->_paused;
	}

	if ( !start_menu->_paused)
	{
	
		// Checks if D key is pressed
		

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
		_Pacman->player_direction = 0;
	}

	if (keyboardState->IsKeyDown(Input::Keys::A)) {

		_Pacman->position->X += -_Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across X axis
		_Pacman->player_direction = 2;
	}

	if (keyboardState->IsKeyDown(Input::Keys::W)) {

		_Pacman->position->Y += -_Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis
		_Pacman->player_direction = 3;
	}

	if (keyboardState->IsKeyDown(Input::Keys::S)) {
		_Pacman->position->Y += _Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis
		_Pacman->player_direction = 1;

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

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		if (collisioncheck(_Pacman->position->X, _Pacman->position->Y, _Pacman->sourcerect->Width, _Pacman->sourcerect->Height, collectables[i]->position->X, collectables[i]->position->Y, collectables[i]->_munchieRect->Width, collectables[i]->_munchieRect->Height))
		{
			collectables[i]->position->X = -100, -100;
			collectables[i]->position->Y = -100, -100;
		}
	}

	
}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _Pacman->position->X << " Y: " << _Pacman->position->Y;


	/*for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[MUNCHIECOUNT] = new collectable();
		collectables[MUNCHIECOUNT]->currentframetime = 0;
	}*/

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_Pacman->texture, _Pacman->position, _Pacman->sourcerect);
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		SpriteBatch::Draw(collectables[i]->_munchieBlueTexture, collectables[i]->position, collectables[i]->_munchieRect);// Draws Pacman
	}
	
	//	if (collectables[i]->_frameCount < 30)
	//	{
	//		// Draws Red Munchie
	//		SpriteBatch::Draw(collectables[i]->_munchieInvertedTexture, collectables[i]->_munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

	//		collectables[i]->_frameCount++;
	//	}
	//	else
	//	{
	//		// Draw Blue Munchie
	//		SpriteBatch::Draw(collectables[i]->_munchieBlueTexture, collectables[i]->_munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

	//		collectables[i]->_frameCount++;

	//		if (collectables[i]->_frameCount >= 60)
	//			collectables[i]->_frameCount = 0;


	//	}
	//}
	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
		if (start_menu->_paused)
		{
			std::stringstream menuStream;
			menuStream << "Paused!"; 

			SpriteBatch::Draw(start_menu->_menuBackround, start_menu->_menuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), start_menu->_menuStringPosition, Color::Red);
		}
		for (int i = 0; i < MUNCHIECOUNT; i++) 
		{
		collectables[i]->currentframetime += elapsedTime;

		}
			
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{

			if (collectables[i]->currentframetime > collectables[i]->Ccollectableframetime)
			{

				collectables[i]->_frameCount++;

				if (collectables[i]->_frameCount >= 2)
					collectables[i]->_frameCount = 0;
				
				collectables[i]->currentframetime = 0;
			}
		}
	SpriteBatch::EndDraw(); // Ends Drawing
}

bool Pacman::collisioncheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	int left1 = x1;
	int left2 = x2;
	int right1 = x1 + width1;
	int right2 = x2 + width2;
	int top1 = y1;
	int top2 = y2;
	int bottom1 = y1 + height1;
	int bottom2 = y2 + height2;
	if (bottom1 < top2)
		return false;
	if (top1 > bottom2)
		return false;
	if (right1 < left2)
		return false;
	if (left1 > right2)
		return false;

	return true;

};