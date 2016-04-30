#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(Scene *pScene, b2World **pWorld);
	~Player();

	// Inherited via Entity
	 void Render() override;

	 // Inherited via Entity
	 virtual void Load() override;

	 // Inherited via Entity
	 virtual void Update() override;

private:
	void Move();
	void Jump();

private:
	SDL_Color color2 = { 128,128,128,255 };
	SDL_Color color = { 32,32,32,255 };
};

