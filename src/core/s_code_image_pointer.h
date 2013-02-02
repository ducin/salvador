#ifndef S_CODE_IMAGE_POINTER
#define S_CODE_IMAGE_POINTER

//// includes

// salvador core
#include "s_enums.h"
#include "s_abstract_pointer.h"

// C++
#include <string>

// STL

/** \file scodeimagepointer.h
 * \brief plik nagłówkowy klasy SCodeImagePointer
 *
 * Plik zawiera definicję klasy SCodeImagePointer. Obiekt tej klasy jest głowicą maszyny kodu.
 */

/** \brief głowica maszyny obsługująca obraz kodu
 *
 * Obiekt klasy SCodeImagePointer jest swoistym wskaźnikiem na daną komórkę obrazu kodu. Maszyna danych (SCodeMachine) wykorzystuje głowicę, by dzięki niej odczytywać wartości z obrazu kodu (SCodeImage) oraz by na tym obrazie zapisywać nowe wartości.
 */
class SCodeImagePointer : public SAbstractPointer
{

	public:

		SCodeImagePointer();
		~SCodeImagePointer();

		void turnUp(); // ^
		void turnDown(); // v
		void turnLeft(); // <
		void turnRight(); // >
};

#endif
