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

		/** szerokość siatki (rozmiar współrzędnej x) */ int size_x;
		/** wysokość siatki (rozmiar współrzędnej y) */ int size_y;

		/** Alokuje pamięć pod siatkę. */ virtual void constructGrid() = 0;
		/** Dealokuje pamięć przeznaczoną dla siatki. */ virtual void destructGrid() = 0;

		/** Zwraca wartość komórki siatki określonej współrzednymi zadanymi parametrami. @return wartość komórki siatki wskazanej parametrami */ virtual int getValueAt(int, int) = 0;

	public:

		SAbstractGrid();
		virtual ~SAbstractGrid();

		bool pointInsideGrid(int, int);
		int getSizeX();
		int getSizeY();

	// development:

		/** METODA TESTOWA. Wyświetla informacje o siatce. */ virtual void __dev__printConsole(int, int) = 0;

};

#endif
