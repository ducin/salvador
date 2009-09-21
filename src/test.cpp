#include "core/svirtualmachine.h"
#include "core/senums.h"
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
 * Ustawia kolor czcionki konsoli Unix.
 * @param color liczba definiująca kolor czcionki pod konsolą (escape string)
 */
void setConsoleColor(int color)
{
	std::cout << "\033[" << color << "m";
}

/**
 * Wyświetla komunikat błędu na konsolę.
 * @param error tekst komunikatu błędu
 */
void printFormattedError(std::string error)
{
	setConsoleColor(31);
	std::cout << error << std::endl;
	setConsoleColor(0);
}

/**
 * Wyświetla standardowy komunikat na konsolę.
 * @param message tekst standardowego komunikatu
 */
void printFormattedMessage(std::string message)
{
	setConsoleColor(32);
	std::cout << message << std::endl;
	setConsoleColor(0);
}

/**
 * Wirtualna maszyna Salvadora - globalna zmienna
 */
SVirtualMachine *m;

/**
 * Wyświetla tekst powitalny programu.
 */
void runWelcome()
{
	setConsoleColor(33);
	std::cout << std::endl;
	std::cout << "Interpreter języka Salvador" << std::endl;
	std::cout << "Załącznik do pracy magisterskiej:" << std::endl;
	std::cout << "\"Języki ezoteryczne Piet i Salvador jako uniwersalne maszyny obliczeniowe\"" << std::endl;
	std::cout << "Tomasz Ducin, 2009" << std::endl;
	setConsoleColor(0);
	std::cout << std::endl;
}

/**
 * Wyświetla menu programu, prosi użytkownika o wybór zadania i zwraca ów wybór.
 * @return numer zadania wybrany przez użytkownika
 */
int runMenu()
{
	std::cout << "wybierz opcję:" << std::endl;
	std::cout << "1. uruchom maszynę i wykonuj instrukcje krok po kroku" << std::endl;
	std::cout << "2. uruchom maszynę i wykonuj zadaną ilość instrukcji w każdym kroku" << std::endl;
	std::cout << "3. włącz/wyłącz tryb gadatliwy (" << (m->isVerbose() ? "włączony" : "wyłączony" ) << ")" << std::endl;
	std::cout << "4. koniec" << std::endl;

	std::string answer;
	std::cout << std::endl << "> "; getline(std::cin, answer); std::cout << std::endl;
	while (!atoi(answer.c_str()))
	{
		std::cout << "> "; getline(std::cin, answer); std::cout << std::endl;
	}
	return atoi(answer.c_str());
}

/**
 * Główna procedura całej aplikacji. Wyświetla przywitanie, potem w pętli pobiera od użytkownika numer zadania i wykonuje je. Działanie programu zależy od decyzji użytkownika.
 */
void runProgram()
{
	// wyświetlanie informacji o programie
	runWelcome();
	// zmienne robocze sterujące pracą programu
	int continued = 1, choice;
	int final_choice = 4;
	// główna pętla programu
	std::string confirm_str;
	while (continued)
	{
		// wyświetlanie menu programu i pobranie odpowiedzi od użytkownika
		choice = runMenu();
		// wykonanie danego zadania w zależności od odpowiedzi użytkownika
		switch (choice)
		{
			case 1: // uruchom maszynę i wykonuj instrukcje krok po kroku
				m->startMachine();
				std::cout << "naciskaj enter po każdym kroku" << std::endl << std::endl;
				while (m->isRunning())
				{
					m->executeInstr();
					if (m->isVerbose())
						m->__dev__printConsole();
					getline(std::cin, confirm_str);
				}
				break;
			case 2: // uruchom maszynę i wykonuj zadaną ilość instrukcji w każdym kroku
				m->startMachine();
				int C;
				std::cin >> C;
				for(int ind = 0; ind < C; ind++)
				{
				    m->executeInstr();
				    m->__dev__printConsole();
				}
				break;
			case 3: // włącz/wyłącz tryb gadatliwy
				m->toggleVerbosity();
				break;
			case 4: // koniec
				m->stopMachine();
				break;
		}
		continued = (choice != final_choice) && (m->isRunning() || m->isReady());
	}
	if (choice != final_choice)
		printFormattedMessage("\r\nPraca programu zakończona");
	else
		printFormattedError("Praca programu przerwana");
}

/**
 * Procedura wejściowa aplikacji, pośrednicząca z linią poleceń (wczytuje nazwę programu z tablicy parametrów). Tworzy wszystkie potrzebne zmienne i wywołuje runProgram().
 * @param argc liczba parametrów pobranych z komendy uruchamiającej program
 * @param argv tablica z wartościami parametrów pobranych z komendy uruchamiającej program
 */
int main(int argc, char **argv)
{
	debug("MAIN HELLO\n");
	if ( argc != 3 ) // źle wywołany program
	{
		printFormattedError("Podaj dwa parametry - tryb pracy oraz plik");
		return 1;
	}
	std::string mode = std::string(argv[1]);
	std::string code_file = std::string(argv[2]);
	std::string code_path = "data/" + code_file;
	std::ifstream fin_code(code_path.c_str());
	if ( !fin_code )
	{
		printFormattedError("Plik nie istnieje, sprawdź przyczynę błędu i spróbuj ponownie");
		return 2;
	}
	// kaskada selekcji trybu pracy programu
	if (mode == "grid") {
		m = new SVirtualMachine(code_path.c_str(), tp_text);
		runProgram();
		m->~SVirtualMachine();
	} else if (mode == "image") {
		m = new SVirtualMachine(code_path.c_str(), tp_graphics);
		runProgram();
		m->~SVirtualMachine();
	} else if (mode == "merge") {
		m = new SVirtualMachine(code_path.c_str(), tp_text);
		std::string image_file;
		printFormattedMessage("Proszę podać obraz na który zostanie nałożona siatka: ");
		std::cin >> image_file;
		std::string image_path = "data/" + image_file;
		std::ifstream fin_image(image_path.c_str());
		if ( !fin_code )
		{
			printFormattedError("Plik nie istnieje, sprawdź przyczynę błędu i spróbuj ponownie");
			return 2;
		}
		if (m->mergeGridWithImage(image_path.c_str())) {
			printFormattedMessage("Operacja nie powiodła się. Sprawdź oba pliki lub ich rozmiar");
		} else {
			printFormattedError("Operacja nie powiodła się. Sprawdź oba pliki lub ich rozmiar");
			return 4;
		}
		m->~SVirtualMachine();
	} else {
		printFormattedError("Nieprawidłowy tryb pracy programu. Dozwolone: grid, image lub merge\r\n");
		return 3;
	}
	debug("MAIN BYE\n");
}
