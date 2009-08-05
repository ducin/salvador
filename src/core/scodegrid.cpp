//// includes

// header file
#include "scodegrid.h"

// salvador core
#include "../debug.h"
#include "senums.h"

// C++
#include <string>
#include <fstream>
#include <iostream>

// STL
// none

SCodeGrid::SCodeGrid(std::string filename, SCodeTypes CODE_TYPE)
{
	debug("CONSTRUCTOR code-grid START\n");
	switch(CODE_TYPE)
	{
		case tp_text:
			readFromFile(filename);
			break;
		case tp_graphics:
			// ???
			break;
	}
	debug("CONSTRUCTOR code-grid END\n");
}

SCodeGrid::~SCodeGrid()
{
	debug("DESTRUCTOR code-grid START\n");
	destructGrid();
	debug("DESTRUCTOR code-grid END\n");
}

void SCodeGrid::constructGrid()
{
	instruction_grid = new SInstructions* [size_y];
	for (int ind = 0; ind < size_y; ind++)
	{
		instruction_grid[ind] = new SInstructions [size_x];
	}
}

void SCodeGrid::destructGrid()
{
	for (int ind = 0; ind < size_y; ind++)
	{
		delete [] instruction_grid[ind];
	}
	delete [] instruction_grid;
}

// zwraca instrukcję wskazywaną przez punkt o podanych współrzędnych
int SCodeGrid::getValueAt(int coord_x, int coord_y)
{
	return instruction_grid[coord_y][coord_x];
}

/** @return kod błędu:
 * 0: ok
 * 1: nie ma takiego pliku
 * 2: błędny format wejścia
 */
// dorobić bezpieczeństwo - np pliku nie ma itp
int SCodeGrid::readFromFile(std::string filename)
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
			instruction_grid[y][x] = __dev__transformCharToBinary(tmp);
		}
	}
	fin.close();
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

void SCodeGrid::__dev__printConsole(int ptr_x, int ptr_y)
{
	std::cout << std::endl << "GRID" << std::endl;
	std::cout << "[X:" << size_x << ", Y:" << size_y << "]" << std::endl;
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
	}
}

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
	}
}
