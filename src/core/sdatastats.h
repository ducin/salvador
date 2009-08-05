#ifndef S_DATA_STATS
#define S_DATA_STATS

//// includes

// salvador core
#include "senums.h"
#include "saction.h"

// C++
#include <string>

// STL
#include <list>

/** \file sdatastats.h
 * \brief plik nagłówkowy klasy SDataStats
 *
 * Plik zawiera definicję klasy SDataStats. Obiekty tej klasy przechowują informacje o działaniu obiektów klasy SDataMachine.
 */

/** \brief informacje o działaniu maszyny danych
 *
 * Obiekt klasy SDataStats jest swego rodzaju pamięcią maszyny danych (SDataMachine). Zapisywane są w niej wszystkie wykonywane instrukcje, zapisywane stany maszyny, statystyki itp. Dzięki tej klasie (we współpracy z klasą SCodeStats) można przywrócić stan maszyny wirtualnej z dowolnego kroku.
 */
class SDataStats
{

	private:

		int *instr_count;
		void clearInstrCount();
		std::list<SAction> history_list;

	public:

		SDataStats(); // konstruktor, inicjuje tablicę zliczeń
		~SDataStats(); // destruktor, niszczy tablicę zliczeń
		//// int reportDataInstruction(SDataInstructions);
		//// int getInstructionCount(SDataInstructions);

		void clear();

};

#endif
