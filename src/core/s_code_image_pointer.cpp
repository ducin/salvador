//// includes

// header file
#include "s_code_image_pointer.h"

// salvador core
#include "../debug.h"
#include "s_enums.h"

// C++
#include <string>

// STL
// none

/** \file scodeimagepointer.cpp
 * \brief Plik z kodem źródłowym klasy SCodeImagePointer
 *
 * Plik zawiera kod źródłowy klasy SCodeImagePointer.
 */

/**
 * Konstruktor głowicy obrazu kodu. Nie robi nic szczególnego.
 */
SCodeImagePointer::SCodeImagePointer()
{
	debug("CONSTRUCTOR ----- code-image-pointer START\n");
	debug("CONSTRUCTOR ----- code-image-pointer END\n");
}

/**
 * Destruktor głowicy obrazu kodu. Nie robi nic szczególnego.
 */
SCodeImagePointer::~SCodeImagePointer()
{
	debug("DESTRUCTOR ----- code-image-pointer START\n");
	debug("DESTRUCTOR ----- code-image-pointer END\n");
}

/**
 * Ustawia kierunek poruszania się głowicy kodu na górę.
 */
void SCodeImagePointer::turnUp()
{
	direction = dir_up;
}

/**
 * Ustawia kierunek poruszania się głowicy kodu na dół.
 */
void SCodeImagePointer::turnDown()
{
	direction = dir_down;
}

/**
 * Ustawia kierunek poruszania się głowicy kodu na lewo.
 */
void SCodeImagePointer::turnLeft()
{
	direction = dir_left;
}

/**
 * Ustawia kierunek poruszania się głowicy kodu na prawo.
 */
void SCodeImagePointer::turnRight()
{
	direction = dir_right;
}
