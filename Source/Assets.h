#pragma once
#include <map>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

enum Asset
{
	Asset_Tree,
	Asset_Car,
	Asset_MachineGun_Bullet,
	Asset_HowTo,
	Asset_Menu_Arrow,
	Asset_Tire,
	Asset_Collectible,
	Asset_HUD,
	Asset_Turret_Calm,
	Asset_Turret_Angry,
	Asset_Turret_Dead,
	Asset_Explosion,
	Asset_MainMenu_Background,
	Asset_LoadScreen_Ad,
	Asset_GameOverScreen_Background
};

class Assets
{
private:
	std::map<Asset, SDL_Texture*> assetMap;
	SDL_Renderer* renderTarget;

	/* Singleton */
	Assets();
	Assets( Assets const& );
	void operator=(Assets const&);
	SDL_Texture* loadTexture( std::string filePath, SDL_Renderer *renderTarget );
	void insertAssetMapEntry(Asset, std::string filePath);
public:
	/* Singleton */
	static Assets* getInstance();
	~Assets();

	void setRenderTarget( SDL_Renderer* renderTarget );
	SDL_Texture* getAsset( Asset asset );
};

/**
This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Assets_Quit();

