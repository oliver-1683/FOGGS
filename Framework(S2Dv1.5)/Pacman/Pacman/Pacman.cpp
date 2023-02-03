#include "Pacman.h"

#include <sstream>



Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{
	_Pacman = new player();
	_Pacman->dead = false;
	_Pacman->player_direction = 0;

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		ghost[i] = new movingenemy();
		ghost[i]->direction = 0;
		ghost[i]->speed = 0.2f;
	}

	_pop = new SoundEffect();

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i] = new collectable();
		collectables[i]->currentframetime = 0;
		collectables[i]->_frameCount = 0;
		collectables[i]->munchiecurrentframetime = 0;
		collectables[i]->munchieframe = 0;
	}
	//local veriable
	start_menu = new menu();
	start_menu->_paused = false;
	
	_Pacman->currentframetime = 0;
	_Pacman->frame = 0;

	Audio::Initialise();

	//initonalise inportant game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "pacman", 60);

	// Start the Game Loop - This calls Update and Draw in game loop
	Input::Initialise();

	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _Pacman->texture;
	delete _Pacman->sourcerect;
	delete _pop;

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

	//load sound effect
	_pop->Load("soundeffects/pop.wav");
	// Load Pacman
	_Pacman->texture = new Texture2D();
	_Pacman->texture->Load("Textures/player.png", false);
	_Pacman->position = new Vector2(350.0f, 350.0f);
	_Pacman->sourcerect = new Rect(0.0f, 0.0f, 12, 23);

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		ghost[i]->texture = new Texture2D();
		ghost[i]->texture->Load("Textures/GhostBlue.png", false);
		ghost[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		ghost[i]->souceRect = new Rect(0.0f, 0.0f, 20, 20);
	}

	Texture2D* collectabletex = new Texture2D();
	collectabletex->Load("Textures/collectable.png", false);

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		collectables[i]->_munchieBlueTexture = collectabletex;	
		collectables[i]->_munchieRect = new Rect(0.0f, 0.0f, 12, 24);
		collectables[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	}


	
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
	Input::MouseState* mouseState = Input::Mouse::GetState();

	if (!start_menu->_paused)
	{
		//Input(elapsedTime, keyboardState, mouseState, Input::Keys::R);
		//UpdatePacman(elapsedTime);
		updateghosts(ghost[0], elapsedTime);
	}

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
	{

		if (collectables[i]->currentframetime > collectables[i]->Ccollectableframetime)
		{
			collectables[i]->_frameCount++;

			if (collectables[i]->_frameCount >= 2)
				collectables[i]->_frameCount = 0;

			collectables[i]->currentframetime = 0;
		}
		collectables[i]->_munchieRect->X = collectables[i]->_munchieRect->Width * collectables[i]->_frameCount;

	}

	


	for (int i = 0; i < MUNCHIECOUNT; i++)
		collectables[i]->_munchieRect->X = collectables[i]->_munchieRect->Width * collectables[i]->_frameCount;

	

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
		_Pacman->player_direction = 2;
	}

	if (keyboardState->IsKeyDown(Input::Keys::A)) {

		_Pacman->position->X += -_Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across X axis
		_Pacman->player_direction = 1;
	}

	if (keyboardState->IsKeyDown(Input::Keys::W)) {

		_Pacman->position->Y += -_Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis
		_Pacman->player_direction = 3;
	}

	if (keyboardState->IsKeyDown(Input::Keys::S)) {
		_Pacman->position->Y += _Pacman->_cpacmanSpeed * elapsedTime; //Moves Pacman across Y axis
		_Pacman->player_direction = 0;

	}
	if (keyboardState->IsKeyDown(Input::Keys::F))
	{
		_Pacman->_cpacmanSpeed = 0.75f;
	}


	if (_Pacman->position->X + _Pacman->sourcerect->Width > Graphics::GetViewportWidth())
	{
		_Pacman->position->X = 0;
		Audio::Play(_pop);
	}

	if (_Pacman->position->X < 0)
	{
		_Pacman->position->X = Graphics::GetViewportWidth() - _Pacman->sourcerect->Width ;
		Audio::Play(_pop);
	}


	if (_Pacman->position->Y + _Pacman->sourcerect->Height > Graphics::GetViewportHeight())
	{
		_Pacman->position->Y = 0;
		Audio::Play(_pop);
	}

	if (_Pacman->position->Y  < 0)
	{
		_Pacman->position->Y = Graphics::GetViewportHeight() - _Pacman->sourcerect->Height;
		Audio::Play(_pop);
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

void Pacman::ceckghostcollisions()
{
	int i = 0;
	int bottom1 = _Pacman->position->Y + _Pacman->sourcerect->Height;
	int bottom2 = 0;
	int left1 = _Pacman->position->X ;
	int left2 = 0;
	int right1 = _Pacman->position->X + _Pacman->sourcerect->Width;
	int right2 = 0;
	int top1 = _Pacman->position->Y;
	int top2 = 0;
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		bottom2 = ghost[i]->position->Y + ghost[i]->souceRect->Height;
		left2 = ghost[i]->position->X;
		right2 = ghost[i]->position->X + ghost[i]->souceRect->Width;
		top2 = ghost[i]->position->Y;
		if ((bottom1 > top2) && (right1 > left2) && (left1 < right2));
	}
	{
		_Pacman->dead = true;
		i = GHOSTCOUNT;
	}


};
void Pacman::updateghosts(movingenemy* ghost, int elapsedTime)
{
	if (ghost->direction == 0) //moves right
	{
		ghost->position->X += ghost->speed * elapsedTime;
	}
	else if (ghost->direction == 1) // moves left
	{
		ghost->position->X -= ghost->speed * elapsedTime;
	}
	if (ghost->position->X + ghost->souceRect->Width >= Graphics::GetViewportWidth()) //hits right edge
	{
		ghost->direction = 1;
	}
	else if (ghost->position->X <= 0) //hits left edge
	{
		ghost->direction = 0; // change direction 
	}
};

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _Pacman->position->X << " Y: " << _Pacman->position->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	//SpriteBatch::Draw(_Pacman->texture, _Pacman->position, _Pacman->sourcerect);
	if (!_Pacman->dead) 
	{
		SpriteBatch::Draw(_Pacman->texture, _Pacman->position, _Pacman->sourcerect);
	}
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		SpriteBatch::Draw(collectables[i]->_munchieBlueTexture, collectables[i]->position, collectables[i]->_munchieRect);// Draws Pacman
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
	for (int i = 0; i < MUNCHIECOUNT; i++) 
	{
	collectables[i]->currentframetime += elapsedTime;

	}

	if (!_Pacman->dead) 
	{
		SpriteBatch::Draw(_Pacman->texture, _Pacman->position, _Pacman->sourcerect);
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

	//draw ghosts
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		SpriteBatch::Draw(ghost[i]->texture, ghost[i]->position, ghost[i]->souceRect);
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