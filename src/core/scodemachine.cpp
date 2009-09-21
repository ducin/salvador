//// includes

// header file
#include "scodemachine.h"

// salvador core
#include "../debug.h"
#include "senums.h"
#include "scodeimagepointer.h"

// C++
#include <string>
#include <iostream>

// STL
// none

// Qt
#include <QImage>
#include <QRgb>

/** \file scodemachine.cpp
 * \brief Plik z kodem źródłowym klasy SCodeMachine
 *
 * Plik zawiera kod źródłowy klasy SCodeMachine.
 */

/**
 * Konstruktor maszyny kodu. Tworzy obiekty głowicy obrazu kodu oraz sam obraz kodu.
 */
SCodeMachine::SCodeMachine(SCodeTypes CODE_TYPE)
{
	debug("CONSTRUCTOR --- code-machine START\n");
	code_type = CODE_TYPE;
	pointer = new SCodeImagePointer();
	debug("CONSTRUCTOR --- code-machine END\n");
}

/**
 * Destruktor maszyny kodu. Niszczy obiekty głowicy obrazu kodu oraz sam obraz kodu.
 */
SCodeMachine::~SCodeMachine()
{
	debug("DESTRUCTOR --- code-machine START\n");
// "śmierdzące" rozwiązanie z C
// ((SCodeImagePointer*) pointer)->~SCodeImagePointer();
	(dynamic_cast<SCodeImagePointer *> (pointer))->~SCodeImagePointer();
	debug("DESTRUCTOR --- code-machine END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void SCodeMachine::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Zwraca instrukcję na jaką wskazuje głowica obrazu kodu.
 * @return instrukcja wskazywana przez głowicę
 */
SInstructions SCodeMachine::getPointedInstruction()
{
	SInstructions result = (SInstructions) grid->getValueAt(pointer->getCoordX(), pointer->getCoordY());
	return result;
}

/**
 * Przesuwa głowicę kodu o jedną komórkę w bieżącym kierunku.
 * @return czy się udało (czy głowica nie wykroczyła poza obraz kodu)
 */
bool SCodeMachine::pushPointer()
{
	// bieżące współrzędne
	int tmp_x = pointer->getCoordX();
	int tmp_y = pointer->getCoordY();
	// współrzędne w następnym ruchu
	switch (pointer->getDirection()) {
		case dir_up:
			tmp_y -= 1;
			break;
		case dir_left:
			tmp_x -= 1;
			break;
		case dir_down:
			tmp_y += 1;
			break;
		case dir_right:
			tmp_x += 1;
			break;
	}
	if (grid->pointInsideGrid(tmp_x, tmp_y)) {
		pointer->moveForward(1);
		return true;
	} else {
		return false;
	}
}

/**
 * Tworzy siatkę kodu Salvadora w oparciu o plik tekstowy zadany parametrem.
 * @param filename nazwa pliku tekstowego zawierającego siatkę kodu Salvadora
 */
void SCodeMachine::readGridFromTextFile(std::string filename)
{
	grid = new SCodeGrid(filename, tp_text);
}

/**
 * Tworzy siatkę kodu Salvadora w oparciu o plik graficzny zadany parametrem.
 * @param filename nazwa pliku tekstowego zawierającego siatkę kodu Salvadora
 */
void SCodeMachine::readGridFromImageFile(std::string filename)
{
	grid = new SCodeGrid(filename, tp_graphics);
}

/**
 * Niszczy siatkę kodu Salvadora, która została stworzona podczas wczytywania z pliku: albo tekstowego albo graficznego.
 */
void SCodeMachine::destroyGrid()
{
	(dynamic_cast<SCodeGrid *> (grid))->~SCodeGrid();
	//grid->~SCodeGrid();
}

/**
 * Sprawdza, czy siatka kodu zmieści się w obrazie graficznym.
 * @param image_width szerokość obrazu na który miałaby zostać nałożona siatka kodu Salvadora
 * @param image_height wysokość obrazu na który miałaby zostać nałożona siatka kodu Salvadora
 * @return czy siatka kodu zmieści się w obrazie graficznym
 */
bool SCodeMachine::ImageFitsGrid(int image_width, int image_height)
{
	return ((image_width >= grid->getSizeX()) && (image_height >= grid->getSizeY()));
}

int SCodeMachine::getPixelRGBCode(QImage *image, int x, int y)
{
	QRgb color = image->pixel(x, y);
	return (qRed(color) + qGreen(color) + qBlue(color));
}

void SCodeMachine::modifyPixelRGBCode(QImage *image, int x, int y, int dif)
{
	QRgb color = image->pixel(x, y);
	int red_dif, green_dif, blue_dif;
	red_dif = green_dif = blue_dif = dif / 3;
	if ((dif % 3) == 2) {
		red_dif++;
		green_dif++;
	} else if ((dif % 3) == 1) {
		red_dif++;
	} else if ((dif % 3) == -2) {
		red_dif--;
		green_dif--;
	} else if ((dif % 3) == -1) {
		red_dif--;
	}
	int new_red = qRed(color);
	int new_green = qGreen(color);
	int new_blue = qBlue(color);
	if (new_red < 16) new_red += 16;
	if (new_green < 16) new_green += 16;
	if (new_blue < 16) new_blue += 16;
	new_red -= red_dif;
	new_green -= green_dif;
	new_blue -= blue_dif;
	QRgb new_color = qRgb(new_red, new_green, new_blue);
	image->setPixel(x, y, new_color);
}

/**
 * Nanosi siatkę kodu na obraz graficzny zadany parametrem. Siatka kodu została uprzednio wczytana (w konstruktorze). Po naniesieniu siatki kodu, plik graficzny zostaje zapisany.
 * @param image obraz graficzny na który zostanie nałożona siatka kodu
 */
void SCodeMachine::mergeCode(QImage *image)
{
	for (int y = 0; y < grid->getSizeY(); y++) {
		for (int x = 0; x < grid->getSizeX(); x++) {
			int pixel_code = getPixelRGBCode(image, x, y);
			int instruction = grid->getValueAt(x, y);
			int mod_code = pixel_code % 16;
			int delta = ((mod_code - instruction + 8) % 16) - 8;
			modifyPixelRGBCode(image, x, y, delta);
		}
	}
}

/*==================================================================*/
/*                                                                  */
/*                 INSTRUCTION EXECUTION PART                       */
/*                                                                  */
/*==================================================================*/

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W LEWO.
 */
void SCodeMachine::executeTurnLeft()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnLeft();
}

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W PRAWO.
 */
void SCodeMachine::executeTurnRight()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnRight();
}

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W GÓRĘ.
 */
void SCodeMachine::executeTurnUp()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnUp();
}

/**
 * Wykonuje instrukcję Salvadora SKRĘĆ GŁOWICE KODU W DÓŁ.
 */
void SCodeMachine::executeTurnDown()
{
	(dynamic_cast<SCodeImagePointer *> (pointer))->turnDown();
}

/**
 * Odbija kierunek ruchu głowicy.
 */
void SCodeMachine::mirrorPointerDirection()
{
	switch (pointer->getDirection()) {
		case dir_up:
			executeTurnDown();
			break;
		case dir_left:
			executeTurnRight();
			break;
		case dir_down:
			executeTurnUp();
			break;
		case dir_right:
			executeTurnLeft();
			break;
	}
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

/**
 * METODA TESTOWA. Wyświetla siatkę kodu.
 */
void SCodeMachine::__dev__printGrid()
{
//	debug("dev print code grid START\n");
	grid->__dev__printConsole(pointer->getCoordX(),pointer->getCoordY());
//	debug("dev print code grid END\n");
}

/**
 * METODA TESTOWA. Wyświetla informacje o głowicy maszyny.
 */
void SCodeMachine::__dev__printPointer()
{
//	debug("dev print pointer START\n");
	std::cout << "gł.kodu ";
	pointer->__dev__printConsoleCoords();
	std::cout << "; ";
	__dev__printPointedInstruction();
//	debug("dev print pointer END\n");
}

/**
 * METODA TESTOWA. Wyświetla nazwę wskazywanje przez głowicę instrukcji.
 */
void SCodeMachine::__dev__printPointedInstruction()
{
	std::cout << "instr: ";
	switch(getPointedInstruction()) {
		case instr_data_left:
			std::cout << "gł.danych w lewo";
			break;
		case instr_data_right:
			std::cout << "gł.danych w prawo";
			break;
		case instr_data_zero:
			std::cout << "zeruj";
			break;
		case instr_data_succ:
			std::cout << "zwiększ";
			break;
		case instr_data_pred:
			std::cout << "zmniejsz";
			break;
		case instr_code_left:
			std::cout << "gł.kodu w lewo";
			break;
		case instr_code_right:
			std::cout << "gł.kodu w prawo";
			break;
		case instr_code_up:
			std::cout << "gł.kodu w górę";
			break;
		case instr_code_down:
			std::cout << "gł.kodu w dół";
			break;
		case instr_code_null:
			std::cout << "pusta";
			break;
		case instr_code_jump:
			std::cout << "jeśli";
			break;
		case instr_code_break:
			std::cout << "zakończ";
			break;
	}
}

/**
 * METODA TESTOWA. Wyświetla informacje o maszynie kodu.
 */
void SCodeMachine::__dev__printConsole()
{
	__dev__printPointer();
//	__dev__printGrid();
}
