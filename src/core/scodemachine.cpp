//// includes

// header file
#include "scodemachine.h"

// salvador core
#include "../debug.h"
#include "senums.h"
#include "scodeimage.h"
#include "scodeimagepointer.h"

// C++
#include <string>
#include <iostream>

// STL
// none

/** \file scodemachine.cpp
 * \brief Plik z kodem źródłowym klasy SCodeMachine
 *
 * Plik zawiera kod źródłowy klasy SCodeMachine.
 */

/**
 * Konstruktor maszyny kodu. Tworzy obiekty głowicy obrazu kodu oraz sam obraz kodu.
 */
SCodeMachine::SCodeMachine(SCodeTypes CODE_TYPE)
{
	debug("CONSTRUCTOR --- code-machine START\n");
	code_type = CODE_TYPE;
	image = new SCodeImage();
	pointer = new SCodeImagePointer();
	debug("CONSTRUCTOR --- code-machine END\n");
}

/**
 * Destruktor maszyny kodu. Niszczy obiekty głowicy obrazu kodu oraz sam obraz kodu.
 */
SCodeMachine::~SCodeMachine()
{
	debug("DESTRUCTOR --- code-machine START\n");
	image->~SCodeImage();
// "śmierdzące" rozwiązanie z C
// ((SCodeImagePointer*) pointer)->~SCodeImagePointer();
	(dynamic_cast<SCodeImagePointer *> (pointer))->~SCodeImagePointer();
	debug("DESTRUCTOR --- code-machine END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void SCodeMachine::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Zwraca instrukcję na jaką wskazuje głowica obrazu kodu.
 * @return instrukcja wskazywana przez głowicę
 */
SInstructions SCodeMachine::getPointedInstruction()
{
	SInstructions result = (SInstructions) grid->getValueAt(pointer->getCoordX(), pointer->getCoordY());
	return result;
}

void SCodeMachine::pushPointer()
{
//	if (grid->pointInsideGrid())
	pointer->moveForward(1);
}

//////////////////////

int SCodeMachine::__dev__readGridFromTextFile(std::string FILENAME)
{
	grid = new SCodeGrid(FILENAME, tp_text);
}

void SCodeMachine::__dev__destroyGrid()
{
	(dynamic_cast<SCodeGrid *> (grid))->~SCodeGrid();
	//grid->~SCodeGrid();
}

/*==================================================================*/
/*                                                                  */
/*                 INSTRUCTION EXECUTION PART                       */
/*                                                                  */
/*==================================================================*/

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W LEWO.
 */
void SCodeMachine::executeTurnLeft()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnLeft();
}

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W PRAWO.
 */
void SCodeMachine::executeTurnRight()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnRight();
}

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W GÓRĘ.
 */
void SCodeMachine::executeTurnUp()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnUp();
}

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W DÓŁ.
 */
void SCodeMachine::executeTurnDown()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnDown();
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

void SCodeMachine::__dev__printGrid()
{
//	debug("dev print code grid START\n");
	grid->__dev__printConsole(pointer->getCoordX(),pointer->getCoordY());
//	debug("dev print code grid END\n");
}

/**
 * METODA TESTOWA. Wyświetla informacje o głowicy maszyny.
 */
void SCodeMachine::__dev__printPointer()
{
//	debug("dev print pointer START\n");
	std::cout << "gł.kodu ";
	pointer->__dev__printConsoleCoords();
	std::cout << "; ";
	__dev__printPointedInstruction();
//	debug("dev print pointer END\n");
}

/**
 * METODA TESTOWA. Wyświetla nazwę wskazywanje przez głowicę instrukcji.
 */
void SCodeMachine::__dev__printPointedInstruction()
{
	std::cout << "instr: ";
	switch(getPointedInstruction()) {
		case instr_data_left:
			std::cout << "gł.danych w lewo";
			break;
		case instr_data_right:
			std::cout << "gł.danych w prawo";
			break;
		case instr_data_zero:
			std::cout << "zeruj";
			break;
		case instr_data_succ:
			std::cout << "zwiększ";
			break;
		case instr_data_pred:
			std::cout << "zmniejsz";
			break;
		case instr_code_left:
			std::cout << "gł.kodu w lewo";
			break;
		case instr_code_right:
			std::cout << "gł.kodu w prawo";
			break;
		case instr_code_up:
			std::cout << "gł.kodu w górę";
			break;
		case instr_code_down:
			std::cout << "gł.kodu w dół";
			break;
		case instr_code_null:
			std::cout << "pusta";
			break;
		case instr_code_jump:
			std::cout << "jeśli";
			break;
		case instr_code_break:
			std::cout << "zakończ";
			break;
	}
}

/**
 * METODA TESTOWA. Wyświetla informacje o maszynie kodu.
 */
void SCodeMachine::__dev__printConsole()
{
	__dev__printPointer();
//	__dev__printGrid();
}
