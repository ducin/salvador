#ifndef S_CODE_GRID
#define S_CODE_GRID

//// includes

// salvador core
#include "senums.h"
#include "sabstractgrid.h"

// C++
#include <string>

// STL

/** \file scodegrid.h
 * \brief plik nagłówkowy klasy SCodeGrid
 *
 * Plik zawiera definicję klasy SCodeGrid. Obiekty tej klasy reprezentują siatkę kodu dowolnego programu w języku Salvador.
 */

/** \brief siatka kodu
 *
 * 2 cele:
 *
 * - testowanie (development)
 * - nakładanie na obrazek siatki kodu (celem stworzenia obrazka zawierającego program)
 */
class SCodeGrid : public SAbstractGrid
{

	protected:

		/** Siatka kodu. */ SInstructions **instruction_grid;

		void readFromTextFile(std::string);
		void readFromImageFile(std::string);

		void constructGrid();
		void destructGrid();

	public:

		SCodeGrid(std::string, SCodeTypes);
		~SCodeGrid();

		int getValueAt(int, int);

	// development:

		void __dev__printConsole(int, int);

		int __dev__transformCharToBinary(char);
		char __dev__transformBinaryToChar(int);

};

#endif
