#include "Sound.h"

Sound::Sound(SDL_Window **pWindow, bool *pRuning)
{
	m_Window = pWindow;
	m_Running = pRuning;
}

Sound::~Sound()
{
	for (auto &ptr : m_Music)
	{
		Mix_FreeMusic(ptr.second);
		ptr.second = nullptr;
	}
	m_Music.clear();

	for (auto &ptr : m_Sound)
	{
		Mix_FreeChunk(ptr.second);
		ptr.second = nullptr;
	}
	m_Sound.clear();
}

const bool Sound::LoadMusic(const string &path, const string &id)
{
	m_Music[id] = Mix_LoadMUS(path.c_str());
	if (m_Music[id] == nullptr)
		System::ShowErrorMessage("Music load fail", path, m_Running, *m_Window);

	Mix_VolumeMusic(100);
	return true;
}

const bool Sound::LoadSound(const string &path, const string &id)
{
	m_Sound[id] = Mix_LoadWAV(path.c_str());
	if (m_Sound[id] == nullptr)
		System::ShowErrorMessage("Sound load fail", path, m_Running, *m_Window);

	return true;
}

void Sound::StopMusic()
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
}

const bool Sound::MusicIsPlaying()
{
	if (Mix_PlayingMusic() == 0)
		return false;
	else return true;
}

void Sound::ResumeMusic()
{
	Mix_ResumeMusic();
}

void Sound::PauseMusic()
{
	Mix_PauseMusic();
}


void Sound::PlayMusic(Mix_Music *pMusic)
{
	//  If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//  Play the music
		Mix_PlayMusic(pMusic, -1);
	}
	////  If music is being played
	//else
	//{
	//	//  If the music is paused
	//	if (Mix_PausedMusic() == 1)
	//	{
	//		//  Resume the music
	//		Mix_ResumeMusic();
	//	}
	//	//  If the music is playing
	//	else
	//	{
	//		//  Pause the music
	//		Mix_PauseMusic();
	//	}
	//}
}

void Sound::PlaySound(Mix_Chunk *pSound, const int &channel, const bool &loop)
{
	if (!SoundIsPlaying(channel))return;

	//	Play the sound;
	if (loop == true)
		Mix_PlayChannel(channel, pSound, -1);
	else
		Mix_PlayChannel(channel, pSound, 0);
}

void Sound::StopSound(const int &channel)
{
	if (Mix_Playing(channel))
		Mix_HaltChannel(channel);
}

const bool Sound::SoundIsPlaying(const int &channel)
{
	if (Mix_Playing(channel) == 0)
		return true;
	else return false;
}

void Sound::ResumeSound(const int &channel)
{
	Mix_Resume(channel);
}

void Sound::PauseSound(const int &channel)
{
	Mix_Pause(channel);
}

