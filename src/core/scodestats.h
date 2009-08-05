#ifndef S_CODE_STATS
#define S_CODE_STATS

//// includes

// salvador core
#include "senums.h"

// C++
#include <string>

// STL

/** \file scodestats.h
 * \brief plik nagłówkowy klasy SCodeStats
 *
 * Plik zawiera definicję klasy SCodeStats. Obiekty tej klasy przechowują informacje o działaniu obiektów klasy SCodeMachine.
 */

/** \brief informacje o działaniu maszyny kodu
 *
 * Obiekt klasy SCodeStats jest swego rodzaju pamięcią maszyny kodu (SCodeMachine). Zapisywane są w niej wszystkie wykonywane instrukcje, zapisywane stany maszyny, statystyki itp. Dzięki tej klasie (we współpracy z klasą SDataStats) można przywrócić stan maszyny wirtualnej z dowolnego kroku.
 */
class SCodeStats
{

	public:

		SCodeStats();
		~SCodeStats();

		void clear();

};

#endif
