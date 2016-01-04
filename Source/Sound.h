#pragma once
#include "irrklang.h"
#include <iostream>
#include <string>
#include <map>
#include <SDL.h>

using namespace irrklang;
enum SoundFiles {	Sound_MainMenu_Theme, 
					Sound_MainMenu_Tick, 
					Sound_MainMenu_Click, 
					Sound_Credits_Theme,
					Sound_Horn,
					Sound_Engine_Start,
					Sound_Engine_Loop,
					Sound_Skid,
					Sound_Level_Desert,
					Sound_Level_Snow,
					Sound_Level_Jungle,
					Sound_Ad,
					Sound_Game_Over,
					Sound_Game_Over_Applause,
					Sound_Game_Over_Win
};

class Sound
{
	
private:
	ISoundEngine* engine;
	std::string startFilePath;
	ik_f32 previousVolume;
	std::map<int, std::string>* sounds;
	ik_f32 fadeTickSpeed;
	bool muted;

	/* Singleton */
	Sound();
	Sound(Sound const&);
	void operator=(Sound const&);
	

public:
	/* Singleton */
	static Sound* getInstance();

	~Sound();
	void playSound(SoundFiles file);
	void playSoundLooping(SoundFiles file);
	void playSound(SoundFiles file, ik_f32 volume);
	void playSoundLooping(SoundFiles file, ik_f32 volume);
	void stopSound(SoundFiles file);
	void pauseAllSounds();
	void setVolume(ik_f32 volume);
	ik_f32 getVolume();
	void mute();
	void unmute();
	void fadeIn();
	void fadeOut();
	void fadeInTick();
	void fadeOutTick();
};

/**
 This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Sound_Quit();