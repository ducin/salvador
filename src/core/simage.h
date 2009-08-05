#ifndef S_IMAGE
#define S_IMAGE

//// includes

// salvador core
#include "senums.h"

// C++
#include <string>

// STL
// none

// Qt
#include <QImage>

/** \file simage.h
 * \brief plik nagłówkowy klasy SImage
 *
 * Plik zawiera definicję klasy SImage która jest rozbudowaniem klasy QImage. Udostepnione są metody graficzne (np rysujące pewne kształty) które to metody są wykorzystywane przez obiekty klas dziedziczących po SImage
 */

/** \brief rozbudowa QImage o odpowiednie metody rysowania kształtów na bitmapie
 *
 * Klasa SImage udostępnia metody rysujące na bitmapie różne kształy, np. prostokąty. Metody te są wywoływane w metodach klas dziedziczących po SImage (czyli SDataImage i SCodeImage). Przykładowo, aby SDataImage wyświetlił swój obraz danych, wielokrotnie będzie uzywał metody paintFilledRectangle do wyświetlenia każdej danej z osobna.
 */
class SImage : public QImage
{

	public:

		SImage();
		~SImage();

		void paintRectangle(int, int, int, int, QColor);
		void paintFilledRectangle(int, int, int, int, QColor, QColor);

};

#endif
