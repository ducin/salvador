#include "core/s_virtual_machine.h"
#include "core/s_enums.h"
#include "debug.h"

#include <iostream>
#include <fstream>
#include <string>

#include <cstdlib>

/** \file test.cpp
 * \brief Plik z kodem źródłowym aplikacji
 *
 * Plik zawiera kod źródłowy aplikacji testującej interpreter języka Salvador. Program przeznaczony do użytku pod konsolą systemu Unix.
 */

/*! \mainpage Dokumentacja kodu projektu Salvador
 *
 * Zarówno sam język graficzny <b>Salvador</b>, jak i jego <b>interpreter</b> zostały stworzone przez <b>Tomasza Ducina</b>. Poniższy tekst pochodzi ze wstępu do rozdziału 2, <i>"Język Salvador"</i>, pracy magisterskiej Tomasza Ducina pt. <i>"Języki ezoteryczne Piet i Salvador jako uniwersalne maszyny obliczeniowe"</i>.
 *
 * Salvador jest językiem programowania, który zawdzięcza swą nazwę najgenialniejszemu surrealistycznemu malarzowi wszech czasów, Katalończykowi Salvadorowi Dalemu. Potrafił on przekazać swoje bardzo kontrowersyjne, odważne i konkretne idee bez względu na temat i realizację poszczególnych obrazów. Podobnie jest z językiem Salvador – dosłownie każdy obraz można zaadaptować w taki sposób, by wykonywał z góry określone programy.
 *
 * Wspólnych cech z Pietem jest niewiele, np. Salvador posiada głowicę (a nawet dwie) czytające obrazy graficzne. Podkreślić jedna należy różnice koncepcyjne względem Pieta. Założeniem przy powstawaniu języka było maksymalne zbliżenie maszyny go interpretującej do maszyny Turinga – rezygnacja ze stosu i zastąpienie jej kolejnym obrazem. Zrezygnowano też z operacji wejścia/wyjścia, przeróżne operacje arytmetyczno-logiczne na danych zastąpiono podstawowymi instrukcjami zerowania, następnika i poprzednika danej wartości – wszystko doprowadzono do możliwie najprostszych operacji.
 *
 * Instrukcje w Salvadorze są wyznaczane na podstawie konkretnego piksla: ilekroć głowica wskaże tenże piksel, zawsze ta sama instrukcja zostanie wykonana – nie istnieją żadne zależności od otoczenia.
 *
 * Pisanie programów w Salvadorze odbywa się na zupełnie innej zasadzie niż w Piecie. Można z łatwością nie tylko pisać różne fragmenty kodu i podprogramy niezależnie – i potem je łączyć w gotowe programy, ale również nie trzeba przykładać tak wielkiej wagi do kształtu obrazu. Nie potrzeba patrzeć na kod całościowo przy pisaniu pojedynczej instrukcji (co utrudniało pracę z Pietem). Cały kod jest organizowany w tzw. „siatkę kodu”, byt niezależny od wszelkich obrazów (w Piecie zaś nie sposób używać jakiejkolwiek notacji/symboliki do zapisywania pojedynczych instrukcji, od początku trzeba operować na całej planszy piksli).
 *
 */

/**
 * Sets Unix console font color.
 * 
 * @param color console font color defining number (escape string)
 */
void setConsoleColor(int color)
{
	std::cout << "\033[" << color << "m";
}

/**
 * Displays error message on the console.
 * 
 * @param message error message
 */
void printFormattedError(std::string message)
{
	setConsoleColor(31);
	std::cout << message << std::endl;
	setConsoleColor(0);
}

/**
 * Displays standard message on the console.
 * 
 * @param message standard message
 */
void printFormattedMessage(std::string message)
{
	setConsoleColor(32);
	std::cout << message << std::endl;
	setConsoleColor(0);
}

/**
 * Displays program welcome message
 */
void runWelcome()
{
	setConsoleColor(33);
	std::cout << std::endl;
	std::cout << "Salvador graphical programming language interpreter" << std::endl;
	std::cout << "Originally based on the thesis:" << std::endl;
	std::cout << "\"Graphical programming languages Piet and Salvador as universal computing machines\"" << std::endl;
	std::cout << "(C) Tomasz Ducin, 2009-2013" << std::endl;
	setConsoleColor(0);
	std::cout << std::endl;
}

/**
 * Displays program menu, asks the user for his choice and returns it.
 * 
 * @return number of the task chosen by the user.
 */
int runMenu(SVirtualMachine *salvador)
{
	std::cout << "choose option:" << std::endl;
	std::cout << "1. run machine and execute single instruction step by step" << std::endl;
	std::cout << "2. run machine and execute given number of instructions step by step" << std::endl;
	std::cout << "3. run machine and execute all instructions" << std::endl;
	std::cout << "4. toggle verbose mode (" << (salvador->isVerbose() ? "on" : "off" ) << ")" << std::endl;
	std::cout << "5. toggle visual mode (" << (salvador->isVisual() ? "on" : "off" ) << ")" << std::endl;
	std::cout << "6. toggle pointer behavior, when the pointer goes beyond the image (" << (salvador->isBehaviorBounce() ? "bounce" : "stop" ) << ")" << std::endl;
	std::cout << "7. exit" << std::endl;

	std::string answer;
	std::cout << std::endl << "> "; getline(std::cin, answer); std::cout << std::endl;
	while (!atoi(answer.c_str()))
	{
		std::cout << "> "; getline(std::cin, answer); std::cout << std::endl;
	}
	return atoi(answer.c_str());
}

/**
 * The main procedure of console application. Displays program welcome. Then
 * asks the user for the task to be performed in a loop (until program
 * termination is chosen).
 * 
 * @param SVirtualMachine* salvador virtual machine
 */
void runProgram(SVirtualMachine *salvador)
{
	// dispay program welcome
	runWelcome();
	// program runtime control variables
	int continued = 1, choice;
	int final_choice = 7;
	// main program loop
	std::string confirm_str;
	while (continued)
	{
		// display the program menu and fetch user choice
		choice = runMenu(salvador);
		// execute the task chosen by the user
		switch (choice)
		{
			case 1: // run machine and execute single instruction step by step
				salvador->startMachine();
				std::cout << "hit enter after each step" << std::endl << std::endl;
				while (salvador->isRunning())
				{
					salvador->executeInstr();
					getline(std::cin, confirm_str);
				}
				break;
			case 2: // run machine and execute given number of instructions step by step
				salvador->startMachine();
				while (salvador->isRunning())
				{
					std::cout << "> "; int C; std::cin >> C;
					for(int ind = 0; ind < C; ind++)
					{
						if (salvador->isRunning()) 
							salvador->executeInstr();
					}
				}
				break;
			case 3: // run machine and execute all instructions
				salvador->startMachine();
				while (salvador->isRunning())
					salvador->executeInstr();
				break;
			case 4: // toggle verbosity mode
				salvador->toggleVerbosity();
				break;
			case 5: // toggle visuality mode
				salvador->toggleVisuality();
				break;
			case 6: // toggle pointer behavior mode
				salvador->toggleBehavior();
				break;
			case 7: // finish
				salvador->stopMachine();
				break;
		}
		continued = (choice != final_choice) && (salvador->isRunning() || salvador->isReady());
	}
	if (choice != final_choice)
		printFormattedMessage("\r\nProgram execution finished");
	else
		printFormattedError("Program execution interrupted");
}

/**
 * Main application procedure
 *
 * @param argc parameters count
 * @param argv parameter value array
 */
int main(int argc, char **argv)
{
	debug("MAIN HELLO\n");
	if ( argc != 3 ) // wrong program parameters
	{
		printFormattedError("Pass two parameters: mode [grid|image|merge] and file (salvador program)");
		return 1;
	}
	std::string mode = std::string(argv[1]);
	std::string code_file = std::string(argv[2]);
	std::string code_path = code_file;
	std::ifstream fin_code(code_path.c_str());
	SVirtualMachine *salvador;
	if ( !fin_code )
	{
		printFormattedError("The file doesn't exist. Check the problem and try again");
		return 2;
	}
	// program mode if-cascade selection
	if (mode == "grid") {
		salvador = new SVirtualMachine(code_path.c_str(), tp_text);
		runProgram(salvador);
		delete salvador;
	} else if (mode == "image") {
		salvador = new SVirtualMachine(code_path.c_str(), tp_graphics);
		runProgram(salvador);
		delete salvador;
	} else if (mode == "merge") {
		salvador = new SVirtualMachine(code_path.c_str(), tp_text);
		std::string image_file;
		printFormattedMessage("Enter the source image filepath, where the code grid will be applied: ");
		std::cin >> image_file;
		std::string image_path = image_file;
		std::ifstream fin_image(image_path.c_str());
		if ( !fin_code )
		{
			printFormattedError("File doesn't exist. Check the problem and try again");
			return 2;
		}
		if (salvador->mergeGridWithImage(image_path.c_str())) {
			printFormattedMessage("Operation successful");
		} else {
			printFormattedError("Operation failed. Check both files and their size");
			return 4;
		}
		delete salvador;
	} else {
		printFormattedError("Wrong program mode. Choose one from [grid|image|merge]\r\n");
		return 3;
	}
	debug("MAIN BYE\n");
}
