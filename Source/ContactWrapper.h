#pragma once

#include "TDCar.h"
#include "TDTire.h"

enum ContactType { Contact_Car, Contact_Car_Horn, Contact_Bullet, Contact_B2Content };

class ContactWrapper{
private:
	ContactType type;
	void* element;
public:
	ContactWrapper(TDCar* car){
		element = car;
		type = Contact_Car;
	};
	ContactWrapper(TDCar* car, bool horn){
		element = car;
		type = Contact_Car_Horn;
	};
	ContactWrapper(TDTire* car, bool horn){
		element = car;
		type = Contact_Car_Horn;
	};
	ContactWrapper(TDTire* tire){
		element = tire;
		type = Contact_Car;
	};
	ContactWrapper(Projectile* pro){
		element = pro;
		type = Contact_Bullet;
	};
	ContactWrapper(B2Content* content){
		element = content;
		type = Contact_B2Content;
	};
	inline ContactType getContactType(){
		return type;
	};
	inline void* getContactElement(){
		return element;
	}
};