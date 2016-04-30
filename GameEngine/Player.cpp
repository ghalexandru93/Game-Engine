#include "Player.h"

Player::Player(Scene *pScene, b2World **pWorld) :
	Entity(pScene, pWorld)
{

}

Player::~Player()
{

}

void Player::Load()
{
	Add("player", 800 / 2, 480 / 2, 210 / 2, 362 / 2, true, 1);
	
	SetLines(1);
	SetColumns(17);
	SetRow(1);
	SetElements(17);
	SetFrameSpeed(50);
	SetAngle(0);
	SetFlip(SDL_FLIP_NONE);
	SetVisibility(true);
	SetVelocity(200.0f);
}

void Player::Update()
{
	Collision();

	Move();
	Jump();

	ClearCollision();
}

void Player::Render()
{
	Texture::DrawSprite(GetTexture("alex"), GetX() - GetWidth() / 2, GetY() - GetHeight() / 2,
		GetWidth(), GetHeight(), GetLines(), GetColumns(), GetRow(), GetElements(), GetFrameSpeed(),
		GetAngle() * 180 / M_PI, GetFlip(), GetKeyState("left") || GetKeyState("right"), GetVisibility());

	Font::DrawFont(GetFont("pixelate"), GetX() - GetWidth() / 2 , GetY() - GetHeight() / 2 - 25, "hi there!", 
		Font::eStyle::shaded, color, color2, GetAngle(), SDL_FLIP_NONE, GetVisibility());
}

void Player::Move()
{
	static bool isMoving = false;

	static b2Vec2 velocity;
	static b2Vec2 desiredVelocity;
	static b2Vec2 velocityChange;
	static b2Vec2 impulse;

	velocity = GetBody()->GetLinearVelocity();

	if (GetKeyState("right"))
		SetFlip(SDL_FLIP_NONE);
	else if (GetKeyState("left"))
		SetFlip(SDL_FLIP_HORIZONTAL);

	if (GetKeyState("right") && GetBody()->GetPosition().x < float(System::GetVWidth() / 2 + 200))
	{
		isMoving = true;
		desiredVelocity.Set(GetVelocity(), 0.0f);
	}
	else if (GetKeyState("left") && GetBody()->GetPosition().x >= float(System::GetVWidth() / 2 - 200))
	{
		isMoving = true;
		desiredVelocity.Set(-GetVelocity(), 0.0f);
	}
	else
	{
		isMoving = false;
		desiredVelocity.Set(0.0f, 0.0f);
	}

	velocityChange.Set(desiredVelocity.x - velocity.x, velocity.y);
	impulse.Set(GetBody()->GetMass() * velocityChange.x, GetBody()->GetMass() * velocityChange.y);
	GetBody()->ApplyLinearImpulse(impulse, GetBody()->GetWorldCenter(), true);

}

void Player::Jump()
{
	static int x = 0;

	if (GetKeyState("space") && GetCollision().size() >= 1)
		x = 20;

	if (x > 0 )
	{
		GetBody()->SetLinearVelocity(b2Vec2(GetBody()->GetLinearVelocity().x, -100.0f));
		x--;
	}
	else if(GetBody()->GetLinearVelocity().y <= -1.0f)
	{
		GetBody()->SetLinearVelocity(b2Vec2(GetBody()->GetLinearVelocity().x, 3.0f));
	}

}



