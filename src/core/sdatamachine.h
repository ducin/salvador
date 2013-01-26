#ifndef S_DATA_MACHINE
#define S_DATA_MACHINE

//// includes

// salvador core
#include "senums.h"
#include "sabstractmachine.h"

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

		/**
		 * Pole logiczne definiujące tryb gadatliwy.
		 */
		bool verbose;

	public:

		SDataMachine();
		~SDataMachine();

		void setVerbosity(bool);

		bool pushPointer();

		void clearData();

		int getPointedValue();

		void executeTurnLeft();
		void executeTurnRight();
		void executeZero();
		void executeSucc();
		void executePred();

		void initGrid();
		void destroyGrid();

	// development:

		void __dev__printConsole();
		void __dev__printPointer();
		void __dev__printGrid();
};

#endif
