#ifndef S_DATA_IMAGE
#define S_DATA_IMAGE

//// includes

// salvador core
#include "senums.h"
#include "simage.h"

// C++
#include <string>

// STL
// none

/** \file sdataimage.h
 * \brief plik nagłówkowy klasy SDataImage
 *
 * Plik zawiera definicję klasy SDataImage. Obiekt tej klasy jest tworzony dla Wirtualnej Maszyny Salvadora i jest graficzną reprezentacją obrazu danych.
 */

class SDataImage : public SImage
{

	public:

		SDataImage();
		~SDataImage();

		void clear();

};

#endif
