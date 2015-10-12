#pragma once

#include <string>
class MapGenerator
{
public:
	void AddTileSet(std::string filePath, int width, int height, int spacing);
	void GenerateMap(std::string filePath);
	void AddTile(int x, int y, int id);
	MapGenerator();
	~MapGenerator();
};

