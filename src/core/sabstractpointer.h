#ifndef S_ABSTRACT_POINTER
#define S_ABSTRACT_POINTER

//// includes

// salvador core
#include "senums.h"

// C++
#include <string>

// STL

/** \file sabstractpointer.h
 * \brief plik nagłówkowy klasy SAbstractPointer
 *
 * Plik zawiera definicję klasy SAbstractPointer. Ma ona zdefiniowane podstawowe operacje na głowicach maszyn (maszyny kodu i maszyny danych) wykorzystywanych w Wirtualnej Maszynie Salvadora.
 */

/** \brief abstrakcyjna głowica maszyn
 *
 * Głowice są wykorzystywane przez maszyny danych i kodu
 */
class SAbstractPointer
{
	friend class SCodeMachine;
	friend class SDataMachine;

	static const int INIT_coord_x = 0, INIT_coord_y = 0;
	static const SDirections INIT_direction = dir_right;

	protected:

		int coord_x, coord_y; // współrzędne na które wskazuje głowica

		SDirections direction; // kierunek poruszania się głowicy
		void setDirection(SDirections);

	public:

		SAbstractPointer();
		virtual ~SAbstractPointer();

		void clear();

		int getCoordX();
		int getCoordY();

		void moveForward(int);

	// development:

		std::string __dev__transformBinaryDirectionToString(SDirections);

		void __dev__printConsoleCoords();

};

#endif
