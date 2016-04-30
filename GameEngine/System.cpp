#include "System.h"

/// <summary>
/// The maxfpms{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
const uint System::MAXFPMS = 1000 / 60;
/// <summary>
/// </summary>
uint System::m_FPMS = 0;

const float System::M2P = 2.0;
const float System::P2M = 1 / M2P;

uint32_t System::FLAG = 0;

int System::m_WindowWidth = 0;
int System::m_WindowHeight = 0;

const int System::m_VWindowWidth = 800;
const int System::m_VWindowHeight = 480;

const string System::Path::Texture = ".\\Assets\\Textures\\";
const string System::Path::Font = ".\\Assets\\Fonts\\";
const string System::Path::Sound = ".\\Assets\\Sounds\\";
const string System::Path::Tiles = ".\\Assets\\Tiles\\";
const string System::Path::Menu = ".\\Assets\\Menu\\";

void System::LimitFrames()
{
	m_FPMS = m_FPMS - SDL_GetTicks();
	if (MAXFPMS > m_FPMS)
	{
		SDL_Delay(MAXFPMS - m_FPMS);
	}
}

void System::GetStartUpInfo()
{
	int width, height;
	int isFullScreen = 0;

	cout << "Please enter width: ";
	cin >> width;

	cout << "Please enter height: ";
	cin >> height;

	cout << "Is fullscreen?(1 for true 0 for false): ";
	cin >> isFullScreen;

	if (!(isFullScreen == 0 || isFullScreen == 1))
	{
		cout << "Value is not 0 or 1" << endl;
		exit(0);
	}

	m_WindowWidth = width;
	m_WindowHeight = height;

	if (isFullScreen)
		FLAG = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_WINDOW_ALLOW_HIGHDPI;
	else
		FLAG = SDL_WINDOW_ALLOW_HIGHDPI | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
}

const SDL_Rect System::TextureStrech(const SDL_Rect &rect)
{
	SDL_Rect newRect = rect;

	if (System::GetWidth() != System::GetVWidth())
		newRect.w = int(float(newRect.w) * System::GetRationWidth());

	if (System::GetHeight() != System::GetVHeight())
		newRect.h = int(float(newRect.h) * System::GetRationHeight());

	return newRect;
}

const SDL_Rect System::CoordsStrech(const SDL_Rect &rect)
{
	static double rationX, rationY;
	SDL_Rect newRect = rect;

	if (System::GetWidth() == System::GetVWidth())
		newRect.x = rect.x;
	else
	{
		rationX = double(rect.x) * System::GetRationWidth();
		newRect.x = int(rationX);
	}

	if (System::GetHeight() == System::GetVHeight())
		newRect.y = rect.y;
	else
	{
		rationY = double(rect.y) * System::GetRationHeight();
		newRect.y = int(rationY);
	}

	return newRect;
}

const bool System::CheckPosition(const SDL_Rect &currentPosition)
{
	SDL_Rect point;
	SDL_Rect positionStrech = System::CoordsStrech(currentPosition);
	SDL_GetMouseState(&point.x, &point.y);
	point.w = point.h = 1;

	if (SDL_HasIntersection(&positionStrech, &point))
		return true;
	else
		return false;
}

const bool System::CheckPosition(const int &x, const int &y, const int &w, const int &h)
{
	SDL_Rect rect = { x,y,w,h };
	SDL_Rect point = { 0,0,1,1 };
	rect = System::CoordsStrech(rect);

	if (SDL_HasIntersection(&rect, &point))
		return true;
	else
		return false;
}

void System::ShowErrorMessage(const string & title, const string & message, bool * pRunning, SDL_Window * pWindow)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), pWindow);
	*pRunning = false;
}

void System::ShowErrorMessage(const string & title, bool * pRunning, SDL_Window * pWindow)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), SDL_GetError(), pWindow);
	*pRunning = false;
}


