#include "Game.h"

void Game::GetDisplayInfo(void)
{
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++)	//	Get the number of avabile video display
	{
		if (SDL_GetCurrentDisplayMode(i, &m_Display) == 0)	//	If it's working it will return 0
															//	and it will fill @_Display with info;
		{
			SDL_Log("Display #%d: Display mode is %dx%dpx @ %dhz.\n",
				i, m_Display.w, m_Display.h, m_Display.refresh_rate);
		}
		else	// Throw an error if it's not working and stop the game;
			System::ShowErrorMessage("Display error!","Can't find any Display", &m_Running, m_Window);

		SDL_RendererInfo drinfo;
		SDL_GetRenderDriverInfo(i, &drinfo);

		SDL_Log("Driver name: %s\n", drinfo.name);
		if (drinfo.flags & SDL_RENDERER_SOFTWARE)
			SDL_Log("Renderer: software fallback\n");
		if (drinfo.flags & SDL_RENDERER_ACCELERATED)
			SDL_Log("Renderer uses hardware acceleration\n");
		if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC)
			SDL_Log("Present is synchronized with the refresh rate\n");
		if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE)
			SDL_Log("Renderer supports rendering to texture\n");
	}
}

void Game::ClearBodies()
{
	if (!m_DeleteBodies)
	{
		for (b2Body* b = m_World->GetBodyList(); b; b = b->GetNext())
		{
			if (b != nullptr)
			{
				System::MyBodyData *data = static_cast <System::MyBodyData*>(b->GetUserData());
				if (data->deleteFlag == true)
				{
					m_DeadBodies.push_back(b);
				}
			}
		}

		for (auto &ptr : m_DeadBodies)
		{
 			m_World->DestroyBody(ptr);
			ptr->SetUserData(nullptr);
			ptr = nullptr;
		}

		m_DeadBodies.clear();
	}
	else
	{
		for (b2Body* b = m_World->GetBodyList(); b; b = b->GetNext())
			m_DeadBodies.push_back(b);

		for (auto &ptr : m_DeadBodies)
		{
			m_World->DestroyBody(ptr);
			ptr->SetUserData(nullptr);
			ptr = nullptr;
		}
		m_DeadBodies.clear();

		m_DeleteBodies = false;
	}
}

const bool Game::Init(const string &title)
{
	//	Throw an error if SDL init failed and stop the game;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		System::ShowErrorMessage("SDL init fail!", &m_Running, m_Window);

	SDL_Log("SDL init SUCCEED\n");

	GetDisplayInfo();

	//	Create main window;
	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, System::GetWidth(), System::GetHeight(), System::GetFullScreenFlag());

	//	Throw an error if @_Window init failed and stop the game;
	if (m_Window == 0)
		System::ShowErrorMessage("Window init fail!", &m_Running, m_Window);

	SDL_Log("Window creation SUCCEED\n");

	//	Create main renderer;
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//	Throw an error if @_Renderer init failed and stop the game;
	if (m_Renderer == 0)
		System::ShowErrorMessage("Renderer init fail!", &m_Running, m_Window);

	SDL_Log("Renderer creation SUCCEED\n");

	//	Set the gray color
	SDL_SetRenderDrawColor(m_Renderer, 16, 78, 139, 255);

	//	Throw an error if TTF_Init failed and stop the game;
	if (TTF_Init() != 0)
		System::ShowErrorMessage("Font init fail!", &m_Running, m_Window);

	SDL_Log("Font init SUCCEED\n");

	//	Throw an error if Mix_OpenAudio failed and stop the game;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Mix_OpenAudio FAILED", Mix_GetError(), m_Window);
		return m_Running = false;
	}

	SDL_Log("Audio init SUCCEED\n");
	SDL_Log("Game init SUCCEED \n");

	m_Running = true;  //  Everything INITED successfully, start the main loop;

	m_World = new b2World(b2Vec2(0.0f, 9.8f));
	m_World->SetAllowSleeping(true);

		//	Loading game content.
	Loading();

	return true;
}

void Game::Loading(void)
{
	m_Scenes[MENU] = new Menu(&m_Window, &m_Renderer, &m_Running, m_Texture, m_Font, m_Sound, &m_Keyboard, &m_Mouse);
	m_Scenes[GAME] = new GameScene(&m_Window, &m_Renderer, &m_Running, &m_World, m_Texture, m_Font, m_Sound, &m_Keyboard, &m_Mouse);

	m_Sound->LoadMusic(System::Path::Sound + "ambient.mp3", "ambient");

	m_Font->LoadFont(System::Path::Font + "pacman.ttf", "pacman", 75);
	m_Font->LoadFont(System::Path::Font + "pixelate.ttf", "pixelate", 25);

	m_Texture->LoadTexture(System::Path::Texture + "background.png", "background");
	m_Texture->LoadTexture(System::Path::Texture + "back_button.png", "back_button");
	m_Texture->LoadTexture(System::Path::Texture + "alex.png", "alex");
	m_Texture->LoadTexture(System::Path::Texture + "rect2.png", "rect");

	m_Scenes[MENU]->SetIsAvailable(true);
	m_Scenes[MENU]->Load();
	m_Scenes[MENU]->SetNextScene(m_Scenes[GAME]);

	m_Scenes[GAME]->SetIsAvailable(false);
	m_Scenes[GAME]->Load();
	m_Scenes[GAME]->SetPrevScene(m_Scenes[MENU]);
}

void Game::Update(void)
{
	m_World->Step(1.0f / 60.0f, 8, 3);
	ClearBodies();

	m_Scenes[MENU]->Update();
	m_Scenes[GAME]->Update();
}

void Game::Render(void)
{
	SDL_RenderClear(m_Renderer);

	m_Scenes[MENU]->Render();
	m_Scenes[GAME]->Render();
	
	SDL_RenderPresent(m_Renderer);
}

void Game::Events(SDL_Event *event)
{
	//  Handle windows close
	if (event->type == SDL_QUIT)
		m_Running = false;

	//  Handle screen resize
	if (event->type == SDL_WINDOWEVENT)
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			break;
		}
	}

	//	If a key was pressed
	if(event->type == SDL_KEYDOWN)
		switch (event->key.keysym.sym)
		{
		case SDLK_DOWN:
			m_Keyboard["down"] = true;
			SDL_Log("key down pressed\n");
			break;

		case SDLK_UP:
			m_Keyboard["up"] = true;
			SDL_Log("key up pressed\n");
			break;

		case SDLK_LEFT:
			SDL_Log("key left pressed\n");
			m_Keyboard["left"] = true;
			break;

		case SDLK_RIGHT:
			SDL_Log("key right pressed\n");

			m_Keyboard["right"] = true;
			break;

		case SDLK_ESCAPE:
			SDL_Log("esc pressed\n");
			m_Running = false;
			break;

		case SDLK_0:
			SDL_Log("0 numpad pressed\n");
			break;

		case SDLK_a:
			m_Keyboard["a"] = true;
			SDL_Log("key a pressed\n");
			break;

		case SDLK_b:
			SDL_Log("key b pressed\n");
			break;

		case SDLK_x:
			m_Keyboard["x"] = true;
			SDL_Log("key x pressed\n");
			break;

		case SDLK_SPACE:
			m_Keyboard["space"] = true;
			SDL_Log("key space pressed\n");
			break;

		default:
			break;
		}

	//  If a key was released
	if (event->type == SDL_KEYUP)
		switch (event->key.keysym.sym)
		{
		case SDLK_DOWN:
			m_Keyboard["down"] = false;
			SDL_Log("key down released\n");
			break;

		case SDLK_UP:
			m_Keyboard["up"] = false;
			SDL_Log("key up released\n");
			break;

		case SDLK_LEFT:
			SDL_Log("key left released\n");
			m_Keyboard["left"] = false;
			break;

		case SDLK_RIGHT:
			SDL_Log("key right released\n");
			m_Keyboard["right"] = false;
			break;

		case SDLK_d:
			SDL_Log("key d released\n");
			break;

		case SDLK_a:
			m_Keyboard["a"] = false;
			SDL_Log("key a released\n");
			break;

		case SDLK_b:
			SDL_Log("key b released\n");
			break;

		case SDLK_x:
			m_Keyboard["x"] = false;
			SDL_Log("key x released\n");
			break;

		case SDLK_0:
			SDL_Log("numpad 0 released\n");
			break;

			case SDLK_SPACE:
				m_Keyboard["space"] = false;
				SDL_Log("space released\n");
				break;

		default:
			break;
		}

	//  If a mouse button was pressed
	if (event->type == SDL_MOUSEBUTTONDOWN)
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			SDL_Log("mouse left pressed x-> %d\n", event->button.x);
			SDL_Log("mouse left pressed y-> %d\n", event->button.y);
			
			m_Mouse["left"] = true;

			break;

		case SDL_BUTTON_RIGHT:
			SDL_Log("mouse right pressed x-> %d\n", event->button.x);
			SDL_Log("mouse right pressed y-> %d\n", event->button.y);

			m_Mouse["right"] = true;
			break;

		default:
			break;
		}

	//  If a mouse button was released
	if (event->type == SDL_MOUSEBUTTONUP)
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			SDL_Log("mouse left released x-> %d\n", event->button.x);
			SDL_Log("mouse left released y-> %d\n", event->button.y);

			m_Mouse["left"] = false;
			break;

		case SDL_BUTTON_RIGHT:
			SDL_Log("mouse right released x-> %d\n", event->button.x);
			SDL_Log("mouse right released y-> %d\n", event->button.y);

			m_Mouse["right"] = false;
			break;

		default:
			break;
		}
}

void Game::Clean(void)
{
	delete m_World;
	delete m_Texture;
	delete m_Font;
	delete m_Sound;

	for (auto itr = m_Scenes.begin(); itr != m_Scenes.end(); itr++)
	{
		delete itr->second;
	}
	m_Scenes.empty();
}

Game::Game()
{
	m_Texture = new Texture(&m_Window, &m_Renderer, &m_Running);
	m_Font = new Font(&m_Window, &m_Renderer, &m_Running);
	m_Sound = new Sound(&m_Window, &m_Running);
}

Game::~Game()
{
	SDL_Log("Cleaning game \n");

	Clean();
	TTF_Quit();
	Mix_Quit();
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	m_Window = nullptr;
	m_Renderer = nullptr;

	SDL_Quit();
}
