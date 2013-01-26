#ifndef S_DEBUG
#define S_DEBUG

/** \file debug.h
 * \brief plik nagłówkowy debuggera
 *
 * Plik zawiera makro definiujące operacje debuggera
 */

/**
 * Procedura wykorzystywana w fazie implementowania aplikacji: do kontroli pamięci, kolejności operacji itp. Gdy aplikacja jest funkcjonalna, procedura nie jest już używana.
 */
	#ifdef DEBUG
		#define debug(...) do { \
		fprintf(stderr, __VA_ARGS__); \
		} while(false)
	#else
		#define debug(...) 
	#endif

#endif
