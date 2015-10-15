#ifndef SOUND_IRRKLANG_H
#define SOUND_IRRKLANG_H

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
	static Sound* getInstance();
	void playSound(std::string file);
	void playSoundLooping(std::string file);
	void playSound(std::string file, ik_f32 volume);
	void playSoundLooping(std::string file, ik_f32 volume);
	void setVolume(ik_f32 volume);
	void mute();
	void unmute();
};

#endif

