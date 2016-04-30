#pragma once
#include "Source.h"
#include "System.h"

class Font
{
private:
	/// <summary>
	/// Store fonts.
	/// </summary>
	map<string, TTF_Font*> m_Font;

	/// <summary>
	/// Pointer to the SDL renderer from @Game class.
	/// </summary>
	SDL_Renderer **m_Renderer;

	/// <summary>
	/// Pointer to SDL window from @Game class.
	/// </summary>
	SDL_Window **m_Window;

	/// <summary>
	/// Pointer to running boolean from @Game class.
	/// </summary>
	bool *m_Running;
	
public:
	Font(){}
	/// <summary>
	/// Initializes a new instance of the <see cref="Font"/> class.
	/// </summary>
	/// <param name="pWindow">Pointer to main SDL_Window of game.</param>
	/// <param name="pRenderer">Pointer to main SDL_Renderer of game.</param>
	/// <param name="pRuning">Pointer to main boolean running of game.</param>
	Font(SDL_Window **pWindow, SDL_Renderer **pRenderer, bool *pRuning);
	 ~Font();

	 /// <summary>
	 /// Enum function for different style of font.
	 /// </summary>
	 enum eStyle : Uint8 { solid, shaded, blended };

private:
	/// <summary>
	/// Make font to fit on any system resolution
	/// </summary>
	/// <param name="size">The size.</param>
	/// <returns></returns>
	const int TextureStretch(const int &size);

	/// <summary>
	/// Helper function that ajust quality of font.
	/// </summary>
	/// <param name="pFont">Pointer to stored font.</param>
	/// <param name="style">Style of font.</param>
	/// <param name="foreground">Foreground color of font.</param>
	/// <param name="background">Background color of font.</param>
	/// <param name="text">Actual text to be processed.</param>
	/// <param name="pSurface">Pointer to pointer to font surface.</param>
	void FontQuality(TTF_Font *pFont, const eStyle &style, const SDL_Color &foreground,
		const SDL_Color &background, const string &text, SDL_Surface **pSurface);

public:
	/// <summary>
	/// Loading Font into @m_Font.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <param name="id">The identifier.</param>
	/// <param name="size">The size.</param>
	/// <returns></returns>
	const bool LoadFont(const string &path, const string &id, const int &size);

	/// <summary>
	/// Draw a static font.
	/// </summary>
	/// <param name="pFont">Pointer to stored font.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="text">Actual text to be processed.</param>
	/// <param name="style">Enum function for different style of font.</param>
	/// <param name="FG">Foreground color of font.</param>
	/// <param name="BG">Background color of font.</param>
	/// <param name="angle">Angle for rotation.</param>
	/// <param name="flip">Texture fliping.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawFont(TTF_Font *pFont, const int &x, const int &y, const string &text, const eStyle &style,
		const SDL_Color &FG, const SDL_Color &BG,  const double &angle,  const SDL_RendererFlip &flip, 
		const bool &isVisible);

	/// <summary>
	/// Get a pointer to specified font.
	/// </summary>
	/// <param name="id"> Unqiue id that access stored font in @m_Font.</param>
	/// <returns></returns>
	inline TTF_Font *GetPointer(const string &id) { return m_Font[id]; }
};
