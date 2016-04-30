#pragma once

#include "Scene.h"
class Menu : public Scene, Texture, Font, Sound
{
public:
	Menu(SDL_Window **pWindow, SDL_Renderer **pRenderer, bool *pRunning,
		Texture *pTexture, Font *pFont, Sound *pSound,
		map<string, bool> *pKey, map<string, bool> *pMouse);
	~Menu();

	// Inherited via Scene
	 void Load() override;
	 void Render() override;

	enum Status
	{
		MENU,
		NEW_GAME,
		CONTINUE,
		QUIT
	};

private:
	SDL_Color color1 = { 0,0,0,0 };
	SDL_Color color2 = { 131,139,139,0 };

	Status m_GameStatus;
	//MouseCoord m_MouseCoord;

	map<string, SDL_Rect> m_MenuInfo;

public:
	inline void SetStatus(const Status &newStatus) { m_GameStatus = newStatus; }
	inline const Status GetStatus() { return m_GameStatus; }

	// Inherited via Scene
	 void Switch(Scene * scene) override;

	// Inherited via Scene
	 void SetNextScene(Scene * scene) override;

	// Inherited via Scene
	 void SetPrevScene(Scene * scene) override;


	 // Inherited via Scene
	 virtual void Update() override;

};

