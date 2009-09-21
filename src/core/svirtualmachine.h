#ifndef VIRTUAL_MACHINE
#define VIRTUAL_MACHINE

//// includes

// salvador core
#include "senums.h"
#include "sdatamachine.h"
#include "scodemachine.h"

// C++
#include <string>

// STL

/** \file svirtualmachine.h
 * \brief plik nagłówkowy klasy SVirtualMachine
 *
 * Plik zawiera definicję klasy SVirtualMachine. Obiekt tej klasy jest w pełni funkcjonalnym interpreterem języka Salvador.
 */

/** \brief wirtualna maszyna Salvadora - najbardziej "zewnętrzna" klasa całego projektu
 *
 * Wirtualna maszyna Salvadora jest czymś w stylu opakowania, które kryje w sobie wszystkie mechanizmy interpretera. Do działania używa dwóch pozostałych maszyn: maszyny kodu (SCodeMachine) oraz maszyny danych (SDataMachine); zarządza czasem życia obu z nich.
 *
 * Działanie wirtualnej maszyny Salvadora:
 *
 * Maszyna musi być ustawiona w stanie 'ready' (SMachineStates, jest to możliwe przy pomocy metody XXX lub od razu po wywołaniu konstruktora). Metoda YYY przełącza wirtualną maszynę w stan działania (SMachineStates, 'running'). Następnie przy pomocy metody ZZZ można zlecać maszynie wykonanie pojedynczej instrukcji intepretera.
 *
 * Wykonanie pojedynczej instrukcji:
 *
 * - wirtualna maszyna zleca maszynie kodu (SCodeMachine) sprawdzenie jaka instrukcja (SCodeInstructions, SDataInstructions) ma zostać wykonana.
 * - maszyna kodu (SCodeMachine) zwraca maszynie wirtualnej informację o instrukcji
 * - w zależności od rodzaju instrukcji, maszyna wirtualna zleca jej wykonanie maszynie kodu (SCodeMachine, SCodeInstructions) lub maszynie danych (SDataMachine, SDataInstructions)
 * - maszyna wykonująca instrukcję, zapisuje ją w swoim logu (SCodeStats, SDataStats)
 * - maszyna kodu (SCodeMachine) przesuwa swoją głowicę (SCodeImagePointer) w dotychczasowym kierunku
 */
class SVirtualMachine
{

	private:

		SDataMachine *data_machine; // maszyna danych
		SCodeMachine *code_machine; // maszyna kodu

		SMachineStates state; // w jakim stanie jest maszyna
		SMachineStates getState();
		void setState(SMachineStates);

		void prepareToExecute();

		bool verbose;
		void setVerbosityRecursively(bool);

		int step;

		SBeyondBorderBehavior beyond_border_behavior;

	protected:

		void finish();

	public:

		SVirtualMachine(std::string, SCodeTypes); // konstruktor, params: istniejący plik graficzny bmp
		~SVirtualMachine(); // destruktor

		bool isVerbose();
		void toggleVerbosity();

		void setBehaviorBounce();
		void setBehaviorStop();
		bool isBehaviorBounce();
		bool isBehaviorStop();

		void bounceCodeImagePointerDirection();
		void performActionWhenPointerOutside();
		void toggleBehavior();

		bool isRunning(); // czy maszyna działa (sprawdzany stan maszyny)
		bool isReady(); // czy maszyna jest gotowa do rozpoczęcia pracy
		bool startMachine();
		bool restartMachine();
		bool stopMachine();

		void clean(); // czyszczenie danych maszyny (zwalnianie pamięci pod obiekty)

		void executeAllInstr(); // wykonywanie instrukcji do końca działania programu
		void executeInstr(); // wykonanie jednej instrukcji

		bool mergeGridWithImage(std::string);

		void destroyGrid();

// development:

		std::string __dev__transformBinaryStateToString(SMachineStates);
		void __dev__printConsole();
		void __dev__runProgram(); // TESTOWE // testowa metoda wykonywania programu dla maszyny, która wczytała już swój kod

};

#endif
