#ifndef S_DATA_GRID
#define S_DATA_GRID

//// includes

// salvador core
#include "senums.h"
#include "sabstractgrid.h"

// C++
#include <string>

// STL

/** \file sdatagrid.h
 * \brief plik nagłówkowy klasy SDataGrid
 *
 * Plik zawiera definicję klasy SDataGrid. Obiekty tej klasy reprezentują siatkę danych uruchomionego programu w języku Salvador.
 */

/** \brief siatka danych
 *
 * Klasa ta umożliwia reprezentację obrazu danych w pamięci komputera.
 */
class SDataGrid : public SAbstractGrid
{

	protected:

		int **data_grid;

		void constructGrid();
		void destructGrid();
		void zeroGrid();

	public:

		SDataGrid();
		~SDataGrid();

		int getValueAt(int, int);

		int performZeroAt(int, int);
		int performSuccAt(int, int);
		int performPredAt(int, int);

	// development:

		void __dev__printConsole(int, int);

		int __dev__transformCharToBinary(char);
		char __dev__transformBinaryToChar(int);

};

#endif
