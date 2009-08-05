#ifndef VIRTUAL_MACHINE
#define VIRTUAL_MACHINE

//// includes

// salvador core
#include "senums.h"
#include "sdatamachine.h"
#include "sdatastats.h"
#include "scodemachine.h"
#include "scodestats.h"

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

		SDataMachine *data_machine; // obiekt, maszyna danych
		SImage *getDataImage(); // 
		SDataStats *getDataStats(); // 

		SCodeMachine *code_machine; // obiekt, maszyna kodu
		SImage *getCodeImage(); // 
		SCodeStats *getCodeStats(); // 

		SMachineStates state; // enum, w jakim stanie jest maszyna
		SMachineStates getState(); // return: stan maszyny
		void setState(SMachineStates);

		SMachineStates prepareToExecute();

	public:

		SVirtualMachine(std::string, SCodeTypes); // konstruktor, params: istniejący plik graficzny bmp
		~SVirtualMachine(); // destruktor

		bool isRunning(); // czy maszyna działa (sprawdzany stan maszyny)
		bool isReady(); // czy maszyna jest gotowa do rozpoczęcia pracy
		void startMachine();
		void restartMachine();
		void stopMachine();
		
		void clean(); // czyszczenie danych maszyny (zwalnianie pamięci pod obiekty)

		// TODO zastanowic sie jaki typ ma zwracac
		void executeAllInstr(); // wykonywanie instrukcji do końca działania programu
		void executeInstr(); // wykonanie jednej instrukcji
		bool revokeInstr(); // cofniecie jednej instrukcji
		bool goBack(int);


	// development:

		std::string __dev__transformBinaryStateToString(SMachineStates);
		void __dev__printConsole();
		void __dev__destroyGrid();
		void __dev__runProgram(); // TESTOWE // testowa metoda wykonywania programu dla maszyny, która wczytała już swój kod

};

#endif
