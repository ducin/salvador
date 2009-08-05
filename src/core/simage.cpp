//// includes

// header file
#include "simage.h"

// salvador core
#include "../debug.h"
#include "senums.h"

// C++
#include <string>

// STL
// none

// Qt
#include <QImage>
#include <QColor>

/** \brief konstruktor
 *
 * Żadne dodatkowe operacje nie są wykonywane.
 */
SImage::SImage()
{
	debug("CONSTRUCTOR ----* image START\n");

	debug("CONSTRUCTOR ----* image END\n");
}

/** \brief destruktor
 *
 * Żadne dodatkowe operacje nie są wykonywane.
 */
SImage::~SImage()
{
	debug("DESTRUCTOR ----* image START\n");

	debug("DESTRUCTOR ----* image END\n");
}

/** \brief wyświetla niewypełniony prostokąt
 *
 * Wyświetla na bitmapie obramowanie prostokąta. Jako argumenty podawany jest punkt (bazowy, od którego rozpoczyna się wyświetlanie), podawane są długość i wysokość prostokąta oraz kolor obramowania
 * \param start_X współrzędna X punktu od którego rozpoczyna się wyświetlanie prostokąta.
 * \param start_Y współrzędna Y punktu od którego rozpoczyna się wyświetlanie prostokąta.
 * \param size_X rozmiar prostokąta w poziomie (wliczając punkt początkowy).
 * \param size_Y rozmiar prostokąta w pionie (wliczając punkt początkowy).
 * \param border_color kolor obramowania.
 * \return void.
 */
void SImage::paintRectangle(int start_X, int start_Y, int size_X, int size_Y, QColor border_color)
{

}

/** \brief wyświetla wypełniony prostokąt
 *
 * Wyświetla na bitmapie obramowanie prostokąta. Jako argumenty podawany jest punkt (bazowy, od którego rozpoczyna się wyświetlanie), podawane są długość i wysokość prostokąta oraz kolor obramowania
 * \param start_X współrzędna X punktu od którego rozpoczyna się wyświetlanie prostokąta
 * \param start_Y współrzędna Y punktu od którego rozpoczyna się wyświetlanie prostokąta
 * \param size_X rozmiar prostokąta w poziomie (wliczając punkt początkowy)
 * \param size_Y rozmiar prostokąta w pionie (wliczając punkt początkowy)
 * \param border_color kolor obramowania
 * \param fill_color kolor wypełnienia
 * \return void.
 */
void SImage::paintFilledRectangle(int start_X, int start_Y, int size_X, int size_Y, QColor border_color, QColor fill_color)
{

}

