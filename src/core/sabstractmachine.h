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
 * \brief Plik nagłówkowy klasy SAbstractMachine
 *
 * Plik zawiera definicję klasy SAbstractMachine. Ma ona zdefiniowane podstawowe operacje na maszynach, dziedziczą po niej dwie najważniejsze klasy projektu: SDataMachine i SCodeMachine.
 */

/** \brief Abstrakcyjna maszyna
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
// może clearPointer zrobić jako czysto wirtualną??
//		virtual void clearPointer() = 0; // ustawia głowicę na początkową komórkę
		void clearPointer(); // ustawia głowicę na początkową komórkę

		virtual void pushPointer() = 0; // pointer->moveForward(1)

};

#endif
