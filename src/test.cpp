#include "core/svirtualmachine.h"
#include "core/senums.h"
#include "debug.h"

#include <iostream>
#include <fstream>
#include <string>

SVirtualMachine *m;

int runMenu()
{
	std::cout << "wybierz opcję:" << std::endl;
	std::cout << "1. uruchom maszynę" << std::endl;
	std::cout << "2. zrestartuj maszynę" << std::endl;
	std::cout << "3. wykonaj instrukcję" << std::endl;
	std::cout << "4. wykonaj podaną ilość instrukcji" << std::endl;
	std::cout << "5. cofnij ostatnią instrukcję" << std::endl;
	std::cout << "6. cofnij o podaną ilość kroków" << std::endl;
	std::cout << "9. koniec" << std::endl;

	std::string answer;
	std::cout << std::endl << "> "; getline(std::cin, answer); std::cout << std::endl;
	while (!atoi(answer.c_str()))
	{
		std::cout << "> "; getline(std::cin, answer); std::cout << std::endl;
	}
	return atoi(answer.c_str());
}

int runProgram()
{
	int continued = 1, choice;

	while (continued)
	{
		m->__dev__printConsole();

		choice = runMenu();

		switch (choice)
		{
			case 1:
				m->startMachine();
				break;
			case 2:
				m->restartMachine();
				break;
			case 3:
				m->executeInstr();
				break;
			case 4:
				// spytaj ile instrukcji do przodu ma pójść
				m->executeInstr();
				break;
			case 5:
				m->revokeInstr();
				break;
			case 6:
				// spytaj ile instrukcji wstecz chcesz isc...
				int z;
				m->goBack(z);
				break;
			case 9:
				m->stopMachine();
				break;
		}
		
		continued = (choice != 9) && (m->isRunning() || m->isReady());
	}

	m->__dev__printConsole();

	if (choice != 9)
		std::cout << "finished" << std::endl;
	else
		std::cout << "aborted" << std::endl;

	m->clean();
}

void setConsoleColor(int color)
{
	std::cout << "\033[" << color << "m";
}

int main(int argc, char **argv)
{
	if ( argc != 2 ) // zle wywolany program
	{
		setConsoleColor(31);
		std::cout << "Run the program with the code filename" << std::endl;
		setConsoleColor(0);
		return 1;
	}
	std::string code_path = "data/" + std::string(argv[1]);
	debug("MAIN HELLO\n");
	std::ifstream fin(code_path.c_str());
	if ( !fin )
	{
		std::cout << "File doesn't exist, check code files and run again" << std::endl;
		return 2;
	}

	m = new SVirtualMachine(code_path.c_str(), tp_text);
	runProgram();
	m->~SVirtualMachine();
	debug("MAIN BYE\n");
}
