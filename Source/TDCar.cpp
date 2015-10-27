#include "TDCar.h"


void TDCar::accept(DrawVisitor *dv)
{
	dv->visit(this);
}
