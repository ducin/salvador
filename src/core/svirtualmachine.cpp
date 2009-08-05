//// includes

// header file
#include "svirtualmachine.h"

// salvador core
#include "../debug.h"
#include "senums.h"
#include "sdatamachine.h"
#include "scodemachine.h"

// C++
#include <iostream>
#include <fstream>
#include <string>

// STL

SVirtualMachine::SVirtualMachine(std::string filename, SCodeTypes CODE_TYPE)
// constructor
{
	debug("CONSTRUCTOR - virtual-machine START\n");
	data_machine = new SDataMachine();
	code_machine = new SCodeMachine(CODE_TYPE);

	switch(CODE_TYPE)
	{
		case tp_text:
			code_machine->__dev__readGridFromTextFile(filename);
			data_machine->__dev__initGrid();
			break;
		case tp_graphics:
			// ???
			break;
	}

	prepareToExecute();
	debug("CONSTRUCTOR - virtual-machine END\n");

// TODO parametr filename
}

SVirtualMachine::~SVirtualMachine()
// destructor
{
	debug("DESTRUCTOR - virtual-machine START\n");
	data_machine->~SDataMachine();
	code_machine->~SCodeMachine();
	debug("DESTRUCTOR - virtual-machine END\n");
}

//=============================================================================

bool SVirtualMachine::isRunning()
{
	return (state == running);
}

bool SVirtualMachine::isReady()
{
	return (state == ready);
}

void SVirtualMachine::startMachine()
{
	setState(running);
}

void SVirtualMachine::restartMachine()
{
// 
}

void SVirtualMachine::stopMachine()
{
//
}

/** \brief przygotowanie do uruchomienia/zresetowania wirtualnej maszyny
 *
 * Metoda używana w celu przygotowania wirtualnej maszyny do uruchomienia. Maszyna mogła być w trakcie działania, mogła zakończyć działanie lub być gotowa do rozpoczęcia pracy. Bez względu na dotychczasowy stan, 
 * \return stan w jakim znajdowała się maszyna (SMachineStates)
 */
SMachineStates SVirtualMachine::prepareToExecute()
{
	// zapamiętaj dotychczasowy stan
	SMachineStates old = getState();

	// wyczyść logi obu pod-maszyn
	code_machine->clearStats();
	data_machine->clearStats();

	// wyczyść obraz danych
	data_machine->clearImage();

	// ustaw wskaźniki obu pod-maszyn na inicjalne
	code_machine->clearPointer();
	data_machine->clearPointer();

	// ustaw stan maszyny na "gotowy"
	setState(ready);

	// zwróć stan maszyny w którym znajdowała się dotychczas
	return old;
}

//=============================================================================

/** \brief zwraca stan wirtualnej maszyny Salvadora
 *
 * W każdej chwili istnienia, wirtualna maszyna Salvadora musi znajdować się w jakimś stanie (SMachineStates). Metoda zwraca aktualny stan wirtualnej maszyny.
 */
SMachineStates SVirtualMachine::getState()
{
	return state;
}

/** \brief ustawia stan wirtualnej maszyny Salvadora
 *
 * W każdej chwili istnienia, wirtualna maszyna Salvadora musi znajdować się w jakimś stanie (SMachineStates). Metoda ustawia stan wirtualnej maszyny na ten zadany parametrem.
 * \param state stan jaki zostanie przypisany wirtualnej maszynie
 */
void SVirtualMachine::setState(SMachineStates state)
{
	this->state = state;
}

//=============================================================================

/**
 * Wykonuje wszystkie instrukcje
 */
void SVirtualMachine::executeAllInstr()
{
	while (getState() != finished)
		executeInstr();
}

void SVirtualMachine::executeInstr()
{
	switch(code_machine->getPointedInstruction())
	{
		case instr_data_left:
			data_machine->executeTurnLeft();
			break;
		case instr_data_right:
			data_machine->executeTurnRight();
			break;
		case instr_data_zero:
			data_machine->executeZero();
			break;
		case instr_data_succ:
			data_machine->executeSucc();
			break;
		case instr_data_pred:
			data_machine->executePred();
			break;
		case instr_code_left:
			code_machine->executeTurnLeft();
			break;
		case instr_code_right:
			code_machine->executeTurnRight();
			break;
		case instr_code_up:
			code_machine->executeTurnUp();
			break;
		case instr_code_down:
			code_machine->executeTurnDown();
			break;
		case instr_code_null:
			// null jak sama nazwa wskazuje - nic nie robi
			break;
		case instr_code_jump:
			if // zero 
				(data_machine->getPointedValue() == 0)
			{ // przeskocz o jedno pole więcej głowica kodu
				code_machine->pushPointer();
			}
			// else zignoruj całość (tak jakbys wykonywał nulla)
			break;
		case instr_code_break:
			setState(finished);
			break;
	}
	if (isRunning())// jeśli maszyna nadal działa, przesuń głowicę maszyny kodu do przodu
		code_machine->pushPointer();
}

bool SVirtualMachine::revokeInstr()
{
//
}

bool SVirtualMachine::goBack(int count)
{
//
}

void SVirtualMachine::clean()
{
    code_machine->__dev__destroyGrid();
    data_machine->__dev__destroyGrid();
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

std::string SVirtualMachine::__dev__transformBinaryStateToString(SMachineStates state)
{
	switch(state)
	{
		case ready:
			return "ready";
		case running:
			return "running";
		case finished:
			return "finished";
		default:
			return "error";
	}
}

void SVirtualMachine::__dev__destroyGrid()
{
	this->data_machine->__dev__destroyGrid();
	this->code_machine->__dev__destroyGrid();
}

void SVirtualMachine::__dev__printConsole()
{
	std::cout << "[STATE: " << __dev__transformBinaryStateToString(getState()) << "]" << std::endl;
	code_machine->__dev__printConsole();
	data_machine->__dev__printConsole();
}

/** \brief symulacja działania wirtualnej maszyny
 *
 * DEVELOPMENT
 *
 * Konsolowo symyluje przebieg działania maszyny. Najpierw wyświetla dane obu maszyn, następnie po każdym kroku wyświetla wynik na konsoli. Przy każdym kroku użytkownik ma możliwość zastopowania działania maszyny, wpisując frazę "no". Metoda kończy działanie, kiedy maszyna skończy swoje działanie.
 */
void SVirtualMachine::__dev__runProgram()
{
	__dev__printConsole();
	code_machine->__dev__printConsole();
	data_machine->__dev__printConsole();
	startMachine();

	std::string answer;
	std::cout << "\n> "; getline(std::cin, answer); std::cout << std::endl;

	while (answer != "no" && isRunning())
	{
		executeInstr();
		__dev__printConsole();
		code_machine->__dev__printConsole();
		data_machine->__dev__printConsole();
		std::cout << std::endl << "> "; getline(std::cin, answer); std::cout << std::endl;
	}
	std::cout << "aborted\n";
	code_machine->__dev__destroyGrid();
	data_machine->__dev__destroyGrid();
}
