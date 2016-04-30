#include "GameScene.h"

GameScene::GameScene(SDL_Window **pWindow, SDL_Renderer **pRenderer,
	bool *pRunning, b2World **pWorld, Texture *pTexture,
	Font *pFont, Sound *pSound, map<string, bool> *pKey,
	map<string, bool> *pMouse):
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

	m_Entity[EnumEntity::Player] = new Player(this, pWorld);
	m_Entity[EnumEntity::BG] = new Background(this, m_Entity[EnumEntity::Player]);
	m_Entity[EnumEntity::Ground] = new Ground(this, pWorld);
}

GameScene::~GameScene()
{
	delete m_Entity[EnumEntity::BG];
	delete m_Entity[EnumEntity::Player];
	delete m_Entity[EnumEntity::Ground];
}

void GameScene::Load()
{
	m_Entity[EnumEntity::BG]->Load();
	m_Entity[EnumEntity::Player]->Load();
	m_Entity[EnumEntity::Ground]->Load();
}

void GameScene::Render()
{
	if (!GetIsAvaible())return;
	m_Entity[EnumEntity::BG]->Render();
	m_Entity[EnumEntity::Player]->Render();
	m_Entity[EnumEntity::Ground]->Render();
}

void GameScene::Switch(Scene *scene)
{
	SetIsAvailable(false);
	scene->SetIsAvailable(true);
}

void GameScene::SetNextScene(Scene *scene)
{
	nextScene = scene;
}

void GameScene::SetPrevScene(Scene *scene)
{
	prevScene = scene;
}

void GameScene::Update()
{
	if (!GetIsAvaible())return;
	m_Entity[EnumEntity::BG]->Update();
	m_Entity[EnumEntity::Player]->Update();
	m_Entity[EnumEntity::Ground]->Update();
}
