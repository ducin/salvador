#ifndef S_CODE_MACHINE
#define S_CODE_MACHINE

//// includes

// salvador core
#include "s_enums.h"
#include "s_abstract_machine.h"

#include "s_code_image_pointer.h"
#include "s_code_grid.h"

// C++
#include <string>

// Qt
#include <QImage>

/** \file scodemachine.h
 * \brief plik nagłówkowy klasy SCodeMachine
 *
 * Plik zawiera definicję klasy SCodeMachine. Maszyna kodu to najważniejszy obiekt projektu Salvador, odpowiada on za działanie całości: wykonuje obliczenia, wymusza operacje innych obiektów (głowic, maszyny danych).
 */

/** \brief maszyna danych, obsługująca obraz danych
 *
 * Obiekt klasy SCodeMachine to tzw. "maszyna kodu" która obsługuje dane programu wykonywanego przez wirtualną maszynę Salvadora. Maszyna ta posiada sam obraz danych, będący graficzną reprezentacją danych wykonywanego programu.
 *
 */
class SCodeMachine : public SAbstractMachine
{

	private:

		SCodeTypes code_type; // czy kod jest z obrazka czy z siatki kodu

		/** Pole logiczne definiujące tryb gadatliwy. */ bool verbose;

		int getPixelRGBCode(QImage *, int, int);
		void modifyPixelRGBCode(QImage *, int, int, int);

	public:

		SCodeMachine(SCodeTypes);
		~SCodeMachine();

		void setVerbosity(bool);

		SInstructions getPointedInstruction(); // zwraca wskazywaną wskaxnikiem instrukcję obrazu kodu

		bool pushPointer();

		void executeTurnLeft();
		void executeTurnRight();
		void executeTurnUp();
		void executeTurnDown();
		void mirrorPointerDirection();

		void readGridFromTextFile(std::string);
		void readGridFromImageFile(std::string);
		void destroyGrid();
		
		bool ImageFitsGrid(int, int);
		void mergeCode(QImage *);

	// development:

		void __dev__printConsole();
		void __dev__printPointer();
		void __dev__printGrid();
		void __dev__printPointedInstruction();

};

#endif
