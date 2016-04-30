#pragma once
#include "Source.h"
#include "System.h"


class Sound
{
private:
	/// <summary>
	/// Pointer to SDL window from @Game class.
	/// </summary>
	SDL_Window **m_Window;

	/// <summary>
	/// Pointer to running boolean from @Game class.
	/// </summary>
	bool *m_Running;

public:
	Sound(){}
	/// <summary>
	/// Initializes a new instance of the <see cref="Sound"/> class.
	/// </summary>
	/// <param name="pWindow">Pointer to main SDL_Window of game.</param>
	/// <param name="pRuning">Pointer to main boolean running of game.</param>
	Sound(SDL_Window **pWindow, bool *pRuning);
	 ~Sound();

private:
	/// <summary>
	/// Store music format.
	/// </summary>
	map<string, Mix_Music*> m_Music;

	/// <summary>
	/// Store sound format.
	/// </summary>
	map<string, Mix_Chunk*> m_Sound;

public:
	/// <summary>
	/// Loading music into @m_Music.
	/// </summary>
	/// <param name="path">Path to locate music.</param>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	const bool LoadMusic(const string &path, const string &id);

	/// <summary>
	/// Loading sound into @m_Sound.
	/// </summary>
	/// <param name="path">Path to locate music.</param>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	const bool LoadSound(const string &path, const string &id);

	/// <summary>
	/// Stops the music.
	/// </summary>
	void StopMusic();

	/// <summary>
	/// Check if music is playing.
	/// </summary>
	/// <returns></returns>
	const bool MusicIsPlaying();

	/// <summary>
	/// Resume music.
	/// </summary>
	void ResumeMusic();

	/// <summary>
	/// Pauses the music.
	/// </summary>
	void PauseMusic();

	/// <summary>
	/// Play selected music.
	/// </summary>
	/// <param name="pMusic">Pointer to music.</param>
	void PlayMusic(Mix_Music *pMusic);


	/// <summary>
	/// Plays selected sound.
	/// </summary>
	/// <param name="pSound">Pointer to sound file.</param>
	/// <param name="channel">channel.</param>
	/// <param name="loop">If true it will loop forever.</param>
	void PlaySound(Mix_Chunk *pSound, const int &channel, const bool &loop);

	/// <summary>
	/// Stop the sound.
	/// </summary>
	/// <param name="channel">The channel.</param>
	void StopSound(const int & channel);

	/// <summary>
	/// Check if sound is playing
	/// </summary>
	/// <param name="channel">The channel.</param>
	/// <returns></returns>
	const bool SoundIsPlaying(const int & channel);

	/// <summary>
	/// Resume sound.
	/// </summary>
	/// <param name="channel">The channel.</param>
	void ResumeSound(const int & channel);

	/// <summary>
	/// Pause the sound.
	/// </summary>
	/// <param name="channel">The channel.</param>
	void PauseSound(const int & channel);


	/// <summary>
	/// Get the pointer to music.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	inline Mix_Music *GetPointerToMusic(const string &id) { return m_Music[id]; }

	/// <summary>
	/// Get the pointer to sound.
	/// </summary>
	/// <param name="id">The identifier.</param>
	/// <returns></returns>
	inline Mix_Chunk *GetPointerToSound(const string &id) { return m_Sound[id]; }
};

