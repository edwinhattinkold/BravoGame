#pragma once
#include <string>
#include <iostream>
#include "Assets.h"
using namespace std;
class Objective
{
private:
	Asset type;
	int collected;
	int total;
public:
	string title;
	Objective( string title, Asset type, int total, int collected = 0 );
	~Objective();
	bool completed();
	void addOne( Asset type );
};