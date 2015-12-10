#pragma once;
class Radar;
class B2Content;

enum ObjectType { Type_B2Content, Type_Radar};

class Contactable{
private:
	ObjectType objectType;
	void* object;
public:
	Contactable(B2Content* obj);
	Contactable(Radar* radar);
	~Contactable();
	inline int getType(){
		return objectType;
	}
	inline void* getObject(){
		return object;
	}
};