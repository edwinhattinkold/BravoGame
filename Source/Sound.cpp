#include "Sound.h"
static Sound* instance;

Sound::Sound(){
	engine = createIrrKlangDevice();
	if (!engine)
		std::cout << "Sound engine irrKlang failed to start!" << std::endl;
	else
		std::cout << "Sound engine initialisation complete" << std::endl;
	startFilePath = "Sounds/";
	muted = false;
	previousVolume = 1.00f;
	fadeTickSpeed = 0.02f;

	sounds = new std::map<int, std::string>();
	sounds->insert( std::pair<int, std::string>( Sound_MainMenu_Theme,		"rock_intro.mp3" ) );
	sounds->insert( std::pair<int, std::string>( Sound_MainMenu_Tick,		"menu_tick.wav" ));
	sounds->insert( std::pair<int, std::string>( Sound_MainMenu_Click,		"menu_confirm.wav" ));
	sounds->insert( std::pair<int, std::string>( Sound_Credits_Theme,		"credits_beelzeboss.mp3" ));
	sounds->insert(	std::pair<int, std::string>( Sound_Horn,				"horn.mp3" ));
	sounds->insert( std::pair<int, std::string>( Sound_Engine_Start,		"car_engine.mp3" ));
	sounds->insert( std::pair<int, std::string>( Sound_Engine_Loop,			"engine_loop2.wav" ));
	sounds->insert( std::pair<int, std::string>( Sound_Skid,				"brake2.mp3" ));
	sounds->insert( std::pair<int, std::string>( Sound_Ad,					"ad.mp3" ));
	sounds->insert( std::pair<int, std::string>( Sound_Game_Over,			"game_over.mp3" ));
	sounds->insert( std::pair<int, std::string>( Sound_Game_Over_Applause,	"win_applause.mp3" ));
	sounds->insert( std::pair<int, std::string>( Sound_Game_Over_Win,		"win_theme.mp3" ));
}

/* Singleton */
Sound* Sound::getInstance(){
	if (!instance)
		instance = new Sound();
	return instance;
}

Sound::~Sound(){
	engine->drop();	engine = nullptr;
	delete sounds;	sounds = nullptr;
	instance = nullptr;
}

void Sound::playSound(SoundFiles file){
	std::string temp = startFilePath + sounds->find(file)->second;
	const char *filepath = temp.c_str();
	engine->play2D(filepath, false);
}

void Sound::playSoundLooping(SoundFiles file){
	std::string temp = startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();
	engine->play2D(filepath, true);
}

void Sound::playSound(SoundFiles file, ik_f32 volume){
	std::string temp = startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();

	ISoundSource* currentSound = engine->addSoundSourceFromFile(filepath);
		currentSound->setDefaultVolume(volume);

	engine->play2D(currentSound, false);
}

void Sound::playSoundLooping(SoundFiles file, ik_f32 volume){
	std::string temp = startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();

	ISoundSource* currentSound = engine->addSoundSourceFromFile(filepath);
	currentSound->setDefaultVolume(volume);

	engine->play2D(currentSound, true);
}

void Sound::stopSound(SoundFiles file){
	std::string temp = startFilePath + sounds->find(file)->second;;
	const char *filepath = temp.c_str();
	engine->removeSoundSource(filepath);
}

void Sound::pauseAllSounds()
{
	engine->setAllSoundsPaused( true );
}

void Sound::setVolume(ik_f32 volume){
	if (!muted)
		engine->setSoundVolume(volume);
}

ik_f32 Sound::getVolume(){
	return engine->getSoundVolume();
}

void Sound::mute(){
	previousVolume = engine->getSoundVolume();
	engine->setSoundVolume(0.00f);
	muted = true;
}

void Sound::unmute(){
	muted = false;
	engine->setSoundVolume(previousVolume);
}

void Sound::fadeIn(){
	while (getVolume() != 1.00f){
		fadeInTick();
		SDL_Delay(16);
	}
}

void Sound::fadeOut(){
	while (getVolume() != 0.00f){
		fadeOutTick();
		SDL_Delay(16);
	}
}

void Sound::fadeInTick(){
	if (getVolume() + fadeTickSpeed > 1.00f)
		setVolume(1.00f);
	else
		setVolume(getVolume() + fadeTickSpeed);
}

void Sound::fadeOutTick(){
	if (getVolume() - fadeTickSpeed < 0.00f)
		setVolume(0.00f);
	else
		setVolume(getVolume() - fadeTickSpeed);
}

extern __declspec(dllexport) void Sound_Quit(){
	delete instance; instance = nullptr;
}
