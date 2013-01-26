//// includes

// header file
#include "sdatamachine.h"

// salvador core
#include "../debug.h"
#include "senums.h"
#include "sdatagrid.h"

// C++
#include <string>
#include <iostream>

// STL
// none

/** \file sdatamachine.cpp
 * \brief Plik z kodem źródłowym klasy SDataMachine
 *
 * Plik zawiera kod źródłowy klasy SDataMachine.
 */

/** \brief konstruktor
 *
 * Tworzy 3 obiekty, do których ma zapisane referencje:
 *   - log operacji maszyny danych (SDataStats)
 *   - obraz danych (SDataImage)
 *   - głowica maszyny danych (SDataImagePointer)
 * Maszyna danych w trakcie swojego działania będzie z nich cały czas korzystać
 */
SDataMachine::SDataMachine()
// constructor
{
	debug("CONSTRUCTOR --- data-machine START\n");
	pointer = new SDataImagePointer();
	debug("CONSTRUCTOR --- data-machine END\n");
}

/** \brief destruktor
 *
 * Niszczy 3 obiekty, niezbędne do działania maszyny:
 *   - log operacji maszyny danych (SDataStats)
 *   - obraz danych (SDataImage)
 *   - głowica maszyny danych (SDataImagePointer)
 */
SDataMachine::~SDataMachine()
// destructor
{
	debug("DESTRUCTOR --- data-machine START\n");
// śmierdzące rozwiązanie z C
// ((SDataImagePointer*) pointer)->~SDataImagePointer();
	(dynamic_cast<SDataImagePointer *> (pointer))->~SDataImagePointer();
	debug("DESTRUCTOR --- data-machine END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void SDataMachine::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Czyści dane przechowywane przez maszynę danych.
 */
void SDataMachine::clearData()
{
	(dynamic_cast<SDataGrid *> (grid))->clear();
}

/**
 * Zwraca wartość wskazywaną przez głowicę danych na obrazie danych.
 * @return wartość wskazywana przez głowicę
 */
int SDataMachine::getPointedValue()
{
	return grid->getValueAt(pointer->getCoordX(), pointer->getCoordY());
}

/**
 * Przesuwa głowicę danych o jedną komórkę w bieżącym kierunku.
 * @return czy się udało; w przypadku maszyny danych zawsze się udaje
 */
bool SDataMachine::pushPointer()
{
	pointer->moveForward(1);
	return true;
}

/////////////////////////

/**
 * Inicjuje siatkę danych.
 */
void SDataMachine::initGrid()
{
	grid = new SDataGrid();
}

/**
 * Niszczy siatkę danych.
 */
void SDataMachine::destroyGrid()
{
	(dynamic_cast<SDataGrid *> (grid))->~SDataGrid();
//	grid->~SDataGrid();
}

/*==================================================================*/
/*                                                                  */
/*                 INSTRUCTION EXECUTION PART                       */
/*                                                                  */
/*==================================================================*/

/**
 * Wykonuje instrukcję Salvadora PRZESUŃ GŁOWICĘ DANYCH W LEWO.
 */
void SDataMachine::executeTurnLeft()
{
	(dynamic_cast<SDataImagePointer *> (pointer))->moveLeft();
}

/**
 * Wykonuje instrukcję Salvadora PRZESUŃ GŁOWICĘ DANYCH W PRAWO.
 */
void SDataMachine::executeTurnRight()
{
	(dynamic_cast<SDataImagePointer *> (pointer))->moveRight();
}

/**
 * Wykonuje instrukcję Salvadora ZERUJ.
 */
void SDataMachine::executeZero()
{
	(dynamic_cast<SDataGrid *> (grid))->performZeroAt(pointer->getCoordX(), pointer->getCoordY());
}

/**
 * Wykonuje instrukcję Salvadora ZWIĘKSZ.
 */
void SDataMachine::executeSucc()
{
	(dynamic_cast<SDataGrid *> (grid))->performSuccAt(pointer->getCoordX(), pointer->getCoordY());
}

/**
 * Wykonuje instrukcję Salvadora ZMNIEJSZ.
 */
void SDataMachine::executePred()
{
	(dynamic_cast<SDataGrid *> (grid))->performPredAt(pointer->getCoordX(), pointer->getCoordY());
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

/**
 * METODA TESTOWA. Wyświetla zawartość siatki danych.
 */
void SDataMachine::__dev__printGrid()
{
//	debug("dev print code grid START\n");
	grid->__dev__printConsole(pointer->getCoordX(),pointer->getCoordY());
//	debug("dev print code grid END\n");
}

/**
 * METODA TESTOWA. Wyświetla informacje o głowicy maszyny danych.
 */
void SDataMachine::__dev__printPointer()
{
//	debug("dev print pointer START\n");
	pointer->__dev__printConsoleCoords();
//	debug("dev print pointer END\n");
}

/**
 * METODA TESTOWA. Wyświetla informacje o maszynie danych.
 */
void SDataMachine::__dev__printConsole()
{
//	__dev__printPointer();
	__dev__printGrid();
}

