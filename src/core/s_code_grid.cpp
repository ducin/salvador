//// includes

// header file
#include "s_code_grid.h"

// salvador core
#include "../debug.h"
#include "s_enums.h"

// C++
#include <string>
#include <fstream>
#include <iostream>

// Qt
#include <QImage>
#include <QRgb>

/** \file scodegrid.cpp
 * \brief Plik z kodem źródłowym klasy SCodeGrid
 *
 * Plik zawiera kod źródłowy klasy SCodeGrid.
 */

/**
 * Konstruktor siatki kodu.
 */
SCodeGrid::SCodeGrid(std::string filename, SCodeTypes CODE_TYPE)
{
	debug("CONSTRUCTOR code-grid START\n");
	switch(CODE_TYPE)
	{
		case tp_text:
			readFromTextFile(filename);
			break;
		case tp_graphics:
			readFromImageFile(filename);
			break;
	}
	debug("CONSTRUCTOR code-grid END\n");
}

/**
 * Destruktor siatki kodu.
 */
SCodeGrid::~SCodeGrid()
{
	debug("DESTRUCTOR code-grid START\n");
	destructGrid();
	debug("DESTRUCTOR code-grid END\n");
}

/**
 * Alokuje pamięć pod siatkę kodu.
 */
void SCodeGrid::constructGrid()
{
	instruction_grid = new SInstructions* [size_y];
	for (int ind = 0; ind < size_y; ind++)
	{
		instruction_grid[ind] = new SInstructions [size_x];
	}
}

/**
 * Dealokuje pamięć przeznaczoną dla siatki kodu.
 */
void SCodeGrid::destructGrid()
{
	for (int ind = 0; ind < size_y; ind++)
	{
		delete [] instruction_grid[ind];
	}
	delete [] instruction_grid;
}

/**
 * Zwraca instrukcję wskazywaną przez punkt współrzędnych zadanych parametrami.
 * @param coord_x pierwsza współrzędna (odcięta) punktu
 * @param coord_y pierwsza współrzędna (rzędna) punktu
 * @return instrukcja umieszczona na siatce
 */
int SCodeGrid::getValueAt(int coord_x, int coord_y)
{
	return instruction_grid[coord_y][coord_x];
}

/**
 * Wczytuje siatkę kodu Salvadora z pliku tekstowego którego nazwa jest zadana przez parametr.
 * @param filename plik z siatką kodu Salvadora
 */
void SCodeGrid::readFromTextFile(std::string filename)
{
	std::ifstream fin(filename.c_str());

	// wczytanie wymiarów siatki
	fin >> size_x;
	fin >> size_y;

	// zaalokowanie pamieci
	constructGrid();

	// bufor
	char tmp;

	// wczytywanie instrukcji
	for(int y = 0; y < size_y; y++)
	{
		for(int x = 0; x < size_x; x++)
		{
			fin >> tmp;
			instruction_grid[y][x] = (SInstructions) __dev__transformCharToBinary(tmp);
		}
	}
	fin.close();
}

/**
 * Wczytuje siatkę kodu Salvadora z pliku graficznego którego nazwa jest zadana przez parametr.
 * @param filename plik z siatką kodu Salvadora
 */
void SCodeGrid::readFromImageFile(std::string filename)
{
	QString QSTR_filename(filename.c_str());
	QImage *image = new QImage(QSTR_filename);

	size_x = image->width();
	size_y = image->height();

	// zaalokowanie pamieci
	constructGrid();

	// bufor
	QRgb color;
	int instr_code;

	// wczytywanie instrukcji
	for(int y = 0; y < size_y; y++)
	{
		for(int x = 0; x < size_x; x++)
		{
			color = image->pixel(x, y);
			instr_code = ( qRed(color) + qGreen(color) + qBlue(color) ) % 16;
			if (instr_code > 11) instr_code = 9;
			instruction_grid[y][x] = (SInstructions) instr_code;
		}
	}
	image->~QImage();
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

/**
 * METODA TESTOWA. Wyświetla informacje o siatce kodu. Parametry określają współrzędne głowicy.
 * @param ptr_x pierwsza współrzędna (odcięta) głowicy
 * @param ptr_y druga współrzędna (rzędna) głowicy
 */
void SCodeGrid::__dev__printConsole(int ptr_x, int ptr_y)
{
	std::cout << std::endl << "siatka kodu: " << "[X:" << size_x << ", Y:" << size_y << "]" << std::endl;
	for(int y = 0; y < size_y; y++)
	{
		for(int x = 0; x < size_x; x++)
			if (ptr_x == x && ptr_y == y)
				std::cout << '<' << __dev__transformBinaryToChar(getValueAt(x,y)) << '>';
			else
				std::cout << '[' << __dev__transformBinaryToChar(getValueAt(x,y)) << ']';
		std::cout << std::endl;
	}
}

/**
 * METODA TESTOWA. Konwertuje znakowy symbol instrukcji w liczbę - element enumeracji SInstructions.
 * @param code znak symbolujący instrukcję Salvadora
 * @return liczba symbolizująca instrukcję
 */
int SCodeGrid::__dev__transformCharToBinary(char code)
{
	switch(code)
	{
		case '2': return instr_code_down;
		case '4': return instr_code_left;
		case '6': return instr_code_right;
		case '8': return instr_code_up;
		case '<': return instr_data_left;
		case '>': return instr_data_right;
		case 'Z': return instr_data_zero;
		case 'S': return instr_data_succ;
		case 'P': return instr_data_pred;
		case '.': return instr_code_null;
		case '?': return instr_code_jump;
		case '#': return instr_code_break;
		default: return instr_code_null;
	}
}

/**
 * METODA TESTOWA. Konwertuje instrukcje Salvadora w znaki je symbolujące.
 * @param binary instrukcja zadana elementem enumeracji SInstructions
 * @return znak symbolujący instrukcję Salvadora
 */
char SCodeGrid::__dev__transformBinaryToChar(int binary)
{
	switch(binary)
	{
		case instr_code_down: return '2';
		case instr_code_left: return '4';
		case instr_code_right: return '6';
		case instr_code_up: return '8';
		case instr_data_left: return '<';
		case instr_data_right: return '>';
		case instr_data_zero: return 'Z';
		case instr_data_succ: return 'S';
		case instr_data_pred: return 'P';
		case instr_code_null: return '.';
		case instr_code_jump: return '?';
		case instr_code_break: return '#';
		default: return '.';
	}
}
