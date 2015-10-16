#include "Sound.h"
static Sound* instance;

Sound::Sound(){
	this->engine = createIrrKlangDevice();
	if (!engine)
		std::cout << "Sound engine irrKlang failed to start!" << std::endl;
	else
		std::cout << "Sound engine initialisation complete" << std::endl;
	this->startFilePath = "Sounds/";
	this->previousVolume = 1.00f;
}

/* Singleton */
Sound* Sound::getInstance(){
	if (!instance)
		instance = new Sound();
	return instance;
}

void Sound::playSound(std::string file){
	std::string temp = this->startFilePath + file;
	const char *filepath = temp.c_str();
	engine->play2D(filepath, false);
}

void Sound::playSoundLooping(std::string file){
	std::string temp = this->startFilePath + file;
	const char *filepath = temp.c_str();
	engine->play2D(filepath, true);
}

void Sound::playSound(std::string file, ik_f32 volume){
	std::string temp = this->startFilePath + file;
	const char *filepath = temp.c_str();

	ISoundSource* currentSound = engine->addSoundSourceFromFile(filepath);
	currentSound->setDefaultVolume(volume);

	engine->play2D(currentSound, false);
}

void Sound::playSoundLooping(std::string file, ik_f32 volume){
	std::string temp = this->startFilePath + file;
	const char *filepath = temp.c_str();

	ISoundSource* currentSound = engine->addSoundSourceFromFile(filepath);
	currentSound->setDefaultVolume(volume);

	engine->play2D(currentSound, true);
}

void Sound::stopSound(std::string file){
	std::string temp = this->startFilePath + file;
	const char *filepath = temp.c_str();
	engine->removeSoundSource(filepath);
}


void Sound::setVolume(ik_f32 volume){
	engine->setSoundVolume(volume);
}

void Sound::mute(){
	this->previousVolume = this->engine->getSoundVolume();
	this->engine->setSoundVolume(0.00f);
}

void Sound::unmute(){
	this->engine->setSoundVolume(this->previousVolume);
}

