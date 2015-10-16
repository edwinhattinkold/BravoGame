#include "XMLReader.h"


XMLReader::XMLReader()
{
}


XMLReader::~XMLReader()
{
}

std::vector<Location>* XMLReader::parseXMLFile(MapGenerator *mapGenerator, std::string filePath)
{
	rapidxml::file<> xmlFile(filePath.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *map = doc.first_node();
	for (rapidxml::xml_node<> *tileset = map->first_node("tileset");
		tileset; tileset = tileset->next_sibling("tileset"))
	{
		int spacing = 0;
		if (tileset->first_attribute("spacing") != nullptr){
			spacing = atoi(tileset->first_attribute("spacing")->value());
		}
		rapidxml::xml_node<> *image = tileset->first_node("image");
		mapGenerator->AddTileSet(image->first_attribute("source")->value(),
			spacing,
			atoi(tileset->first_attribute("firstgid")->value()),
			atoi(tileset->first_attribute("tilecount")->value()),
			atoi(image->first_attribute("width")->value()),
			atoi(image->first_attribute("height")->value()));
	}

	//return tiles
	std::vector<Location> *locations = new std::vector<Location>();
	//find layers
	for (rapidxml::xml_node<> *layer = map->first_node("layer"); layer; layer = layer->next_sibling("layer"))
	{
		int x = std::stoi(layer->first_attribute("width")->value());
		int y = std::stoi(layer->first_attribute("height")->value());
		std::cout << x;
		int currentX = 0;
		int currentY = 0;
		rapidxml::xml_node<> *layerdata = layer->first_node("data");
		for (rapidxml::xml_node<> *tile = layerdata->first_node("tile"); tile; tile = tile->next_sibling("tile"))
		{
			locations->push_back(Location(currentX, currentY, atoi(tile->first_attribute("gid")->value())));
			currentX++;
			if (currentX >= x){
				currentX = 0;
				currentY++;
				if (currentY > y){
					std::cout << "WARNING to manny tiles" << std::endl;
				}
			}
		}
		return locations;
	}
}
