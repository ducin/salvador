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

// Qt
#include <QString>
#include <QImage>

/** \file svirtualmachine.cpp
 * \brief Plik z kodem źródłowym klasy SVirtualMachine
 *
 * Plik zawiera kod źródłowy klasy SVirtualMachine.
 */

/**
 * Konstruktor wirtualnej maszyny Salvadora.
 */
SVirtualMachine::SVirtualMachine(std::string filename, SCodeTypes CODE_TYPE)
// constructor
{
	debug("CONSTRUCTOR - virtual-machine START\n");
	data_machine = new SDataMachine();
	code_machine = new SCodeMachine(CODE_TYPE);
	switch(CODE_TYPE)
	{
		case tp_text:
			code_machine->readGridFromTextFile(filename);
			break;
		case tp_graphics:
			code_machine->readGridFromImageFile(filename);
			break;
	}
	data_machine->initGrid();
	prepareToExecute();
	debug("CONSTRUCTOR - virtual-machine END\n");
}

/**
 * Destruktor wirtualnej maszyny Salvadora.
 */
SVirtualMachine::~SVirtualMachine()
// destructor
{
	debug("DESTRUCTOR - virtual-machine START\n");
	data_machine->~SDataMachine();
	code_machine->~SCodeMachine();
	debug("DESTRUCTOR - virtual-machine END\n");
}

//=============================================================================

/**
 * Sprawdza, czy maszyna wirtualna pracuje (sprawdzany stan maszyny).
 * @return czy maszyna pracuje
 */
bool SVirtualMachine::isRunning()
{
	return (state == state_running);
}

/**
 * Sprawdza, czy maszyna wirtualna jest gotowa (sprawdzany stan maszyny).
 * @return czy maszyna jest gotowa
 */
bool SVirtualMachine::isReady()
{
	return (state == state_ready);
}

/**
 * Uruchamia maszynę (ustawia odpowiedni stan).
 */
bool SVirtualMachine::startMachine()
{
	if (isReady()) {
		setState(state_running);
		return true;
	} else {
		return false;
	}
}

/**
 * Restartuje maszynę (ustawia odpowiedni stan).
 * @return czy operacja się powiodła
 */
bool SVirtualMachine::restartMachine()
{
	prepareToExecute();
	return true;
}

/**
 * Zatrzymuje maszynę (ustawia odpowiedni stan).
 * @return czy operacja się powiodła
 */
bool SVirtualMachine::stopMachine()
{
	if (isRunning()) {
		setState(state_finished);
		return true;
	} else {
		return false;
	}
}

/** \brief przygotowanie do uruchomienia/zresetowania wirtualnej maszyny
 *
 * Metoda używana w celu przygotowania wirtualnej maszyny do uruchomienia. Maszyna mogła być w trakcie działania, mogła zakończyć działanie lub być gotowa do rozpoczęcia pracy. Bez względu na dotychczasowy stan, 
 * \return stan w jakim znajdowała się maszyna (SMachineStates)
 */
void SVirtualMachine::prepareToExecute()
{
	// wyczyść obraz danych
	data_machine->clearData();

	// ustaw wskaźniki obu pod-maszyn na inicjalne
	code_machine->clearPointer();
	data_machine->clearPointer();

	// ustaw stan maszyny na "gotowy"
	setState(state_ready);

	// domyślna wartość zachowania przy głowicy chcącej wyjść poza obraz kodu - odbijaj kierunek ruchu głowicy
	beyond_border_behavior = beh_bounce;

	step = 0;
	verbose = true;
	visual = false;
}

//=============================================================================

/**
 * Ustala zachowanie wirtualnej maszyny w sytuacji, gdy głowica kodu ma za chwilę opuścić obraz kodu, na odbicie kierunku głowicy.
 */
void SVirtualMachine::setBehaviorBounce()
{
	beyond_border_behavior = beh_bounce;
}

/**
 * Ustala zachowanie wirtualnej maszyny w sytuacji, gdy głowica kodu ma za chwilę opuścić obraz kodu, na zakończenie pracy maszyny.
  */
void SVirtualMachine::setBehaviorStop()
{
	beyond_border_behavior = beh_stop;
}

/**
 * Sprawdza czy zachowaniem wirtualnej maszyny w sytuacji, gdy głowica kodu ma za chwilę opuścić obraz kodu, jest odbicie kierunku głowicy.
 * @return czy zachowanie maszyny to odbicie kierunku głowicy
 */
bool SVirtualMachine::isBehaviorBounce()
{
	return (beyond_border_behavior == beh_bounce);
}

/**
 * Sprawdza czy zachowaniem wirtualnej maszyny w sytuacji, gdy głowica kodu ma za chwilę opuścić obraz kodu, jest zakończenie pracy maszyny.
 * @return czy zachowanie maszyny to zakończenie pracy maszyny
 */
bool SVirtualMachine::isBehaviorStop()
{
	return (beyond_border_behavior == beh_stop);
}

/**
 * Zmień zachowanie na przeciwne.
 */
void SVirtualMachine::toggleBehavior()
{
	if (isBehaviorBounce()) {
		setBehaviorStop();
	} else if (isBehaviorStop()) {
		setBehaviorBounce();
	}
}

/**
 * Nakazuje maszynie kodu odbić kierunek ruchu głowicy kodu.
 */
void SVirtualMachine::bounceCodeImagePointerDirection()
{
	code_machine->mirrorPointerDirection();
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

//=========================================================

void SVirtualMachine::setVerbosityRecursively(bool verbosity)
{
	verbose = verbosity;
	code_machine->setVerbosity(verbosity);
	code_machine->setVerbosity(verbosity);
}

/**
 * Sprawdza, czy maszyna ma włączony tryb gadatliwy.
 * @return tryb gadatliwy
 */
bool SVirtualMachine::isVerbose()
{
	return verbose;
}

/**
 * Przełącza tryb gadatliwy na przeciwny. Przełącza tryb we wszystkich podrzędnych obiektach.
 */
void SVirtualMachine::toggleVerbosity()
{
	if (verbose) {
		setVerbosityRecursively(false);
	} else {
		setVerbosityRecursively(true);
	}
}

/**
 * Sprawdza, czy maszyna ma włączony tryb wizualny.
 * @return tryb wizualny
 */
bool SVirtualMachine::isVisual()
{
	return visual;
}

/**
 * Przełącza tryb wizualny na przeciwny.
 */
void SVirtualMachine::toggleVisuality()
{
	visual = !visual;
}

//=============================================================================

/**
 * Wykonuje instrukcje aż maszyna zmieni swój stan na "zakończony".
 */
void SVirtualMachine::executeAllInstr()
{
	while (getState() != state_finished)
		executeInstr();
}

/**
 * Wykonuje jedną instrukcję.
 */
void SVirtualMachine::executeInstr()
{
	std::cout << std::endl << "krok: " << step << "; ";
	if (isVerbose())
		__dev__printConsole();
	data_machine->__dev__printConsole();
	if (isVisual())
		code_machine->__dev__printGrid();
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
			finish();
			break;
	}
	if (isRunning()) { // jeśli maszyna nadal działa, przesuń głowicę maszyny kodu do przodu
		step++;
		if (!code_machine->pushPointer()) { // jeśli głowica kodu ma za chwilę wyjść poza obraz kodu
			performActionWhenPointerOutside();
		}
	}
}

/**
 * Metoda czyści wszystkie tymczasowe dane maszyny.
 */
void SVirtualMachine::clean()
{
	code_machine->destroyGrid();
	data_machine->destroyGrid();
}

/**
 * Metoda reaguje na sytuację, gdy głowica kodu ma za chwilę znaleźć się poza obrazem kodu. Reakcja zależy od
 */
void SVirtualMachine::performActionWhenPointerOutside()
{
	if (isBehaviorBounce()) { // jeśli maszyna ma ustawiony tryb 'odbij kierunek w takiej sytuacji'
		bounceCodeImagePointerDirection();
	} else { // isBehaviorStop()
		finish();
		std::cout << "Głowica wykracza poza obraz danych";
	}
}

/**
 * Metoda kończy działanie maszyny wirtualnej Salvadora (stan zmieniony na "maszyna zakończyła działanie").
 */
void SVirtualMachine::finish()
{
	setState(state_finished);
}

/*==================================================================*/
/*                                                                  */
/*                          MERGING PART                            */
/*                                                                  */
/*==================================================================*/

/**
 * Metoda nakłada siatkę kodu (uprzednio wczytaną) na obraz, plik graficzny, przekazywany przez parametr.
 * @param filename plik graficzny
 * @return czy się udało
 */
bool SVirtualMachine::mergeGridWithImage(std::string filename)
{
	// zmienna robocza przechowująca ścieżkę do pliku z kodem
	QString QSTR_filename(filename.c_str());
	
	// stworzenie obiektu obrazu kodu, na który zostanie nałożona siatka instrukcji
	QImage *image = new QImage(QSTR_filename);
	
	if (!code_machine->ImageFitsGrid(image->width(), image->height())) { // przyszły obraz kodu za mały względem siatki kodu
		return false;
	} else {
		code_machine->mergeCode(image);
		return image->save(QSTR_filename);
	}
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

/**
 * METODA TESTOWA. Zwraca nazwę stanu zadanego przez parametr.
 * @param state stan maszyny
 * @return nazwa stanu
 */
std::string SVirtualMachine::__dev__transformBinaryStateToString(SMachineStates state)
{
	switch(state)
	{
		case state_ready:
			return "ready";
		case state_running:
			return "running";
		case state_finished:
			return "finished";
		default:
			return "error";
	}
}

/**
 * Rozkazuje podrzędnym maszynom niszczyć ich siatki.
 */
void SVirtualMachine::destroyGrid()
{
	this->data_machine->destroyGrid();
	this->code_machine->destroyGrid();
}

/**
 * METODA TESTOWA. Wyświetla informacje o wirtualnej maszynie Salvadora.
 */
void SVirtualMachine::__dev__printConsole()
{
//	std::cout << "[STATE: " << __dev__transformBinaryStateToString(getState()) << "]" << std::endl;
	code_machine->__dev__printConsole();
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
	code_machine->destroyGrid();
	data_machine->destroyGrid();
}
