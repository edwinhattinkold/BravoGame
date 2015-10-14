#pragma once
#include <string>;
#include "MapGenerator.h";
#include "rapidxml.hpp";
#include "rapidxml_utils.hpp";
#include "Location.h";

class MapGenerator;

class XMLReader
{
public:
	XMLReader();
	~XMLReader();
	std::vector<Location>* parseXMLFile(MapGenerator *mapGenerator, std::string filePath);
};

