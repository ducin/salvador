#ifndef S_ABSTRACT_GRID
#define S_ABSTRACT_GRID

//// includes

// salvador core
#include "senums.h"

// C++
#include <string>

// STL

/** \file sabstractgrid.h
 * \brief Plik nagłówkowy klasy SAbstractGrid
 *
 * Plik zawiera definicję klasy SAbstractGrid. Obiekty tej klasy reprezentują abstrakcyjną siatkę wykorzystywaną przez programy języka Salvador
 */

/** \brief Sbstrakcyjna siatka
 *
 * Siatka jest narzędziem które ułatwia przetrzymywanie pewnych danych w pamięci i udostępnia proste metody wyświetlające te dane na konsolę. Po klasie SAbstractGrid dziedziczą dwie klasy: SCodeGrid - siatka kodu oraz SDataGrid - siatka danych.
 */
class SAbstractGrid
{

	friend class SCodeMachine;
	friend class SDataMachine;

	protected:

		int size_x, size_y;

		virtual void constructGrid() = 0;
		virtual void destructGrid() = 0;

		virtual int getValueAt(int, int) = 0;

	public:

		SAbstractGrid();
		virtual ~SAbstractGrid();

		bool pointInsideGrid(int, int);

	// development:

		virtual int __dev__transformCharToBinary(char) = 0;
		virtual char __dev__transformBinaryToChar(int) = 0;

		virtual void __dev__printConsole(int, int) = 0;

};

#endif
