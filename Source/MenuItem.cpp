#include "MenuItem.h"


MenuItem::MenuItem(SDL_Renderer* renderTarget, TTF_Font* font, char* content)
{
	this->content = content;
	myFont = font;
	normalColor = { 140, 0, 0, 255 };
	highlightedColor = { 255, 0, 0, 255 };
	normalTexture = createTextTexture(renderTarget, myFont, content, normalColor);
	highlightedTexture = createTextTexture(renderTarget, myFont, content, highlightedColor);
	currentTexture = normalTexture;
	selected = false;
	SDL_QueryTexture(normalTexture, NULL, NULL, &position.w, &position.h);
}

MenuItem::~MenuItem()
{
	SDL_DestroyTexture(normalTexture);
	SDL_DestroyTexture(highlightedTexture);
	SDL_DestroyTexture(currentTexture);
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

void MenuItem::setColor(SDL_Renderer* renderTarget, Color color){
	SDL_Color newColor;
	switch (color){
		case(Color::Red):
			newColor = { 140, 0, 0, 255 };
			break;
		case(Color::White):
			newColor = { 255, 255, 255, 255 };
			break;
	}
	currentTexture = createTextTexture(renderTarget, myFont, content, newColor);
}

bool MenuItem::checkHover(int x, int y){
	if (x >= position.x && x <= position.x + position.w && y >= position.y && y <= position.y + position.h){
		if (!selected){
			toggleSelected();
			return true;
		}
	}
    else if (selected)
		toggleSelected();
	return false;
}

void MenuItem::toggleSelected(){
	selected = !selected;
	if (selected)
		currentTexture = highlightedTexture;
	else
		currentTexture = normalTexture;
}

void MenuItem::setHighlighted()
{
	currentTexture = highlightedTexture;
}

int MenuItem::getHeight(){
	return position.h;
}

int MenuItem::getWidth(){
	return position.w;
}

int MenuItem::getXPosition(){
	return position.x;
}

int MenuItem::getYPosition(){
	return position.y;
}

void MenuItem::setXPosition(int xPosition){
	position.x = xPosition;
}

void MenuItem::setYPosition(int yPosition){
	position.y = yPosition;
}

void MenuItem::setText(SDL_Renderer* renderTarget, char* text){
	content = text;
	SDL_DestroyTexture(normalTexture);
	SDL_DestroyTexture(highlightedTexture);
	SDL_DestroyTexture(currentTexture);
	normalTexture = createTextTexture(renderTarget, myFont, content, normalColor);
	highlightedTexture = createTextTexture(renderTarget, myFont, content, highlightedColor);
	currentTexture = normalTexture;
	SDL_QueryTexture(normalTexture, NULL, NULL, &position.w, &position.h);
}

void MenuItem::draw(SDL_Renderer* renderTarget){
	SDL_RenderCopy(renderTarget, currentTexture, NULL, &position);
}
