#include "Chunk.h"

SDL_Texture* LoadImage(SDL_Renderer *renderTarget, std::string filePath){
	filePath = filePath.substr(3);
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error1" << filePath << std::endl;
	else {
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error2" << std::endl;
		SDL_FreeSurface(surface);
		return texture;
	}
}

Chunk::Chunk(SDL_Renderer *rt, std::string filePath)
{
	renderTarget = rt;
	textures = new std::vector<SDL_Texture*>();
	tiles = new std::vector<Tile*>();
	tiles->push_back(nullptr);
	locations = new std::vector<Location>();
	//create holder and definitions for box2d
	bodies = new std::vector<b2Body>();
	collisionBodyDef = new b2BodyDef();
	collisionBodyDef->type = b2_staticBody;
	collisionBodyDef->angle = 0;
	collisionFixtureDef = new b2FixtureDef();
	boxShape = new b2PolygonShape();
	boxShape->SetAsBox(1, 1);
	collisionFixtureDef->shape = boxShape;
	collisionFixtureDef->density = 1;
	XMLReader reader;
	reader.parseXMLFile(this, filePath);
}

Chunk::~Chunk()
{
	for (size_t i = 1; i < tiles->size(); i++){
		delete tiles->at(i);
		tiles->at(i) = nullptr;
	}
	for (size_t j = 0; j < textures->size(); j++){
		SDL_DestroyTexture(textures->at(j));
		textures->at(j) = nullptr;
	}
	delete tiles;
	tiles = nullptr;
	delete textures;
	textures = nullptr;
	delete locations;
	locations = nullptr;
	/*delete bodies;*/
	delete collisionBodyDef;
	collisionBodyDef = nullptr;
	delete collisionFixtureDef;
	collisionFixtureDef = nullptr;
	delete boxShape;
	boxShape = nullptr;
}

void Chunk::AddTileSet(std::string filePath, int spacing, int firstId, int amount, int width, int height)
{
	
	SDL_Texture  *texture = LoadImage(renderTarget, filePath);
	//save pointer for removing
	textures->push_back(texture);
	int x = 0;
	int y = 0;
	for (int c = 0; c < amount; c++){
		SDL_Rect cropRect;
		cropRect.h = 32;
		cropRect.w = 32;
		cropRect.x = x;
		cropRect.y = y;
		x += spacing + 32;
		
		tiles->push_back(new Tile(texture, cropRect));
		if (x + 32 > width){
			x = 0;
			y += spacing + 32;
		}
	}
}

void Chunk::AddCollidableObject(int x, int y){
	//collisionBodyDef->position.Set(x * 2, y * 3);
	//b2Body staticBody = m_world->CreateBody(collisionBodyDef);
	//staticBody.CreateFixture(collisionFixtureDef);
	//bodies->push_back(staticBody);
}

void Chunk::AddLocation(Location l){
	locations->push_back(l);
}

void Chunk::Draw(int x, int y, SDL_Rect *cameraRect){
	Tile *tile = nullptr;
	SDL_Rect tarRect = { 0, 0, 32, 32 };
	for (int i = 0; i < locations->size(); i++){
	Location l = locations->at(i);
	tarRect.x = l.x * 32 + x - cameraRect->x;
	tarRect.y = l.y * 32 + y - cameraRect->y;
	tile = tiles->at(l.id);;
	SDL_RenderCopy(renderTarget, tile->getTexture(), tile->getRect(), &tarRect);
	}
}