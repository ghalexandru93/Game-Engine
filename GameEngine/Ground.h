#pragma once
#include "Entity.h"

class Ground : public Entity
{
public:
	Ground(Scene *pScene, b2World **pWorld);
	~Ground();

	// Inherited via Entity
	virtual void Render() override;
	virtual void Load() override;
	virtual void Update() override;
};

