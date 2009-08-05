#ifndef S_CODE_MACHINE
#define S_CODE_MACHINE

//// includes

// salvador core
#include "senums.h"
#include "sabstractmachine.h"

#include "scodestats.h"
#include "scodeimage.h"
#include "scodeimagepointer.h"
#include "scodegrid.h"

// C++
#include <string>

// STL

/** \file scodemachine.h
 * \brief plik nagłówkowy klasy SCodeMachine
 *
 * Plik zawiera definicję klasy SCodeMachine. Maszyna kodu to najważniejszy obiekt projektu Salvador, odpowiada on za działanie całości: wykonuje obliczenia, wymusza operacje innych obiektów (głowic, maszyny danych).
 */

/** \brief maszyna danych, obsługująca obraz danych
 *
 * Obiekt klasy SCodeMachine to tzw. "maszyna kodu" która obsługuje dane programu wykonywanego przez wirtualną maszynę Salvadora. Maszyna ta posiada swój log (dziennik wszystkich wykonywanych operacji) w obiekcie klasy SCodeStats oraz posiada sam obraz danych, będący graficzną reprezentacją danych wykonywanego programu.
 *
 */
class SCodeMachine : public SAbstractMachine
{

	private:

		SCodeTypes code_type; // czy kod jest z obrazka czy z siatki kodu

		SCodeStats *stats;
		SCodeImage *image;

	public:

		SCodeMachine(SCodeTypes);
		~SCodeMachine();

		void clearStats();

		SInstructions getPointedInstruction(); // zwraca wskazywaną wskaxnikiem instrukcję obrazu kodu

		void executeTurnLeft();
		void executeTurnRight();
		void executeTurnUp();
		void executeTurnDown();
		// void executeNull(); // brak instrukcji
		// void executeJump(); // nadzoruje maszyna wirtualna
		// void executeBreak(); // brak instrukcji

	// development:

		int __dev__readGridFromTextFile(std::string); // TESTOWE // wczytanie siatki kodu z pliku
		void __dev__destroyGrid(); // TESTOWE // niszczenie grida

};

#endif
