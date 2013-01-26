#ifndef S_DATA_IMAGE_POINTER
#define S_DATA_IMAGE_POINTER

//// includes

// salvador core
#include "senums.h"
#include "sabstractpointer.h"

// C++
#include <string>

// STL

/** \file sdataimagepointer.h
 * \brief plik nagłówkowy klasy SDataImagePointer
 *
 * Plik zawiera definicję klasy SDataImagePointer. Obiekt tej klasy jest głowicą maszyny danych.
 */

/** \brief głowica maszyny obsługująca obraz danych
 *
 * Obiekt klasy SDataImagePointer jest swoistym wskaźnikiem na daną komórkę obrazu danych. Maszyna danych (SDataMachine) wykorzystuje głowicę, by dzięki niej odczytywać wartości z obrazu danych (SDataImage) oraz by na tym obrazie zapisywać nowe wartości.
 */
class SDataImagePointer : public SAbstractPointer
{

	public:

		SDataImagePointer();
		~SDataImagePointer();

		void moveLeft(); // <<
		void moveRight(); // >>

		// jakaś metoda do pobrania wartości wskazywanej przez głowicę: SDataValue readValue();

};

#endif
