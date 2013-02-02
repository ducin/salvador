// header file
#include "s_data_image_pointer.h"

//// includes

// salvador core
#include "../debug.h"
#include "s_enums.h"

/** \file sdataimagepointer.cpp
 * \brief Plik z kodem źródłowym klasy SDataImagePointer
 *
 * Plik zawiera kod źródłowy klasy SDataImagePointer.
 */

/**
 * Konstruktor głowicy obrazu danych. Nie robi nic szczególnego.
 */
SDataImagePointer::SDataImagePointer()
{
	debug("CONSTRUCTOR ----- data-image-pointer START\n");
	debug("CONSTRUCTOR ----- data-image-pointer END\n");
}

/**
 * Destruktor głowicy obrazu danych. Nie robi nic szczególnego.
 */
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
void SDataImagePointer::moveLeft()
{
	setDirection(dir_left);
	moveForward(1);
}

/** \brief przesuwa głowicę maszyny danych w prawo
 *
 * Najpierw ustalony jest nowy kierunek ruchu (SDirections) - w prawo, następnie głowica przesuwana jest o jedno pole (w ustalonym kierunku). Efektem przesunięcia głowicy jest zmiana jej współrzędnych względem obrazu danych.
 * \return ?
 */
void SDataImagePointer::moveRight()
{
	setDirection(dir_right);
	moveForward(1);
}
