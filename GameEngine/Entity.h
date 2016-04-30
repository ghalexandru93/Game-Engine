#pragma once
#include "Source.h"
#include "Texture.h"
#include "Font.h"
#include "Sound.h"
#include "Box.h"
#include "Scene.h"

/// <summary>
/// Base class for all game objects.
/// </summary>
/// <seealso cref="Box" />
/// <seealso cref="Texture" />
/// <seealso cref="Font" />
/// <seealso cref="Sound" />
class Entity : protected Box, protected Texture, protected Font, protected Sound
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Entity"/> class.
	/// </summary>
	/// <param name="pScene">Current scene where entity is.</param>
	/// <param name="pWorld">Box2d world.</param>
	Entity(Scene * pScene, b2World **pWorld);

	/// <summary>
	/// Initializes a new instance of the <see cref="Entity"/> class.
	/// </summary>
	/// <param name="pScene">Current scene where entity is.</param>
	Entity(Scene * pScene);
	~Entity();

	/// <summary>
	/// Render content.
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// Load content.
	/// </summary>
	virtual void Load() = 0;

	/// <summary>
	/// Update content.
	/// </summary>
	virtual void Update() = 0;

protected:
	/// <summary>
	/// Pointer to main SDL window.
	/// </summary>
	SDL_Window **m_Window;

	/// <summary>
	/// Pointer to main SDL renderer.
	/// </summary>
	SDL_Renderer **m_Renderer;

	/// <summary>
	/// Pointer to main running boolean.
	/// </summary>
	bool *m_Running;

	/// <summary>
	/// Pointer to main box2d world.
	/// </summary>
	b2World **m_World;

	/// <summary>
	/// Ponter to delete body from @Game class.
	/// </summary>
	vector<b2Body*> *m_DeleteBody;

private:
	/// <summary>
	/// Current scene where the entity is.
	/// </summary>
	Scene *m_CurrentScene;

	/// <summary>
	/// Pointer to @Texture.
	/// </summary>
	Texture *m_Texture;

	/// <summary>
	/// Pointer to @Font.
	/// </summary>
	Font *m_Font;

	/// <summary>
	/// Pointer to @Sound.
	/// </summary>
	Sound *m_Sound;

	/// <summary>
	/// Width of entity.
	/// </summary>
	int m_Width;

	/// <summary>
	/// Hidth of entity.
	/// </summary>
	int m_Height;

	/// <summary>
	/// Velocity of entity.
	/// </summary>
	float m_Velocity;

	/// <summary>
	/// Visibility of entity.
	/// </summary>
	bool m_Visibility;

	/// <summary>
	/// Flip of entity.
	/// </summary>
	SDL_RendererFlip m_Flip;

	/// <summary>
	/// Jump value of entity.
	/// </summary>
	float m_Jump;

	/// <summary>
	/// Frame speed of entity.
	/// </summary>
	uint m_FrameSpeed;

	/// <summary>
	/// Lines of sprite sheet.
	/// </summary>
	int m_Lines;

	/// <summary>
	/// Columns of sprite sheet.
	/// </summary>
	int m_Columns;

	/// <summary>
	/// Row of sprite sheet.
	/// </summary>
	int m_Row;

	/// <summary>
	/// Elements to be draw of sprite sheet
	/// </summary>
	int m_Elements;

	/// <summary>
	/// Angle of entity.
	/// </summary>
	double m_Angle;

	/// <summary>
	/// Fix rotation of box2d body.
	/// </summary>
	bool m_FixRotation;

	/// <summary>
	/// Density of box2d body.
	/// </summary>
	float m_Density;

	/// <summary>
	/// Damping of box2d body.
	/// </summary>
	float m_Damping;

	/// <summary>
	/// Friction of box2d body.
	/// </summary>
	float m_Friction;

	/// <summary>
	/// Restitution of box2d body.
	/// </summary>
	float m_Restitution;

	/// <summary>
	/// Gravity scale of box2d body.
	/// </summary>
	float m_GravityScale;
	

	/// <summary>
	/// Check if is box2d is added.
	/// </summary>
	bool m_IsAdded = false;

	/// <summary>
	/// Check if is box2d is deleted.
	/// </summary>
	bool m_IsDeleted = false;

	/// <summary>
	/// Pointer to map of keyboard events from @Game class.
	/// </summary>
	map<string, bool> *m_Keyboard;

	/// <summary>
	/// Pointer to map of mouse events from @Game class.
	/// </summary>
	map<string, bool> *m_Mouse;
public:
	/// <summary>
	/// Get current scene.
	/// </summary>
	/// <returns></returns>
	Scene *GetScene() { return m_CurrentScene; }

	/// <summary>
	/// Delete box2d body.
	/// </summary>
	void Delete();

	/// <summary>
	/// Get the x coord.
	/// </summary>
	/// <returns></returns>
	const int GetX() { return (int)GetBody()->GetPosition().x; }

	/// <summary>
	/// Get the y coord.
	/// </summary>
	/// <returns></returns>
	const int GetY() { return (int)GetBody()->GetPosition().y; }

	/// <summary>
	/// Set angle.
	/// </summary>
	/// <param name="angle">The angle.</param>
	void SetAngle(const double &angle) { m_Angle = angle; }

	/// <summary>
	/// Get angle.
	/// </summary>
	/// <returns></returns>
	const double GetAngle() { return m_Angle; }

	/// <summary>
	/// Check if box2d body is added.
	/// </summary>
	/// <returns></returns>
	const bool CheckAdded()const { return m_IsAdded; }

	/// <summary>
	/// Set box2d body to be deleted.
	/// </summary>
	/// <param name="isDeleted">The is deleted.</param>
	void SetDeleted(const bool &isDeleted) { Entity::m_IsDeleted = isDeleted; }

	/// <summary>
	/// Check if box2d body is selected to be deleted.
	/// </summary>
	/// <returns></returns>
	const bool CheckDeleted()const { return m_IsDeleted; }

	/// <summary>
	/// Set the flip.
	/// </summary>
	/// <param name="flip">The flip.</param>
	inline void SetFlip(const SDL_RendererFlip &flip) { Entity::m_Flip = flip; }

	/// <summary>
	/// Get the flip.
	/// </summary>
	/// <returns></returns>
	inline const SDL_RendererFlip GetFlip()const { return Entity::m_Flip; }

	/// <summary>
	/// Set visibility.
	/// </summary>
	/// <param name="isVisible">The is visible.</param>
	inline  void SetVisibility(const bool &isVisible) { Entity::m_Visibility = isVisible; }

	/// <summary>
	/// Get visibility.
	/// </summary>
	/// <returns></returns>
	inline const bool GetVisibility()const { return Entity::m_Visibility; }

	/// <summary>
	/// Set velocity.
	/// </summary>
	/// <param name="velocity">The velocity.</param>
	inline void SetVelocity(const float &velocity) { m_Velocity = velocity; }

	/// <summary>
	/// Get velocity.
	/// </summary>
	/// <returns></returns>
	inline const float GetVelocity()const { return m_Velocity; }

	/// <summary>
	/// Set jump.
	/// </summary>
	/// <param name="jumpValue">The jump value.</param>
	inline void SetJump(const float &jumpValue) { m_Jump = jumpValue; }

	/// <summary>
	/// Get jump.
	/// </summary>
	/// <returns></returns>
	inline const float GetJump()const { return m_Jump; }

	/// <summary>
	/// Sets the frame speed.
	/// </summary>
	/// <param name="frameSpeed">The frame speed.</param>
	inline void SetFrameSpeed(const uint &frameSpeed) { m_FrameSpeed = frameSpeed; }

	/// <summary>
	/// Gets the frame speed.
	/// </summary>
	/// <returns></returns>
	inline const uint GetFrameSpeed()const { return m_FrameSpeed; }

protected:
	/// <summary>
	/// Get width.
	/// </summary>
	/// <returns></returns>
	const int GetWidth()const { return Entity::m_Width; }

	/// <summary>
	/// Get height.
	/// </summary>
	/// <returns></returns>
	const int  GetHeight()const { return Entity::m_Height; }

	/// <summary>
	/// Set lines of sprite sheet.
	/// </summary>
	/// <param name="nrOfLines">The nr of lines.</param>
	void SetLines(const uint nrOfLines) { m_Lines = nrOfLines; }

	/// <summary>
	/// Get lines of sprite sheet.
	/// </summary>
	/// <returns></returns>
	const uint GetLines()const { return m_Lines; }

	/// <summary>
	/// Set columns of sprite sheet.
	/// </summary>
	/// <param name="nrOfCoumns">The nr of coumns.</param>
	void SetColumns(const uint &nrOfCoumns) { m_Columns = nrOfCoumns; }

	/// <summary>
	/// Get columns of sprite sheet.
	/// </summary>
	/// <returns></returns>
	const uint GetColumns()const { return m_Columns; }

	/// <summary>
	/// Set row of sprite sheet.
	/// </summary>
	/// <param name="row">The row.</param>
	void SetRow(const uint row) { m_Row = row; }

	/// <summary>
	/// Get row of sprite sheet.
	/// </summary>
	/// <returns></returns>
	const uint GetRow()const { return m_Row; }

	/// <summary>
	/// Set elements of sprite sheet.
	/// </summary>
	/// <param name="elements">The elements.</param>
	void SetElements(const uint &elements) { m_Elements = elements; }

	/// <summary>
	/// Get elements of sprite sheet.
	/// </summary>
	/// <returns></returns>
	const uint GetElements()const { return m_Elements; }

	/// <summary>
	/// Add box2d body.
	/// </summary>
	/// <param name="bodyId">The body identifier.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="w">width to be rendered.</param>
	/// <param name="h">height to be rendered.</param>
	/// <param name="fixRotation">The fix rotation.</param>
	/// <param name="density">The density.</param>
	/// <param name="damping">The damping.</param>
	/// <param name="friction">The friction.</param>
	/// <param name="restitution">The restitution.</param>
	/// <param name="hasGravityScale">to have gravity scale.</param>
	/// <param name="gravityScale">The gravity scale.</param>
	void Add(const string &bodyId, const float &x, const float &y,
		const int &w, const int &h, const bool &fixRotation, const float &density,
		const float &damping = 0.0f, const float &friction = 0.0f, const float &restitution = 0.0f,
		const bool &hasGravityScale = false, const float &gravityScale = 0.0f);

	/// <summary>
	/// Add box2d body.
	/// </summary>
	/// <param name="bodyId">The body identifier.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="w">width to be rendered.</param>
	/// <param name="h">height to be rendered.</param>
	void Add(const string &bodyId, const float &x, const float &y,
		const int &w, const int &h);

	/// <summary>
	/// Get pointer to SDL texture how is loaded in @Game class.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	SDL_Texture *GetTexture(const string &id) { return m_Texture->GetPointer(id); }

	/// <summary>
	/// Get pointer to SDL font how is loaded in @Game class.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	TTF_Font *GetFont(const string &id) { return m_Font->GetPointer(id); }

	/// <summary>
	/// Get pointer to SDL Mix_Music how is loaded in @Game class.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	Mix_Music *GetMusic(const string &id) { return m_Sound->GetPointerToMusic(id); }

	/// <summary>
	/// Get pointer to SDL Mix_Chunk how is loaded in @Game class.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	Mix_Chunk *GetSound(const string &id) { return m_Sound->GetPointerToSound(id); }

	/// <summary>
	/// Get the state of the keyboard.
	/// </summary>
	/// <param name="button">The button.</param>
	/// <returns></returns>
	const bool GetKeyState(const string &button);

	/// <summary>
	/// Get the state of the mouse.
	/// </summary>
	/// <param name="button">The button.</param>
	/// <returns></returns>
	const bool GetMouseState(const string &button);
};

