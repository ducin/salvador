//// includes

// header file
#include "sabstractgrid.h"

// salvador core
#include "../debug.h"
#include "senums.h"

// C++
#include <string>
#include <fstream>
#include <iostream>

// STL
// none

/** \file sabstractgrid.cpp
 * \brief Plik z kodem źródłowym klasy SAbstractGrid
 *
 * Plik zawiera kod źródłowy klasy SAbstractGrid.
 */

/**
 * Konstruktor abstrakcyjnej siatki. Nie robi nic szczególnego.
 */
SAbstractGrid::SAbstractGrid()
{
	debug("CONSTRUCTOR abstract-grid START\n");
	debug("CONSTRUCTOR abstract-grid END\n");
}

/**
 * Destruktor abstrakcyjnej siatki. Nie robi nic szczególnego.
 */
SAbstractGrid::~SAbstractGrid()
{
	debug("DESTRUCTOR abstract-grid START\n");
	debug("DESTRUCTOR abstract-grid END\n");
}

/**
 * Sprawdza czy punkt o współrzędnych zadanych parametrami mieści się w siatce.
 * @param X odcięta (współrzędna)
 * @param Y rzędna (współrzędna)
 * @return czy punkt o zadanych współrzednych mieści się w siatce
 */
bool SAbstractGrid::pointInsideGrid(int X, int Y)
{
	return ((X < size_x) && (X >= 0) && (Y < size_y) && (Y >= 0));
}

/**
 * Zwraca szerokość siatki (rozmiar współrzędnej x).
 * @return szerokość siatki
 */
int SAbstractGrid::getSizeX()
{
	return size_x;
}

/**
 * Zwraca wysokość siatki (rozmiar współrzędnej y).
 * @return wysokość siatki
 */
int SAbstractGrid::getSizeY()
{
	return size_y;
}
