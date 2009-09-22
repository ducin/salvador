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
	private:

		int max_index;

	protected:

		/** Siatka kodu */ int **data_grid;

		void constructGrid();
		void destructGrid();
		void zeroGrid();

	public:

		SDataGrid();
		~SDataGrid();

		int getValueAt(int, int);

		void performZeroAt(int, int);
		void performSuccAt(int, int);
		void performPredAt(int, int);

		void clear();

	// development:

		void __dev__printConsole(int, int);

};

#endif
