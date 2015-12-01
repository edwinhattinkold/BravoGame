#include "Assets.h"
static Assets* instance;

Assets::Assets()
{
	
}

/* Singleton */
Assets* Assets::getInstance()
{
	if( !instance )
		instance = new Assets();
	return instance;
}

Assets::~Assets()
{
	typedef std::map<Asset, SDL_Texture*>::iterator it_type;
	for( it_type iterator = assetMap.begin(); iterator != assetMap.end(); iterator++ )
	{
		SDL_DestroyTexture( iterator->second );
	}
}

void Assets::insertAssetMapEntry(Asset asset, std::string filePath)
{
	assetMap.insert(std::pair<Asset, SDL_Texture*>(asset, loadTexture(filePath, renderTarget)));
}

void Assets::setRenderTarget( SDL_Renderer* renderTarget )
{
	this->renderTarget = renderTarget;
	insertAssetMapEntry( Asset_Car, "Car/topview.png" );
	insertAssetMapEntry( Asset_MachineGun_Bullet, "Objects/Shooting/machineGun-bullet.png" );
	insertAssetMapEntry( Asset_HowTo, "Mainmenu/howto.png" );
	insertAssetMapEntry( Asset_Menu_Arrow, "Cursor/menuArrow.png" );
	insertAssetMapEntry( Asset_Tree, "Objects/Tree.png" );
	insertAssetMapEntry(Asset_Collectible, "Objects/Collectible.png");
	insertAssetMapEntry( Asset_Tire, "Car/tire.png" );
	insertAssetMapEntry( Asset_HUD, "hud/hud.png" );
	insertAssetMapEntry(Asset_Turret_Calm, "Objects/Turrets/normal_turret_calm.png");
	insertAssetMapEntry(Asset_Turret_Angry, "Objects/Turrets/normal_turret_angry.png");
	insertAssetMapEntry(Asset_Turret_Dead, "Objects/Turrets/normal_turret_destroyed.png");
	insertAssetMapEntry( Asset_Explosion, "Animations/Dying/Explosion/explosion.png" );
	insertAssetMapEntry( Asset_MainMenu_Background, "Mainmenu/background.png" );
}

SDL_Texture* Assets::getAsset( Asset asset )
{
	return assetMap.at( asset );
}

SDL_Texture* Assets::loadTexture( std::string filePath, SDL_Renderer *renderTarget )
{
	filePath = "Images/" + filePath;
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load( filePath.c_str() );
	if( surface == NULL )
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface( renderTarget, surface );
		if( texture == NULL )
			std::cout << "Error" << std::endl;
	}
	SDL_FreeSurface( surface );
	return texture;
}

extern __declspec(dllexport) void Assets_Quit()
{
	delete instance; instance = nullptr;
}
