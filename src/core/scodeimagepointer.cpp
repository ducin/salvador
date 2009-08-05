//// includes

// header file
#include "scodeimagepointer.h"

// salvador core
#include "../debug.h"
#include "senums.h"

// C++
#include <string>

// STL
// none

SCodeImagePointer::SCodeImagePointer()
{
	debug("CONSTRUCTOR ----- code-image-pointer START\n");

	debug("CONSTRUCTOR ----- code-image-pointer END\n");
}

SCodeImagePointer::~SCodeImagePointer()
{
	debug("DESTRUCTOR ----- code-image-pointer START\n");

	debug("DESTRUCTOR ----- code-image-pointer END\n");
}

void SCodeImagePointer::turnUp()
{
	direction = dir_up;
}

void SCodeImagePointer::turnDown()
{
	direction = dir_down;
}

void SCodeImagePointer::turnLeft()
{
	direction = dir_left;
}

void SCodeImagePointer::turnRight()
{
	direction = dir_right;
}
