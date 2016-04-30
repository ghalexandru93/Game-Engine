#include "Texture.h"

Texture::Texture(SDL_Window **pWindow, SDL_Renderer **pRenderer, bool *pRuning)
{
	m_Window = pWindow;
	m_Renderer = pRenderer;
	m_Running = pRuning;
}

Texture::~Texture()
{
	for (auto &ptr : m_Texture)
	{
		SDL_DestroyTexture(ptr.second);
		ptr.second = nullptr;
	}
	m_Texture.clear();
}

const bool Texture::LoadTexture(const string &path, const string &id)
{
	//	Load image from @path and put into @pSurface;
	SDL_Surface *pSurface = IMG_Load(path.c_str());

	//	If @pSurface is null then show error message and make 
	//  @pRunning to be false;
	if (pSurface == nullptr)
		System::ShowErrorMessage("Image load fail", path, m_Running, *m_Window);

	m_Texture[id] = SDL_CreateTextureFromSurface(*m_Renderer, pSurface);
	if (m_Texture[id] == nullptr)
		System::ShowErrorMessage("Texture from surface failed!", m_Running, *m_Window);

	SDL_FreeSurface(pSurface);
	return true;
}

void Texture::DrawTexture(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
	const double &angle, const SDL_RendererFlip &flip, const bool &isVisible = false)
{
	if (!isVisible)return;

	//	Width and height;
	static int w = 0, h = 0;
	for (static bool onlyOnce = true; onlyOnce != false; onlyOnce = false)
	{
		if (SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h) == -1)
			System::ShowErrorMessage("Texture is invalid", m_Running, *m_Window);
	}

	static SDL_Rect srcRect = { 0, 0, w, h };
	static SDL_Rect destRect = { 0,0,0,0 };

	destRect = { x, y, width, height };
	destRect = System::TextureStrech(destRect);
	destRect = System::CoordsStrech(destRect);

	SDL_RenderCopyEx(*m_Renderer, pTexture, &srcRect,
		&destRect, angle, 0, flip);
}

void Texture::DrawBackground(SDL_Texture *pTexture, const bool &isVisible)
{
	if (!isVisible)return;

	SDL_RenderCopy(*m_Renderer, pTexture, nullptr, nullptr);
}

void Texture::DrawScrollBackground(SDL_Texture *pTexture, const int &x, const int &y, const bool &isVisible)
{
	if (!isVisible)return;

	static int w, h;
	static SDL_Rect srcRect;

	for (static bool onlyOnce = true; onlyOnce != false; onlyOnce = false)
	{
		if (SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h) == -1)
			System::ShowErrorMessage("Texture is invalid", m_Running, *m_Window);
	}

	srcRect = { x, y, System::GetVWidth(), System::GetVHeight() };

	SDL_RenderCopy(*m_Renderer, pTexture, &srcRect, nullptr);
}

void Texture::DrawSprite(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
	const int &nrOfLines, const int &nrOfColumns, const int &row, const int &speed, const double &angle,
	const SDL_RendererFlip &flip, const bool &key, const bool &isVisible)
{
	if (!isVisible)return;

	static SDL_Rect srcRect, destRect;

	//	Width and height;
	static int w = 0, h = 0;
	int currentFrame = 0;

	if (key == true)
		currentFrame = int(((SDL_GetTicks() / speed) % nrOfColumns));

	destRect = { x, y, width, height };

	destRect = System::TextureStrech(destRect);
	destRect = System::CoordsStrech(destRect);

	if (SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h) == -1)
		System::ShowErrorMessage("Texture is invalid", m_Running, *m_Window);

	//	Get size of one row of sprite;
	w = int(w / nrOfColumns);
	h = int(h / nrOfLines);


	//	Move frames;
	srcRect.x = w * currentFrame;
	srcRect.y = h * (row - 1);

	srcRect.w = w;
	srcRect.h = h;

	SDL_RenderCopyEx(*m_Renderer, pTexture, &srcRect,
		&destRect, angle, 0, flip);
}

void Texture::DrawSprite(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
	const int &nrOfLines, const int &nrOfColumns, const int &row, const int &nrOfElements, const int &speed,
	const double &angle, const SDL_RendererFlip &flip, const bool &key, const bool &isVisible)
{
	if (!isVisible)return;

	static SDL_Rect srcRect, destRect;

	//	Width and height;
	static int w = 0, h = 0;
	int currentFrame = 0;

	if (key == true)
		currentFrame = int(((SDL_GetTicks() / speed) % nrOfElements));

	destRect = { x, y, width, height };

	destRect = System::TextureStrech(destRect);
	destRect = System::CoordsStrech(destRect);

	if (SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h) == -1)
		System::ShowErrorMessage("Texture is invalid", m_Running, *m_Window);

	//	Get size of one row of sprite;
	w = int(w / nrOfColumns);
	h = int(h / nrOfLines);


	//	Move frames;
	srcRect.x = w * currentFrame;
	srcRect.y = h * (row - 1);

	srcRect.w = w;
	srcRect.h = h;

	SDL_RenderCopyEx(*m_Renderer, pTexture, &srcRect,
		&destRect, angle, 0, flip);
}

void Texture::DrawTexture(SDL_Texture *pTexture, const int &x, const int &y, const int &width, const int &height,
	const int &nrOfLines, const int &nrOfColumns, const int &row, const int &currentFrame, const double &angle,
	const SDL_RendererFlip &flip, const bool &isVisible)
{
	if (!isVisible)return;

	static SDL_Rect srcRect, destRect;

	//	Width and height;
	static int w = 0, h = 0;

	destRect = { x, y, width, height };

	destRect = System::TextureStrech(destRect);
	destRect = System::CoordsStrech(destRect);

	if (SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h) == -1)
		System::ShowErrorMessage("Texture is invalid", m_Running, *m_Window);

	//	Get size of one row of sprite;
	w = int(w / nrOfColumns);
	h = int(h / nrOfLines);

	//	Move frames;
	srcRect.x = w * currentFrame;
	srcRect.y = h * (row - 1);

	srcRect.w = w;
	srcRect.h = h;

	SDL_RenderCopyEx(*m_Renderer, pTexture, &srcRect,
		&destRect, angle, 0, flip);
}
