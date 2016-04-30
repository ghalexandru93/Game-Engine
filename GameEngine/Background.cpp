#include "Background.h"

Background::Background(Scene *pScene, Entity *pPlayer) : Entity(pScene)
{
	m_Player = pPlayer;
}

Background::~Background()
{

}

void Background::Render()
{
	Texture::DrawScrollBackground(GetTexture("background"), x, 0, true);
	Texture::DrawTexture(GetTexture("back_button"), 0, 0,
		71, 76, 0, SDL_FLIP_NONE, true);
}

void Background::Load()
{
	SDL_QueryTexture(GetTexture("background"), nullptr, nullptr, &m_BackgroundWidth, &m_BackgroundHeight);
}

void Background::Update()
{
	if (System::CheckPosition(0, 0, 71, 76) && GetMouseState("left"))
		GetScene()->Switch(GetScene()->GetPrevScene());

	Move();
}

void Background::Move()
{
	if (GetKeyState("right") && m_Player->GetX() >= float(System::GetVWidth() / 2 + 200))
		x += 5;
	else if (GetKeyState("left") && m_Player->GetX() <= float(System::GetVWidth() / 2 - 200))
		x -= 5;

	if (x > m_BackgroundWidth - System::GetVWidth())
		x = 0;
	else if (x < 0)
		x = m_BackgroundWidth - System::GetVWidth();
}
