#include "MenuItem.h"


MenuItem::MenuItem(SDL_Renderer* renderTarget, TTF_Font* font, char* content)
{
	this->content = content;
	this->normalColor = { 140, 0, 0, 255 };
	this->highlightedColor = { 255, 0, 0, 255 };
	this->normalTexture = createTextTexture(renderTarget, font, this->content, this->normalColor);
	this->highlightedTexture = createTextTexture(renderTarget, font, this->content, this->highlightedColor);
	this->currentTexture = this->normalTexture;
	this->selected = false;
	SDL_QueryTexture(this->normalTexture, NULL, NULL, &position.w, &position.h);
}

MenuItem::~MenuItem()
{
	SDL_DestroyTexture(this->normalTexture);
	SDL_DestroyTexture(this->highlightedTexture);
}

SDL_Texture* MenuItem::createTextTexture(SDL_Renderer* renderTarget, TTF_Font* font, const char* text, SDL_Color color){
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_FreeSurface(textSurface);
	return textTexture;
}

void MenuItem::setPosition(SDL_Rect position){
	this->position = position;
}

void MenuItem::checkHover(int x, int y){
	if (x >= this->position.x && x <= this->position.x + this->position.w && y >= this->position.y && y <= this->position.y + this->position.h){
		if (!this->selected)
			this->toggleSelected();
	}
    else if (this->selected)
		this->toggleSelected();
}

void MenuItem::toggleSelected(){
	this->selected = !this->selected;
	if (this->selected)
		this->currentTexture = this->highlightedTexture;
	else
		this->currentTexture = this->normalTexture;
}

int MenuItem::getHeight(){
	return this->position.h;
}

int MenuItem::getWidth(){
	return this->position.w;
}

int MenuItem::getXPosition(){
	return this->position.x;
}

int MenuItem::getYPosition(){
	return this->position.y;
}

void MenuItem::setXPositon(int xPosition){
	this->position.x = xPosition;
}

void MenuItem::setYPosition(int yPosition){
	this->position.y = yPosition;
}

void MenuItem::draw(SDL_Renderer* renderTarget){
	SDL_RenderCopy(renderTarget, this->currentTexture, NULL, &this->position);
}
