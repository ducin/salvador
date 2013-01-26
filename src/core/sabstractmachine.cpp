//// includes

// header file
#include "sabstractmachine.h"

// salvador core
#include "../debug.h"
#include "senums.h"
#include "sabstractgrid.h"

// C++
#include <string>
#include <iostream>

// STL
// none

/** \file sabstractmachine.cpp
 * \brief Plik z kodem źródłowym klasy SAbstractMachine
 *
 * Plik zawiera kod źródłowy klasy SAbstractMachine.
 */

/**
 *
 * Konstruktor maszyny abstrakcyjnej. Póki co nie robi nic ciekawego. Nie zajmuje się tworzeniem głowic, tym zajmują się konstruktory klas dziedziczących po SAbstractMachine (SCodeMachine, SDataMachine).
 */
SAbstractMachine::SAbstractMachine()
{
	debug("CONSTRUCTOR --* abstract-machine START\n");
	debug("CONSTRUCTOR --* abstract-machine END\n");
}

/** \brief
 *
 * Destruktor maszyny abstrakcyjnej. Póki co nie robi nic ciekawego. Nie zajmuje się niszczeniem głowic, tym zajmują się destruktory klas dziedziczących po SAbstractMachine (SCodeMachine, SDataMachine).
 */
SAbstractMachine::~SAbstractMachine()
{
	debug("DESTRUCTOR --* abstract-machine START\n");
	debug("DESTRUCTOR --* abstract-machine END\n");
}

/** \brief ustaw współrzędne głowicy na domyślne [[i kierunek]]
 *
 * Ustawia współrzędne głowicy na wartości domyślne. Wewnątrz klasy SAbstractMachine nie zostaje tworzony żaden obiekt głowicy (ani SCodeImagePointer, ani SDataImagePointer). Są one tworzone w konstruktorach klas dziedziczących po SAbstractMachine, czyli odpowiednio: SCodeMachine lub SDataMachine. Jakoże obie głowice dziedziczą po klasie SAbstractPointer (zdefiniowane są w niej współdzędne), możliwe jest użycie wskaźnika na głowicę (teoretycznie bez jej utworzenia, przynajmniej w tej klasie)
 */
void SAbstractMachine::clearPointer()
{
	pointer->clear();
}
