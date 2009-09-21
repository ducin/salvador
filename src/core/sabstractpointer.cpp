// header file
#include "sabstractpointer.h"

//// includes

// salvador core
#include "../debug.h"
#include "senums.h"

// C++
#include <iostream>
#include <fstream>
#include <string>

// STL

/** \file sabstractpointer.cpp
 * \brief Plik z kodem źródłowym klasy SAbstractPointer
 *
 * Plik zawiera kod źródłowy klasy SAbstractPointer.
 */

/**
 * Konstruktor głowicy abstrakcyjnej. Ustala atrybuty głowicy (współrzędne, kierunek poruszania itp.) na wartości domyślne.
 */
 SAbstractPointer::SAbstractPointer()
{
	debug("CONSTRUCTOR ----* abstract-pointer START\n");
	clear(); // ustawienie współrzędnych i kierunku poruszania na wartości domyślne
	debug("CONSTRUCTOR ----* abstract-pointer END\n");
}

/**
 * Destruktor głowicy abstrakcyjnej. Nie robi nic szczególnego.
 */
SAbstractPointer::~SAbstractPointer()
{
	debug("DESTRUCTOR ----* abstract-pointer START\n");
	debug("DESTRUCTOR ----* abstract-pointer END\n");
}

void SAbstractPointer::setDirection(SDirections dir)
{
	direction = dir;
}

int SAbstractPointer::getCoordX()
{
	return coord_x;
}

int SAbstractPointer::getCoordY()
{
	return coord_y;
}

void SAbstractPointer::moveForward(int count)
{
	switch(direction)
	{
		case dir_up:
			coord_y -= count;
			break;
		case dir_right:
			coord_x += count;
			break;
		case dir_down:
			coord_y += count;
			break;
		case dir_left:
			coord_x -= count;
			break;
	}
}

void SAbstractPointer::clear()
{
	coord_x = INIT_coord_x;
	coord_y = INIT_coord_y;
	direction = INIT_direction;
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

std::string SAbstractPointer::__dev__transformBinaryDirectionToString(SDirections dir)
{
	switch(dir)
	{
		case dir_up:
			return "up";
		case dir_right:
			return "right";
		case dir_down:
			return "down";
		case dir_left:
			return "left";
		default:
			return "error";
	}
}

void SAbstractPointer::__dev__printConsoleCoords()
{
	std::cout << "[X:" << coord_x << ", Y:" << coord_y << "] [DIR:" << __dev__transformBinaryDirectionToString(direction) << "]";
}

