#include "Menu.h"


Menu::Menu(SDL_Window **pWindow, SDL_Renderer **pRenderer, bool *pRunning,
	Texture *pTexture, Font *pFont, Sound *pSound,
	map<string, bool> *pKey, map<string, bool> *pMouse) :
	Texture(pWindow, pRenderer, pRunning),
	Font(pWindow, pRenderer, pRunning),
	Sound(pWindow, pRunning)
{
	Scene::m_Window = pWindow;
	Scene::m_Renderer = pRenderer;
	Scene::m_Running = pRunning;

	Scene::m_Texture = pTexture;
	Scene::m_Font = pFont;
	Scene::m_Sound = pSound;

	Scene::m_Keyboard = pKey;
	Scene::m_Mouse = pMouse;
}

Menu::~Menu()
{

}

void Menu::Load()
{
	SetStatus(MENU);

	m_MenuInfo["NEW_GAME"] = { 100,50,800,100 };
	m_MenuInfo["CONTINUE"] = { 100,200,800,100 };
	m_MenuInfo["QUIT"] = { 100,350,400,100 };
}

void Menu::Render()
{
	if (!GetIsAvaible())return;

	PlayMusic(Scene::m_Sound->GetPointerToMusic("ambient"));

	if (System::CheckPosition(m_MenuInfo["NEW_GAME"]))
		DrawFont(GetFont("pacman"), m_MenuInfo["NEW_GAME"].x, m_MenuInfo["NEW_GAME"].y, "New Game", Font::shaded, color1, color2, 0.0, SDL_FLIP_NONE, true);
	else
		DrawFont(GetFont("pacman"), m_MenuInfo["NEW_GAME"].x, m_MenuInfo["NEW_GAME"].y, "New Game", Font::blended, color1, color2, 0.0, SDL_FLIP_NONE, true);

	if (System::CheckPosition(m_MenuInfo["CONTINUE"]))
	{
		DrawFont(GetFont("pacman"), m_MenuInfo["CONTINUE"].x, m_MenuInfo["CONTINUE"].y, "Continue", Font::shaded, color1, color2, 0.0, SDL_FLIP_NONE, true);
		if (m_Mouse->operator[]("left"))
			Switch(nextScene);
	}
	else
		DrawFont(GetFont("pacman"), m_MenuInfo["CONTINUE"].x, m_MenuInfo["CONTINUE"].y, "Continue", Font::blended, color1, color2, 0.0, SDL_FLIP_NONE, true);

	if (System::CheckPosition(m_MenuInfo["QUIT"]))
	{
		DrawFont(GetFont("pacman"), m_MenuInfo["QUIT"].x, m_MenuInfo["QUIT"].y, "Quit", Font::shaded, color1, color2, 0.0, SDL_FLIP_NONE, true);
		if (m_Mouse->operator[]("left"))
			*Scene::m_Running = false;
	}
	else
		DrawFont(GetFont("pacman"), m_MenuInfo["QUIT"].x, m_MenuInfo["QUIT"].y, "Quit", Font::blended, color1, color2, 0.0, SDL_FLIP_NONE, true);
	
}

void Menu::Switch(Scene *scene)
{
	StopMusic();
	SetIsAvailable(false);
	scene->SetIsAvailable(true);
}

void Menu::SetNextScene(Scene *scene)
{
	nextScene = scene;
}

void Menu::SetPrevScene(Scene * scene)
{
}

void Menu::Update()
{
}


