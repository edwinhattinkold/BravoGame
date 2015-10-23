#pragma once

#include "irrklang.h"
#include <iostream>
#include <string>
using namespace irrklang;

class Sound
{
private:
	ISoundEngine* engine;
	std::string startFilePath;
	ik_f32 previousVolume;

	/* Singleton */
	Sound();
	Sound(Sound const&);
	void operator=(Sound const&);

public:
	/* Singleton */
	static Sound* getInstance();

	~Sound();
	void playSound(std::string file);
	void playSoundLooping(std::string file);
	void playSound(std::string file, ik_f32 volume);
	void playSoundLooping(std::string file, ik_f32 volume);
	void stopSound(std::string file);
	void setVolume(ik_f32 volume);
	void mute();
	void unmute();
};

/**
 This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Sound_Quit();