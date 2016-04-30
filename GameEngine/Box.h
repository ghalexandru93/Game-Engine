#pragma once
#include "Source.h"
#include "System.h"

class Box 
{
private:
	/// <summary>
	/// Box2d body.
	/// </summary>
	b2Body *m_Body = nullptr;

	/// <summary>
	/// Box2d fixture.
	/// </summary>
	b2Fixture *m_Fixture = nullptr;

	/// <summary>
	/// Store collisions between box2d bodies.
	/// </summary>
	vector<System::MyBodyData*> m_Collision;
	
protected:
	/// <summary>
	/// Body data.
	/// </summary>
	System::MyBodyData m_BodyData;

	/// <summary>
	/// Box2d world.
	/// </summary>
	b2World *m_World;
		
public:
	/// <summary>
	/// Loop through all collisions between box2d bodies and store that bodies to @m_Collision.
	/// </summary>
	void Collision();

	/// <summary>
	/// Get a vector of all box2d bodies who collide.
	/// </summary>
	/// <returns></returns>
	vector<System::MyBodyData*> GetCollision() { return m_Collision; }

	/// <summary>
	/// Clear all bodies from collision vector.
	/// </summary>
	void ClearCollision() { m_Collision.clear(); }

	/// <summary>
	/// Add a new box2d body.
	/// </summary>
	/// <param name="world">Pointer to a box2d world.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="w">Width of body.</param>
	/// <param name="h">Height of body.</param>
	/// <param name="fixRotation">Can rotate.</param>
	/// <param name="density">Density.</param>
	/// <param name="damping">Damping.</param>
	/// <param name="friction">Friction.</param>
	/// <param name="restitution">Restitution.</param>
	/// <param name="hasGravityScale">Can have gravity scale.</param>
	/// <param name="gravityScale">Gravity scale .</param>
	virtual void AddBody(b2World* world, const float &x, const float &y, const int &w, const int &h,
		 const bool &fixRotation, const float &density, const float &damping,
		 const float &friction, const float &restitution, const bool &hasGravityScale, const float &gravityScale);

	/// <summary>
	/// Add a new box2d body.
	/// </summary>
	/// <param name="world">Pointer to a box2d world.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="w">Width of body.</param>
	/// <param name="h">Height of body.</param>
	virtual void AddBody(b2World *world, const float &x, const float &y, const int &w, const int &h);

	/// <summary>
	/// Get body.
	/// </summary>
	/// <returns></returns>
	inline  b2Body* GetBody() { return m_Body; }

	/// <summary>
	/// Get fixture.
	/// </summary>
	/// <returns></returns>
	inline  b2Fixture* GetFixture() const { return m_Fixture; }
};
