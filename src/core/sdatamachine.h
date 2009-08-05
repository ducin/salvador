#ifndef S_DATA_MACHINE
#define S_DATA_MACHINE

//// includes

// salvador core
#include "senums.h"
#include "sabstractmachine.h"

#include "sdatastats.h"
#include "sdataimage.h"
#include "sdataimagepointer.h"

// C++
#include <string>

// STL

/** \file sdatamachine.h
 * \brief plik nagłówkowy klasy SDataMachine
 *
 * Plik zawiera definicję klasy SDataMachine. Maszyna danych wykonuje operacje nad obrazem danych, jest zależna od maszyny kodu (która wymusza na maszynie danych określone zachowanie).
 */

/** \brief maszyna danych, obsługująca obraz danych
 *
 * Obiekt klasy SDataMachine to tzw. "maszyna danych" która obsługuje dane programu wykonywanego przez Wirtualną Maszynę Salvadora. Maszyna ta posiada swój log (dziennik wszystkich wykonywanych operacji) w obiekcie klasy SDataStats oraz posiada sam obraz danych, będący graficzną reprezentacją danych wykonywanego programu.
 *
 */
class SDataMachine : public SAbstractMachine
{

	private:

		SDataStats *stats;
		SDataImage *image;

	public:

		SDataMachine(); // konstruktor z pustym obrazem danych
		//// SDataMachine(int); // konstruktor z niepustym obrazem danych
		~SDataMachine();

		void clearStats();
		void clearImage();

		int getPointedValue();

		void executeTurnLeft();
		void executeTurnRight();
		void executeZero();
		void executeSucc();
		void executePred();

	// development:

		void __dev__initGrid(); // TESTOWE // stworzenie nowej, pustej siatki
		void __dev__destroyGrid(); // TESTOWE // niszczenie grida

};

#endif
