#pragma once
#include "Scene.h"
#include "Source.h"
#include "Texture.h"
#include "Font.h"
#include "Sound.h"
#include "Player.h"
#include "Entity.h"
#include "Ground.h"
#include "Background.h"

class GameScene : public Scene, Texture, Font, Sound
{
public:
	GameScene(SDL_Window **pWindow, SDL_Renderer **pRenderer,
		bool *pRunning, b2World **pWorld, Texture *pTexture,
		Font *pFont, Sound *pSound, map<string, bool> *pKey,
		map<string, bool> *pMouse);
	~GameScene();

	// Inherited via Scene
	 void Update() override;
	 void Load() override;
	 void Render() override;

	// Inherited via Scene
	 void Switch(Scene * scene) override;

	// Inherited via Scene
	 void SetNextScene(Scene * scene) override;

	 void SetPrevScene(Scene * scene) override;
private:
	enum class EnumEntity
	{
		BG,
		Ground,
		Player
	};

	map<EnumEntity, Entity*> m_Entity;

};

