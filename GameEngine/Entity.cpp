#include "Entity.h"

Entity::Entity(Scene *pScene, b2World **pWorld) :
	Texture(pScene->GetWindow(), pScene->GetRenderer(), pScene->GetRunning()),
	Font(pScene->GetWindow(), pScene->GetRenderer(), pScene->GetRunning()),
	Sound(pScene->GetWindow(), pScene->GetRunning())
{
	m_CurrentScene = pScene;

	m_Running = pScene->GetRunning();
	m_Window = pScene->GetWindow();
	m_Renderer = pScene->GetRenderer();

	m_Texture = pScene->GetTexture();
	m_Font = pScene->GetFont();
	m_Sound = pScene->GetSound();

	m_World = pWorld;

	m_Keyboard = pScene->GetKeyboard();
	m_Mouse = pScene->GetMouse();
}

Entity::Entity(Scene *pScene) : 
	Texture(pScene->GetWindow(), pScene->GetRenderer(), pScene->GetRunning()),
	Font(pScene->GetWindow(), pScene->GetRenderer(), pScene->GetRunning()),
	Sound(pScene->GetWindow(), pScene->GetRunning())
{
	m_CurrentScene = pScene;

	m_Running = pScene->GetRunning();
	m_Window = pScene->GetWindow();
	m_Renderer = pScene->GetRenderer();

	m_Texture = pScene->GetTexture();
	m_Font = pScene->GetFont();
	m_Sound = pScene->GetSound();

	m_Keyboard = pScene->GetKeyboard();
	m_Mouse = pScene->GetMouse();
}

Entity::~Entity()
{
	Delete();
}


void Entity::Add(const string &bodyId, const float &x, const float &y,
	const int &w, const int &h, const bool &fixRotation, const float &density,
	const float &damping, const float &friction, const float &restitution,
	const bool &hasGravityScale, const float &gravityScale)
{
	m_IsAdded = true;

	m_Width = w;
	m_Height = h;

	m_FixRotation = fixRotation;
	m_Density = density;
	m_Damping = damping;
	m_Friction = friction;
	m_Restitution = restitution;
	m_GravityScale = gravityScale;

	AddBody(*m_World, (float)x*System::M2P, (float)y*System::M2P, (float)w*System::M2P, (float)h*System::M2P, fixRotation, density, damping,
		friction, restitution, hasGravityScale, gravityScale);

	m_BodyData.type = bodyId;

	GetBody()->SetUserData(&m_BodyData);
}

void Entity::Add(const string &bodyId, const float &x, const float &y, 
	const int &w, const int &h)
{
	m_IsAdded = true;
	m_Width = w;
	m_Height = h;

	AddBody(*m_World, (float)x*System::M2P, (float)y*System::M2P, (float)w*System::M2P, (float)h*System::M2P);

	m_BodyData.type = bodyId;

	GetBody()->SetUserData(&m_BodyData);
}

const bool Entity::GetKeyState(const string &button)
{
		return m_Keyboard->operator[](button);
}

const bool Entity::GetMouseState(const string & button)
{
		return m_Mouse->operator[](button);
}

void Entity::Delete()
{
	if (m_BodyData.deleteFlag == false)
	{
		m_BodyData.deleteFlag = true;
		m_IsDeleted = true;
	}
}
