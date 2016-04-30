#include "Box.h"

void Box::AddBody(b2World* world, const float &x, const float &y, const int &w, const int &h,
	const bool &fixRotation, const float &density, const float &damping ,
	const float &friction , const float &restitution , const bool &hasGravityScale, 
	const float &gravityScale)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(x * System::P2M, y * System::P2M);
	bodyDef.linearDamping = damping;
	bodyDef.fixedRotation = fixRotation;
	Box::m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox((float)(w / 2)* System::P2M, (float)(h / 2)*System::P2M);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	fixtureDef.restitution = restitution;
	Box::m_Fixture = Box::m_Body->CreateFixture(&fixtureDef);

	if(hasGravityScale)
		GetBody()->SetGravityScale(gravityScale);
}

void Box::AddBody(b2World* world, const float &x, const float &y, const int &w, const int &h)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;

	bodyDef.position.Set(x * System::P2M, y * System::P2M);

	Box::m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox((float)(w / 2)* System::P2M, (float)(h / 2)*System::P2M);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	Box::m_Fixture = Box::m_Body->CreateFixture(&fixtureDef);
}

void Box::Collision()
{
	for (b2ContactEdge* ce = GetBody()->GetContactList(); ce; ce = ce->next)
	{
		if (!ce->contact->IsTouching())continue;

		m_Collision.push_back(static_cast<System::MyBodyData*>(ce->other->GetUserData()));
	}
}