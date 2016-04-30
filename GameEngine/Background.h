#pragma once
#include "Entity.h"
#include "Player.h"
class Background : public Entity
{
public:
	Background(Scene *pScene, Entity *pPlayer);
	~Background();

	// Inherited via Entity
	virtual void Render() override;
	virtual void Load() override;
	virtual void Update() override;

	

private:
	Entity *m_Player;
	int m_BackgroundWidth;
	int m_BackgroundHeight;
	int x = 0;

	void Move();
};

