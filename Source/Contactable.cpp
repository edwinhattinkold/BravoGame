#include "Contactable.h"
#include "B2Content.h"
#include "Radar.h"
Contactable::Contactable(B2Content* obj){
	object = obj;
	objectType = Type_B2Content;
}

Contactable::Contactable(Radar* radar){
	object = radar;
	objectType = Type_Radar;
}

Contactable::~Contactable(){

}