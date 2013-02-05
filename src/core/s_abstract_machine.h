#ifndef S_ABSTRACT_MACHINE
#define S_ABSTRACT_MACHINE

//// includes

// salvador core
#include "s_enums.h"
#include "s_abstract_pointer.h"
#include "s_abstract_grid.h"

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

		/** Głowica maszyny. Maszyna kodu ma swoją głowicę, a maszyna danych swoją. */
		SAbstractPointer *pointer;

		/** Siatka maszyny. Maszyna kodu ma swoją siatkę, a maszyna danych swoją. */
		SAbstractGrid *grid;

	public:

		SAbstractMachine();
		virtual ~SAbstractMachine();
// może clearPointer zrobić jako czysto wirtualną??
//		virtual void clearPointer() = 0; // ustawia głowicę na początkową komórkę
		void clearPointer();

		/** Przesuwa głowicę o jedną komórkę w bieżącym kierunku. */
		virtual bool pushPointer() = 0;

};

#endif
