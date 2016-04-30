#include "Ground.h"


Ground::Ground(Scene *pScene, b2World **pWorld) : Entity(pScene, pWorld)
{

}

Ground::~Ground()
{

}

void Ground::Render()
{
	Texture::DrawTexture(GetTexture("rect"), GetX() - GetWidth() / 2, GetY() - GetHeight() / 2,
		GetWidth(), GetHeight(), GetAngle() * 180 / M_PI, GetFlip(), GetVisibility());
}

void Ground::Load()
{
	Add("background", 800 / 2, 410, 800, 10);
	SetAngle(0);
	SetFlip(SDL_FLIP_NONE);
	SetVisibility(false);
}

void Ground::Update()
{

}
