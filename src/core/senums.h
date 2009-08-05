#ifndef ENUMS
#define ENUMS

/** \file senums.h
 * \brief wszystkie enumeracje
 *
 * Plik nagłówkowy zawiera wszystkie enumeracje które są wykorzystywane w projekcie.
 */

//! operacje obu maszyn (SCodeMachine i SDataMachine)
/*! Zestaw wszystkich możliwych operacji wykonywanych przez maszynę kodu i maszynę danych. Podczas wykonywania pojedynczej instrukcji, wirtualna maszyna Salvadora (SVirtualMachine) wysyła polecenie do odpowiedniej maszyny. Ta ją następnie wykonuje. */
enum SInstructions {
	instr_data_left, /*!< <b>@htmlonly &laquo; @endhtmlonly</b>, <b>przesuń</b> głowicę maszyny danych <b>w lewo</b> */
	instr_data_right, /*!< <b>@htmlonly &raquo; @endhtmlonly</b>, <b>przesuń</b> głowicę maszyny danych <b>w prawo</b> */
	instr_data_zero, /*!< <b>Z</b>, <b>wyzeruj</b> komórkę pamięci na którą wskazuje głowica maszyny danych */
	instr_data_succ, /*!< <b>S</b>, <b>zwiększ o 1</b> wartość komórki pamięci na którą wskazuje głowica maszyny danych */
	instr_data_pred, /*!< <b>P</b>, <b>zmniejsz o 1</b> wartość komórki pamięci na którą wskazuje głowica maszyny danych */
	instr_code_left, /*!< <b>@htmlonly &larr; @endhtmlonly</b>, <b>przesuń</b> głowicę maszyny kodu <b>w lewo</b> */
	instr_code_right, /*!< <b>@htmlonly &rarr; @endhtmlonly</b>, <b>przesuń</b> głowicę maszyny kodu <b>w prawo</b> */
	instr_code_up, /*!< <b>@htmlonly &uarr; @endhtmlonly</b>, <b>przesuń</b> głowicę maszyny kodu <b>w górę</b> */
	instr_code_down, /*!< <b>@htmlonly &darr; @endhtmlonly</b>, <b>przesuń</b> głowicę maszyny kodu <b>w dół</b> */
	instr_code_null, /*!< <b>.</b>, instrukcja pusta */
	instr_code_jump, /*!< <b>?</b>, <b>sprawdź</b> czy wartość komórki wskazywanej przez głowicę maszyny danych jest liczbą niezerową; <b>jeśli tak</b> - przesuń głowicę maszyny kodu w dotychczasowym kierunku o jedną komórkę i wykonuj dalej polecenia; <b>jeśli nie</b> - przesuń (analogicznie) o 2 komórki i wykonuj dalej polecenia */
	instr_code_break /*!< <b>#</b>, <b>zakończ</b> pracę maszyny kodu */
 };

//! stany wirtualnej maszyny Salvadora (SVirtualMachine)
/*! Wirtualna maszyna Salvadora (SVirtualMachine) w kazdej chwili istnienia ma określony stan. Nie wpływa to bezpośrednio na przebieg wykonywania instrukcji języka Salvador, ale znacząco ułatwia wykorzystywanie interpretera przez UI, np komponenty graficzne. */
enum SMachineStates {
	ready, /*!< maszyna jest gotowa do rozpoczęcia pracy */
	running, /*!< maszyna jest w trakcie pracy */
	finished /*!< maszyna zakończyła działanie */
};

//! kierunki głowicy maszyny kodu
/*! Głowica maszyny kodu ma cechę, która określa, w którym kierunku zwrócona jest głowica. */
enum SDirections {
	dir_up, /*!< w górę */
	dir_right, /*!< w prawo */
	dir_down, /*!< w dół */
	dir_left /*!< w lewo */
};

//! zachowanie maszyny w przypadku gdy głowica kodu miałaby wyjść poza granice rysunku
/*! Głowica maszyny kodu (SCodeImagePointer) porusza się po obrazie kodu (SCodeImage) i istnieje możliwość, że głowica mogłaby "wypaść" poza obraz kodu. Enumeracja ta definiuje zachowanie wirtualnej maszyny w takiej sytuacji */
enum SBeyondBorderBehavior {
	beh_bounce, /*!< głowica zmienia swój zwrot ("odbija się") */
	beh_stop, /*!< kończy się praca wirtualnej maszyny */
};

//! rodzaje kodów wirtualnych maszyn
/*! Wirtaulna maszyna Salvadora może przyjmować kody programów w różnej postaci. */
enum SCodeTypes {
	tp_graphics, /*!< grafika - rysunek */
	tp_text, /*!< tekst */
};

#endif
