//// includes

// header file
#include "sdatagrid.h"

// salvador core
#include "../debug.h"
#include "senums.h"

// C++
#include <string>
#include <fstream>
#include <iostream>

// STL
// none

/** \file sdatagrid.cpp
 * \brief Plik z kodem źródłowym klasy SDataGrid
 *
 * Plik zawiera kod źródłowy klasy SDataGrid.
 */

/**
 * Konstruktor siatki danych.
 */
SDataGrid::SDataGrid()
{
	debug("CONSTRUCTOR data-grid START\n");
	size_x = 4;
	size_y = 1;
	constructGrid();
	zeroGrid();
	debug("CONSTRUCTOR data-grid END\n");
}

/**
 * Destruktor siatki danych.
 */
SDataGrid::~SDataGrid()
{
	debug("DESTRUCTOR data-grid START\n");
	destructGrid();
	debug("DESTRUCTOR data-grid END\n");
}

/**
 * Alokuje pamięć pod siatkę kodu.
 */
void SDataGrid::constructGrid()
{
	data_grid = new int* [size_y];
	for (int ind = 0; ind < size_y; ind++)
	{
		data_grid[ind] = new int [size_x];
	}
}

/**
 * Dealokuje pamięć przeznaczoną dla siatki kodu.
 */
void SDataGrid::destructGrid()
{
	for (int ind = 0; ind < size_y; ind++)
	{
		delete [] data_grid[ind];
	}
	delete [] data_grid;
}

/**
 * Czyści (zeruje) wszystkie komórki siatkę kodu.
 */
void SDataGrid::zeroGrid()
{
	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			data_grid[y][x] = 0;
		}
	}
}

/**
 * Czyści komórki siatki danych.
 */
void SDataGrid::clear()
{
	zeroGrid();
}

/**
 * Zwraca wartość danej określonej przez współrzędne zadane parametrami.
 * @param coord_x odcięta (współrzędna)
 * @param coord_y rzędna (współrzędna)
 * @return wartość danej określonej podanymi współrzędnymi
 */
int SDataGrid::getValueAt(int coord_x, int coord_y)
{
	return data_grid[coord_y][coord_x];
}

/**
 * Wykonuje instrukcję Salvadora ZERUJ na danej określonej przez współrzędne zadane parametrami.
 * @param coord_x odcięta (współrzędna)
 * @param coord_y rzędna (współrzędna)
 */
void SDataGrid::performZeroAt(int coord_x, int coord_y)
{
	data_grid[coord_y][coord_x] = 0;
}

/**
 * Wykonuje instrukcję Salvadora ZWIĘKSZ na danej określonej przez współrzędne zadane parametrami.
 * @param coord_x odcięta (współrzędna)
 * @param coord_y rzędna (współrzędna)
 */
void SDataGrid::performSuccAt(int coord_x, int coord_y)
{
	data_grid[coord_y][coord_x] += 1;
}

/**
 * Wykonuje instrukcję Salvadora ZMNIEJSZ na danej określonej przez współrzędne zadane parametrami.
 * @param coord_x odcięta (współrzędna)
 * @param coord_y rzędna (współrzędna)
 */
void SDataGrid::performPredAt(int coord_x, int coord_y)
{
	data_grid[coord_y][coord_x] -= 1;
}

/*==================================================================*/
/*                                                                  */
/*                        DEVELOPMENT PART                          */
/*                                                                  */
/*==================================================================*/

void SDataGrid::__dev__printConsole(int ptr_x, int ptr_y)
{
//	std::cout << std::endl << "GRID" << std::endl;
//	std::cout << "[X:" << size_x << ", Y:" << size_y << "]" << std::endl;
	std::cout << "; dane: ";
	for(int y = 0; y < size_y; y++)
	{
		for(int x = 0; x < size_x; x++)
		{
			if (ptr_x == x && ptr_y == y)
				std::cout << '<' << getValueAt(x,y) << '>';
			else
				std::cout << /*'[' <<*/ getValueAt(x,y) /*<< ']'*/;
			std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

int SDataGrid::__dev__transformCharToBinary(char code)
{
	switch(code)
	{
		case '2': return instr_code_down;
		// ?
	}
}

char SDataGrid::__dev__transformBinaryToChar(int binary)
{
	switch(binary)
	{
		case instr_code_down: return '2';
		// ?
	}
}
