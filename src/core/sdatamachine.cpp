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

void SDataMachine::clearData()
{
	// ?
}

int SDataMachine::getPointedValue()
{
	return grid->getValueAt(pointer->getCoordX(), pointer->getCoordY());
}

void SDataMachine::pushPointer()
{
	pointer->moveForward(1);
}

/*==================================================================*/
/*                                                                  */
/*                 INSTRUCTION EXECUTION PART                       */
/*                                                                  */
/*==================================================================*/

void SDataMachine::executeTurnLeft()
{
	(dynamic_cast<SDataImagePointer *> (pointer))->moveLeft();
}

void SDataMachine::executeTurnRight()
{
	(dynamic_cast<SDataImagePointer *> (pointer))->moveRight();
}

void SDataMachine::executeZero()
{
	(dynamic_cast<SDataGrid *> (grid))->performZeroAt(pointer->getCoordX(), pointer->getCoordY());
}

void SDataMachine::executeSucc()
{
	(dynamic_cast<SDataGrid *> (grid))->performSuccAt(pointer->getCoordX(), pointer->getCoordY());
}

void SDataMachine::executePred()
{
	(dynamic_cast<SDataGrid *> (grid))->performPredAt(pointer->getCoordX(), pointer->getCoordY());
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

void SDataMachine::__dev__initGrid()
{
	grid = new SDataGrid();
}

void SDataMachine::__dev__destroyGrid()
{
	(dynamic_cast<SDataGrid *> (grid))->~SDataGrid();
//	grid->~SDataGrid();
}

/////////////////////////

void SDataMachine::__dev__printGrid()
{
//	debug("dev print code grid START\n");
	grid->__dev__printConsole(pointer->getCoordX(),pointer->getCoordY());
//	debug("dev print code grid END\n");
}

void SDataMachine::__dev__printPointer()
{
//	debug("dev print pointer START\n");
	pointer->__dev__printConsoleCoords();
//	debug("dev print pointer END\n");
}

void SDataMachine::__dev__printConsole()
{
//	__dev__printPointer();
	__dev__printGrid();
}

