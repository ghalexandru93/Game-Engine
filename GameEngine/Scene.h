#pragma once
#include "Source.h"
#include "Source.h"
#include "Texture.h"
#include "Font.h"
#include "Sound.h"

/// <summary>
/// Base class for all scenes.
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Update scene.
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// Load content of scene.
	/// </summary>
	virtual void Load() = 0;

	/// <summary>
	/// Render content of scene.
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// Switch to a new scene.
	/// </summary>
	/// <param name="scene">The scene.</param>
	virtual void Switch(Scene *scene) = 0;

	/// <summary>
	/// Set the next scene.
	/// </summary>
	/// <param name="scene">The scene.</param>
	virtual void SetNextScene(Scene *scene) = 0;

	/// <summary>
	/// Set the previous scene.
	/// </summary>
	/// <param name="scene">The scene.</param>
	virtual void SetPrevScene(Scene *scene) = 0;
	
	/// <summary>
	/// Set availability of scene.
	/// </summary>
	/// <param name="isAvailable">The is available.</param>
	void SetIsAvailable(const bool &isAvailable) { Scene::isAvailable = isAvailable; }

	/// <summary>
	/// Get availability of scene.
	/// </summary>
	/// <returns></returns>
	const bool GetIsAvaible() { return isAvailable; }

	/// <summary>
	/// Get the next scene.
	/// </summary>
	/// <returns></returns>
	Scene* GetNextScene() { return nextScene; }

	/// <summary>
	/// Get the previous scene.
	/// </summary>
	/// <returns></returns>
	Scene* GetPrevScene() { return prevScene; }

		//	Getters of protected members. 
	map<string, bool> *GetKeyboard() { return m_Keyboard; }
	map<string, bool> *GetMouse() { return m_Mouse; }
	SDL_Window **GetWindow() { return m_Window; }
	SDL_Renderer **GetRenderer() { return m_Renderer; }
	bool *GetRunning() { return m_Running; }
	Texture *GetTexture() { return m_Texture; }
	Font *GetFont() { return m_Font; }
	Sound *GetSound() { return m_Sound; }

	SDL_Texture *GetTexture(const string &id) { return m_Texture->GetPointer(id); }
	TTF_Font *GetFont(const string &id) { return m_Font->GetPointer(id); }
	Mix_Music *GetMusic(const string &id) { return m_Sound->GetPointerToMusic(id); }
	Mix_Chunk *GetSound(const string &id) { return m_Sound->GetPointerToSound(id); }

	 ~Scene(){}
protected:
	/// <summary>
	/// Pointer to map of keyboard events.
	/// </summary>
	map<string, bool> *m_Keyboard;

	/// <summary>
	/// Pointer to map of mouse events.
	/// </summary>
	map<string, bool> *m_Mouse;

	/// <summary>
	/// Pointer to the main SDL window.
	/// </summary>
	SDL_Window **m_Window;

	/// <summary>
	/// Pointer to the main SDL renderer.
	/// </summary>
	SDL_Renderer **m_Renderer;

	/// <summary>
	/// Pointer to the main running boolean.
	/// </summary>
	bool *m_Running;

	/// <summary>
	/// Pointer to @Texture class.
	/// </summary>
	Texture *m_Texture;

	/// <summary>
	/// Pointer to @Font class.
	/// </summary>
	Font *m_Font;

	/// <summary>
	/// Pointer to @Sound class.
	/// </summary>
	Sound *m_Sound;

	/// <summary>
	/// The next scene.
	/// </summary>
	Scene *nextScene;

	/// <summary>
	/// The previous scene
	/// </summary>
	Scene *prevScene;

protected:
	/// <summary>
	/// Get the state of the keyboard.
	/// </summary>
	/// <param name="button">The button.</param>
	/// <returns></returns>
	const bool GetKeyboardState(const string &button)
	{
			return m_Keyboard->operator[](button);
	}

	/// <summary>
	/// Get the state of the mouse.
	/// </summary>
	/// <param name="button">The button.</param>
	/// <returns></returns>
	const bool GetMouseState(const string &button)
	{
			return m_Mouse->operator[](button);
	}

private:
	bool isAvailable;
};

