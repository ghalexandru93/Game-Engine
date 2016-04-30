#pragma once
#include "Source.h"
#include "System.h"


/// <summary>
/// A class that can store and drow textures.
/// </summary>
class Texture
{
private:
	/// <summary>
	/// Pointer to the SDL window from @Game class.
	/// </summary>
	SDL_Window **m_Window;

	/// <summary>
	/// Pointer to the SDL renderer from @Game class.
	/// </summary>
	SDL_Renderer **m_Renderer;

	/// <summary>
	/// Pointer to the running boolean from @Game class.
	/// </summary>
	bool *m_Running;

	/// <summary>
	/// Map of textures.
	/// </summary>
	map<string, SDL_Texture*> m_Texture;

public:
	Texture(){}
	/// <summary>
	/// Initializes a new instance of the <see cref="Texture"/> class.
	/// </summary>
	/// <param name="pWindow">Main SDL_Window from @Game class.</param>
	/// <param name="pRenderer">Main SDL_Renderer from @Game class.</param>
	/// <param name="pRuning">Main running from @Game class.</param>
	Texture(SDL_Window **pWindow, SDL_Renderer **pRenderer, bool *pRuning);
	 ~Texture();

public:
	/// <summary>
	/// Loading texzture into @m_Texture.
	/// </summary>
	/// <param name="path">Path where image is.</param>
	/// <param name="id">The identifier of image.</param>
	/// <returns></returns>
	const bool LoadTexture(const string &path, const string &id);

	/// <summary>
	/// Draw a static image.
	/// </summary>
	/// <param name="pTexture">Pointer to loaded texture.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="width">Chosen width.</param>
	/// <param name="height">Chosen height.</param>
	/// <param name="angle">The angle.</param>
	/// <param name="flip">The flip.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawTexture(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
		const double &angle, const SDL_RendererFlip &flip, const bool &isVisible);

	/// <summary>
	/// Draws the texture.
	/// </summary>
	/// <param name="pTexture">Pointer to loaded texture.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="width">Chosen width.</param>
	/// <param name="height">Chosen height.</param>
	/// <param name="nrOfLines">Number of lines of current sprite sheet.</param>
	/// <param name="nrOfColumns">Number of columns of current sprite sheet.</param>
	/// <param name="row">Current row of sprite sheet.</param>
	/// <param name="currentFrame">Current element in the line and column to be draw.</param>
	/// <param name="angle">The angle.</param>
	/// <param name="flip">The flip.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawTexture(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
		const int &nrOfLines, const int &nrOfColumns, const int &row, const int &currentFrame, const double &angle,
		const SDL_RendererFlip &flip, const bool &isVisible);

	/// <summary>
	/// Draw a static image with width and height of actual window.
	/// </summary>
	/// <param name="pTexture">Pointer to loaded texture.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawBackground(SDL_Texture *pTexture, const bool &isVisible);


	/// <summary>
	/// Drow a scrollable image width width and height of actual window.
	/// </summary>
	/// <param name="pTexture">Pointer to loaded texture.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawScrollBackground(SDL_Texture *pTexture, const int &x, const int &y, const bool &isVisible);


	/// <summary>
	/// Draws the texture.
	/// </summary>
	/// <param name="pTexture">Pointer to loaded texture.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="width">Chosen width.</param>
	/// <param name="height">Chosen height.</param>
	/// <param name="nrOfLines">Number of lines of current sprite sheet.</param>
	/// <param name="nrOfColumns">Number of columns of current sprite sheet.</param>
	/// <param name="row">Current row of sprite sheet.</param>
	/// <param name="frameSpeed">Frame speed.</param>
	/// <param name="angle">The angle.</param>
	/// <param name="flip">The flip.</param>
	/// <param name="key">The key from keyboard or mouse.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawSprite(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
		const int &nrOfLines, const int &nrOfColumns, const int &row, const int &frameSpeed, const double &angle,
		const SDL_RendererFlip &flip, const bool &key, const bool &isVisible);
	

	/// <summary>
	/// Draws the texture.
	/// </summary>
	/// <param name="pTexture">Pointer to loaded texture.</param>
	/// <param name="x">x coord.</param>
	/// <param name="y">y coord.</param>
	/// <param name="width">Chosen width.</param>
	/// <param name="height">Chosen height.</param>
	/// <param name="nrOfLines">Number of lines of current sprite sheet.</param>
	/// <param name="nrOfColumns">Number of columns of current sprite sheet.</param>
	/// <param name="row">Current row of sprite sheet.</param>
	/// <param name="nrOfElements">Number of elements to be drow.</param>
	/// <param name="frameSpeed">Frame speed.</param>
	/// <param name="angle">The angle.</param>
	/// <param name="flip">The flip.</param>
	/// <param name="key">The key from keyboard or mouse.</param>
	/// <param name="isVisible">Visibility.</param>
	void DrawSprite(SDL_Texture *pTexture, const int &x, const int &y, const int & width, const int & height,
		const int & nrOfLines, const int & nrOfColumns, const int & row, const int & nrOfElements, const int & speed, 
		const double & angle, const SDL_RendererFlip & flip, const bool & key, const bool & isVisible);


	/// <summary>
	/// Return a texture assigned with an id.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	inline SDL_Texture *GetPointer(const string &id) { return m_Texture[id]; }

	/// <summary>
	/// Blend effect for texture.
	/// </summary>
	/// <param name="pTexture">The texture.</param>
	/// <param name="blend">The blend.</param>
	inline void SetBlendMod(SDL_Texture *pTexture, const SDL_BlendMode &blend) { SDL_SetTextureBlendMode(pTexture, blend); }

	/// <summary>
	/// Set the color mod for texture.
	/// </summary>
	/// <param name="pTexture">The texture.</param>
	/// <param name="r">red.</param>
	/// <param name="g">green.</param>
	/// <param name="b">blue.</param>
	inline void SetColorMod(SDL_Texture *pTexture, const Uint8 &r, const Uint8 &g, const Uint8 &b) { SDL_SetTextureColorMod(pTexture, r, g, b); }

	/// <summary>
	/// Set the color mod for texture.
	/// </summary>
	/// <param name="pTexture">The texture.</param>
	/// <param name="color">The color.</param>
	inline void SetColorMod(SDL_Texture *pTexture, const SDL_Color &color) { SDL_SetTextureColorMod(pTexture, color.r, color.g, color.b); }

	/// <summary>
	/// Set the alpha mod for texture.
	/// </summary>
	/// <param name="pTexture">The texture.</param>
	/// <param name="alpha">alpha.</param>
	inline void SetAlphaMod(SDL_Texture *pTexture, const Uint8 &alpha) { SDL_SetTextureAlphaMod(pTexture, alpha); }
};
