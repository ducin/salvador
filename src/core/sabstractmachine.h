#ifndef S_ABSTRACT_MACHINE
#define S_ABSTRACT_MACHINE

//// includes

// salvador core
#include "senums.h"
#include "sabstractpointer.h"
#include "sabstractgrid.h"

// C++
#include <string>

// STL

/** \file sabstractmachine.h
 * \brief plik nagłówkowy klasy SAbstractMachine
 *
 * Plik zawiera definicję klasy SAbstractMachine. Ma ona zdefiniowane podstawowe operacje na maszynach, dziedziczą po niej dwie najważniejsze klasy projektu: SDataMachine i SCodeMachine.
 */

/** \brief abstrakcyjna maszyna
 *
 * Po tej klasie dziedzicza dwie klasy (SCodeMachine, SDataMachine, jedne z najważniejszych w projekcie).
 */
class SAbstractMachine
{

	protected:

		SAbstractPointer *pointer; // maszyna kodu ma swoją głowicę, a maszyna danych swoją
		SAbstractGrid *grid; // maszyna kodu ma swoją siatkę, a maszyna danych swoją

	public:

		SAbstractMachine();
		virtual ~SAbstractMachine();

		virtual void clearStats() = 0; // czyści logi
		void clearPointer(); // ustawia głowicę na początkową komórkę

		void pushPointer(); // pointer->moveForward(1)

	// development:

		void __dev__grid_printConsole(); // TESTOWE // wyswietlenie siatki
		void __dev__pointer_printConsole(); // TESTOWE // wyświetlanie głowicy
		void __dev__printConsole(); // TESTOWE
};

#endif
