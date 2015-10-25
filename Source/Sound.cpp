#include "Sound.h"
static Sound* instance;

Sound::Sound(){
	this->engine = createIrrKlangDevice();
	if (!engine)
		std::cout << "Sound engine irrKlang failed to start!" << std::endl;
	else
		std::cout << "Sound engine initialisation complete" << std::endl;
	this->startFilePath = "Sounds/";
	this->muted = false;
	this->previousVolume = 1.00f;
	this->fadeTickSpeed = 0.01f;

	this->sounds = new std::map<int, std::string>();
	this->sounds->insert( std::pair<int, std::string>( Sound_MainMenu_Theme,	"rock_intro.mp3" ) );
	this->sounds->insert( std::pair<int, std::string>( Sound_MainMenu_Tick,		"menu_tick.wav" ));
	this->sounds->insert( std::pair<int, std::string>( Sound_MainMenu_Click,	"menu_confirm.wav" ));
	this->sounds->insert( std::pair<int, std::string>( Sound_Credits_Theme,		"credits_beelzeboss.mp3" ));
}

/* Singleton */
Sound* Sound::getInstance(){
	if (!instance)
		instance = new Sound();
	return instance;
}

Sound::~Sound(){
	this->engine->drop();	this->engine = nullptr;
	delete this->sounds;	this->sounds = nullptr;
	instance = nullptr;
}

void Sound::playSound(SoundFiles file){
	std::string temp = this->startFilePath + sounds->find(file)->second;
	const char *filepath = temp.c_str();
	engine->play2D(filepath, false);
}

void Sound::playSoundLooping(SoundFiles file){
	std::string temp = this->startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();
	engine->play2D(filepath, true);
}

void Sound::playSound(SoundFiles file, ik_f32 volume){
	std::string temp = this->startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();

	ISoundSource* currentSound = engine->addSoundSourceFromFile(filepath);
	currentSound->setDefaultVolume(volume);

	engine->play2D(currentSound, false);
}

void Sound::playSoundLooping(SoundFiles file, ik_f32 volume){
	std::string temp = this->startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();

	ISoundSource* currentSound = engine->addSoundSourceFromFile(filepath);
	currentSound->setDefaultVolume(volume);

	engine->play2D(currentSound, true);
}

void Sound::stopSound(SoundFiles file){
	std::string temp = this->startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();
	engine->removeSoundSource(filepath);
}


void Sound::setVolume(ik_f32 volume){
	if (!muted)
		this->engine->setSoundVolume(volume);
}

ik_f32 Sound::getVolume(){
	return this->engine->getSoundVolume();
}

void Sound::mute(){
	this->previousVolume = this->engine->getSoundVolume();
	this->engine->setSoundVolume(0.00f);
	this->muted = true;
}

void Sound::unmute(){
	this->muted = false;
	this->engine->setSoundVolume(this->previousVolume);
	
}

void Sound::fadeIn(){
	SDL_Event ev;
	while (this->getVolume() != 1.00f){
		while (SDL_PollEvent(&ev)); //Keep the application responsive
		this->fadeInTick();
		SDL_Delay(16);
	}
}

void Sound::fadeOut(){
	SDL_Event ev;
	while (this->getVolume() != 0.00f){
		while (SDL_PollEvent(&ev)); //Keep the application responsive
		this->fadeOutTick();
		SDL_Delay(16);
	}
}

void Sound::fadeInTick(){
	if (this->getVolume() + this->fadeTickSpeed > 1.00f)
		this->setVolume(1.00f);
	else
		this->setVolume(this->getVolume() + this->fadeTickSpeed);
}

void Sound::fadeOutTick(){
	if (this->getVolume() - this->fadeTickSpeed < 0.00f)
		this->setVolume(0.00f);
	else
		this->setVolume(this->getVolume() - this->fadeTickSpeed);
}

extern __declspec(dllexport) void Sound_Quit(){
	delete Sound::getInstance();
}
