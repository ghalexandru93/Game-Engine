#pragma once
#include "Game.h"
#include "Texture.h"
#include "Sound.h"
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"

class Game
{
private:
	SDL_DisplayMode m_Display;

	/// <summary>
	/// Pointer to the SDL window.
	/// </summary>
	SDL_Window *m_Window;

	/// <summary>
	/// Pointer to the SDL renderer.
	/// </summary>
	SDL_Renderer *m_Renderer;

	/// <summary>
	/// Determine if game is running.
	/// </summary>
	bool m_Running;

	/// <summary>
	/// Pointer to the box2d world.
	/// </summary>
	b2World *m_World;

	/// <summary>
	/// A vector of box2d bodies how will be deleted.
	/// </summary>
	vector<b2Body*> m_DeadBodies;

	/// <summary>
	/// If it's true then will delete all box2d bodies.
	/// </summary>
	bool m_DeleteBodies = false;

	/// <summary>
	/// Map of events of keyboard.
	/// </summary>
	map<string, bool> m_Keyboard;

	/// <summary>
	/// Map of events of mouse.
	/// </summary>
	map<string, bool> m_Mouse;
private:
	/// <summary>
	/// Pointer to texture entity.
	/// </summary>
	Texture *m_Texture;

	/// <summary>
	/// Pointer to font entity.
	/// </summary>
	Font *m_Font;

	/// <summary>
	/// Pointer to sound entity.
	/// </summary>
	Sound *m_Sound;

	/// <summary>
	/// Enum of scenes.
	/// </summary>
	enum eScenes
	{
		BG,
		MENU,
		GAME
	};

	/// <summary>
	/// Map all scenes.
	/// </summary>
	map<eScenes, Scene*> m_Scenes;
private:
/// <summary>
/// Get info about current system.
/// </summary>
	void GetDisplayInfo(void);

	/// <summary>
	/// Get all box2d bodies and delete those how have delete flag true.
	/// </summary>
	void ClearBodies();

public:
	/// <summary>
	/// Initialize the game.
	/// </summary>
	/// <param name="title">The title.</param>
	/// <returns></returns>
	const bool Init(const string &title);


	/// <summary>
	/// Load everything only once.
	/// </summary>
	void Loading(void);

	/// <summary>
	/// Handle events.
	/// </summary>
	/// <param name="event">Event from mouse or keyboard to be handle.</param>
	void Events(SDL_Event *event);


	/// <summary>
	/// Updates things.
	/// </summary>
	void Update(void);


	/// <summary>
	/// Renders things.
	/// </summary>
	void Render(void);


	/// <summary>
	/// Clears things.
	/// </summary>
	void Clean(void);

	/// <summary>
	/// Determines whether the game is running.
	/// </summary>
	/// <returns></returns>
	const bool IsRunning()const { return m_Running; }
public:
	Game();
	~Game();
};

