#pragma once
#include "Source.h"

class System
{
private:
	/// <summary>
	/// Maximum frames per milisecond.
	/// </summary>
	const static uint MAXFPMS;

	/// <summary>
	/// Frames per milisecond.
	/// </summary>
	static uint m_FPMS;

	/// <summary>
	/// Real window width.
	/// </summary>
	static int m_WindowWidth;

	/// <summary>
	/// Real window height.
	/// </summary>
	static int m_WindowHeight;

	/// <summary>
	/// A virtual width which will be used to scale everything up or down to real window width.
	/// </summary>
	static const int m_VWindowWidth;

	/// <summary>
	/// A virtual height which will be used to scale everything up or down to real window height.
	/// </summary>
	static const int m_VWindowHeight;

	/// <summary>
	/// A flag for window.
	/// </summary>
	static uint32_t FLAG;

public:
	/// <summary>
	/// Meter to pixel.
	/// </summary>
	const static float M2P;

	/// <summary>
	/// Pixel to meter.
	/// </summary>
	const static float P2M;

	/// <summary>
	/// Store info about location of assets folders.
	/// </summary>
	typedef struct
	{
		const static string Texture;
		const static string Font;
		const static string Sound;
		const static string Tiles;
		const static string Menu;
	}Path;

	/// <summary>
	/// Store info about a box2d body.
	/// </summary>
	typedef struct
	{
		string type;
		int number;

		bool deleteFlag = false;
	}MyBodyData;

	/// <summary>
	/// Set @m_FPMS to have current miliseconds from the beginning of game.
	/// </summary>
	static void SetFrames() { m_FPMS = SDL_GetTicks(); }

	/// <summary>
	/// Limit frames to not overcome maximum frames per milisecond.
	/// </summary>
	static void LimitFrames();

	/// <summary>
	/// Get input info about preferable window size and flag from cmd.
	/// </summary>
	static void GetStartUpInfo();


	/// <summary>
	/// Show an error message and exit game.
	/// </summary>
	/// <param name="title">Title of window error.</param>
	/// <param name="message">Message error.</param>
	/// <param name="pRunning">Pointer to boolean running variable from @Game class.</param>
	/// <param name="pWindow">Pointer to SDL_Window variable from @Game class.</param>
	static void ShowErrorMessage(const string &title, const string &message, bool *pRunning, SDL_Window *pWindow);

	/// <summary>
	/// Show an error message and exit game.
	/// </summary>
	/// <param name="title">Title of window error.</param>
	/// <param name="pRunning">Pointer to boolean running variable from @Game class.</param>
	/// <param name="pWindow">Pointer to SDL_Window variable from @Game class.</param>
	static void ShowErrorMessage(const string &title, bool *pRunning, SDL_Window *pWindow);

	/// <summary>
	/// Scale width and height of input rect according to ration between real size window size and virtual window size.
	/// </summary>
	/// <param name="rect">Input rect.</param>
	/// <returns></returns>
	static const SDL_Rect TextureStrech(const SDL_Rect &rect);

	/// <summary>
	/// Modify x and y coords according to ration betweeen real size of window and virtual size.
	/// </summary>
	/// <param name="rect">Input rect.</param>
	/// <returns></returns>
	static const SDL_Rect CoordsStrech(const SDL_Rect &rect);

	/// <summary>
	/// Check if mouse position intersect with an object.
	/// </summary>
	/// <param name="currentPosition">Object.</param>
	/// <returns></returns>
	static const bool CheckPosition(const SDL_Rect &currentPosition);


	/// <summary>
	/// Check if mouse position intersect with an object.
	/// </summary>
	/// <param name="x">x coord of object.</param>
	/// <param name="y">y coord of object.</param>
	/// <param name="w">width of object.</param>
	/// <param name="h">height of object.</param>
	/// <returns></returns>
	static const bool CheckPosition(const int & x, const int & y, const int & w, const int & h);

	/// <summary>
	/// Return current flag of window.
	/// </summary>
	/// <returns></returns>
	static uint32_t GetFullScreenFlag() { return FLAG; }

	/// <summary>
	/// Get real width window width size.
	/// </summary>
	/// <returns></returns>
	static const int GetWidth() { return m_WindowWidth; }

	/// <summary>
	/// Get real window height size.
	/// </summary>
	/// <returns></returns>
	static const int GetHeight() { return m_WindowHeight; }

	/// <summary>
	/// Get origin of x of real window.
	/// </summary>
	/// <returns></returns>
	static const int GetOriginX() { return m_WindowWidth / 2; }

	/// <summary>
	/// Get origin of y of real window.
	/// </summary>
	/// <returns></returns>
	static const int GetOriginY() { return m_WindowHeight / 2; }

	/// <summary>
	/// Get virtual width.
	/// </summary>
	/// <returns></returns>
	static const int GetVWidth() { return m_VWindowWidth; }

	/// <summary>
	/// Get virtual height.
	/// </summary>
	/// <returns></returns>
	static const int GetVHeight() { return m_VWindowHeight; }

	/// <summary>
	/// Get virtual origin of x.
	/// </summary>
	/// <returns></returns>
	static const int GetVOriginX() { return m_VWindowWidth / 2; }

	/// <summary>
	/// Get virtual origin of y.
	/// </summary>
	/// <returns></returns>
	static const int GetVOriginY() { return m_VWindowHeight / 2; }

	/// <summary>
	/// Get width ration of real and virtual width.
	/// </summary>
	/// <returns></returns>
	static const double GetRationWidth() { return (double)m_WindowWidth / (double)m_VWindowWidth; }

	/// <summary>
	/// Get height ration of real and virtual width.
	/// </summary>
	/// <returns></returns>
	static const double GetRationHeight() { return (double)m_WindowHeight / (double)m_VWindowHeight; }

	static const int GetVTopLeftCoordX() { return 0; }
	static const int GetVTopLeftCoordY() { return 0; }
	static const int GetVTopRightCoordX() { return m_VWindowWidth; }
	static const int GetVTopRightCoordY() { return 0; }
	static const int GetVBottomLeftCoordX() { return 0; }
	static const int GetVBottomLeftCoordY() { return m_VWindowHeight; }
	static const int GetVBottomRightCoordX() { return m_VWindowWidth; }
	static const int GetVBottomRightCoordY() { return m_VWindowHeight; }
};

