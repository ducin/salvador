//// includes

// header file
#include "scodemachine.h"

// salvador core
#include "../debug.h"
#include "senums.h"
#include "scodestats.h"
#include "scodeimage.h"
#include "scodeimagepointer.h"

// C++
#include <string>
#include <iostream>

// STL
// none

SCodeMachine::SCodeMachine(SCodeTypes CODE_TYPE)
// constructor
{
	debug("CONSTRUCTOR --- code-machine START\n");
	code_type = CODE_TYPE;
	stats = new SCodeStats();
	image = new SCodeImage();
	pointer = new SCodeImagePointer();
	debug("CONSTRUCTOR --- code-machine END\n");
}

SCodeMachine::~SCodeMachine()
// destructor
{
	debug("DESTRUCTOR --- code-machine START\n");
	stats->~SCodeStats();
	image->~SCodeImage();
// śmierdzące rozwiązanie z C
// ((SCodeImagePointer*) pointer)->~SCodeImagePointer();
	(dynamic_cast<SCodeImagePointer *> (pointer))->~SCodeImagePointer();
	debug("DESTRUCTOR --- code-machine END\n");
}

void SCodeMachine::clearStats()
{
	stats->clear();
}

SInstructions SCodeMachine::getPointedInstruction()
{
	return grid->getValueAt(pointer->getCoordX(), pointer->getCoordY());
}

/*==================================================================*/
/*                                                                  */
/*                 INSTRUCTION EXECUTION PART                       */
/*                                                                  */
/*==================================================================*/

void SCodeMachine::executeTurnLeft()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnLeft();
}

void SCodeMachine::executeTurnRight()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnRight();
}

void SCodeMachine::executeTurnUp()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnUp();
}

/** \brief wykonuje instrukcję instr_code_down
 *
 * Instrukcja skręta :)
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

int SCodeMachine::__dev__readGridFromTextFile(std::string FILENAME)
{
	grid = new SCodeGrid(FILENAME, tp_text);
}

void SCodeMachine::__dev__destroyGrid()
{
	(dynamic_cast<SCodeGrid *> (grid))->~SCodeGrid();
	//grid->~SCodeGrid();
}
