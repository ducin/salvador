#ifndef S_ACTION
#define S_ACTION

//// includes

// salvador core
#include "senums.h"

// C++
#include <string>

// STL

/** \file saction.h
 * \brief plik nagłówkowy klasy SAction
 *
 * Plik zawiera definicję klasy SAction. Nie wiem jeszcze co to jest i po co
 */

/** \brief zapis instrukcji wykonanej przez wirtualną maszynę
 *
 * Każda instrukcja wykonywana przez wirtualną maszynę jest zapisywana
 */
class SAction
{

	private:

		int instruction_type; // SDataInstructions lub SCodeInstructions
		SDirections pointer_direction;

	public:

		SAction(int, SDirections);
		~SAction();

};

#endif
