/* File : PylonOpenCvSwingWrapper.cxx */

#include "PylonOpenCvSwingWrapper.h"

Shape::Shape(int aX)
	:x(aX)
{
}

int Shape::getX()
{
	return x;
}

void Shape::setX(int aX)
{
	x = aX;
}
