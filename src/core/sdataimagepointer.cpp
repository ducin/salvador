// header file
#include "sdataimagepointer.h"

//// includes

// salvador core
#include "../debug.h"
#include "senums.h"

SDataImagePointer::SDataImagePointer()
{
	debug("CONSTRUCTOR ----- data-image-pointer START\n");

	debug("CONSTRUCTOR ----- data-image-pointer END\n");
}

SDataImagePointer::~SDataImagePointer()
{
	debug("DESTRUCTOR ----- data-image-pointer START\n");

	debug("DESTRUCTOR ----- data-image-pointer END\n");
}

/** \brief przesuwa głowicę maszyny danych w lewo
 *
 * Najpierw ustalony jest nowy kierunek ruchu (SDirections) - w lewo, następnie głowica przesuwana jest o jedno pole (w ustalonym kierunku). Efektem przesunięcia głowicy jest zmiana jej współrzędnych względem obrazu danych.
 * \return ?
 */
int SDataImagePointer::moveLeft()
{
	setDirection(dir_left);
	moveForward(1);
// TODO return
}

/** \brief przesuwa głowicę maszyny danych w prawo
 *
 * Najpierw ustalony jest nowy kierunek ruchu (SDirections) - w prawo, następnie głowica przesuwana jest o jedno pole (w ustalonym kierunku). Efektem przesunięcia głowicy jest zmiana jej współrzędnych względem obrazu danych.
 * \return ?
 */
int SDataImagePointer::moveRight()
{
	setDirection(dir_right);
	moveForward(1);
// TODO return
}
