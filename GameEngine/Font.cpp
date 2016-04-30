#include "Font.h"


Font::Font(SDL_Window **pWindow, SDL_Renderer **pRenderer, bool *pRuning)
{
	m_Window = pWindow;
	m_Renderer = pRenderer;
	m_Running = pRuning;
}

Font::~Font()
{
	for (auto &ptr : m_Font)
	{
		TTF_CloseFont(ptr.second);
		ptr.second = nullptr;
	}
	m_Font.clear();
}

const bool Font::LoadFont(const string &path, const string &id, const int &size)
{
	m_Font[id] = TTF_OpenFont(path.c_str(), TextureStretch(size));

	if (m_Font[id] == nullptr)
		System::ShowErrorMessage("Font loading fail", m_Running, *m_Window);

	return true;
}

void Font::DrawFont(TTF_Font *pFont, const int &x, const int &y, const string &text, const eStyle &style,
	const SDL_Color &FG, const SDL_Color &BG, const double &angle, const SDL_RendererFlip &flip,
	const bool &isVisible)
{
	if (!isVisible)return;

	//	Surface;
	static SDL_Surface *pSurface = nullptr;
	//	Texture;
	static SDL_Texture *pTexture = nullptr;

	//	Width and height;
	static int w = 0, h = 0;

	if (pTexture != nullptr)
	{
		SDL_DestroyTexture(pTexture);
		pTexture = nullptr;
	}

	//	What qulaity to have this font;
	FontQuality(pFont, style, FG, BG, text, &pSurface);

	//	Create texture from a surface;
	pTexture = SDL_CreateTextureFromSurface(*m_Renderer, pSurface);

	SDL_FreeSurface(pSurface);

	//	Source and destionation rect;
	static SDL_Rect srcRect, destRect;


	if (SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h) == -1)
		System::ShowErrorMessage("Font is invalid", m_Running, *m_Window);

	srcRect = { 0, 0, w, h };
	destRect = { x, y, w, h };

	destRect = System::CoordsStrech(destRect);

	SDL_RenderCopyEx(*m_Renderer, pTexture, &srcRect, &destRect, angle, 0, flip);
}

const int Font::TextureStretch(const int &size)
{
	if (System::GetWidth() == System::GetVWidth())
		return size;
	else
		return int(float(size) * System::GetRationWidth());
}

void Font::FontQuality(TTF_Font *pFont, const eStyle &style, const SDL_Color &foreground,
	const SDL_Color &background, const string &text, SDL_Surface **pSurface)
{
	switch (style)
	{
	case solid:
		*pSurface = TTF_RenderText_Solid(pFont, text.c_str(), foreground);
		break;

	case shaded:
		*pSurface = TTF_RenderText_Shaded(pFont, text.c_str(), foreground, background);
		break;

	case blended:
		*pSurface = TTF_RenderText_Blended(pFont, text.c_str(), foreground);
		break;

	default:
		System::ShowErrorMessage("Text quality not set", m_Running, *m_Window);

		break;
	}
}