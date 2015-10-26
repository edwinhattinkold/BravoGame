#pragma once
#include <string>;
#include "Chunk.h";
#include "rapidxml.hpp";
#include "rapidxml_utils.hpp";
#include "Location.h";

class Chunk;

class XMLReader
{
public:
	XMLReader();
	~XMLReader();
	void parseXMLFile(Chunk *chunk, std::string filePath);
};

