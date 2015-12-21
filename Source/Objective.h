#pragma once
#include <string>
#include <iostream>
using namespace std;
class Objective
{
private:
	string type;
	int collected;
	int total;
public:
	string title;
	Objective(string title, string type, int total, int collected = 0);
	~Objective();
	bool completed();
	void addOne( string type );
};