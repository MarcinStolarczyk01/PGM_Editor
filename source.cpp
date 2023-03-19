#include <iostream>
#include "repository.h"


int main()
{
	//dodaj komentarze po angielsku
	//dodaj rzucanie wyjatkow i obsluge bledow
	//zabazpiecz vector przed realokacją podczas tworzenia mapy pixeli
	// skoro masz już wymiary to łątwo jest wg nich dobrać capacity

	//shipcomment będzie tylko odpowiedzialny za przesunięcie wskaźnika w tekście
	//za komentarz

	//następnie w load image muszę wyczyścić źle pobraną do rtablicy pixeli
	//wartość i odczytać ją ponownie

	//jeżeli pierwszy znak nie będący liczbą nie jest również '#' to zgłoś błąd odczytu.
	//możesz też zaproponować wczytywanie dalej lub przerwanie

	Repository rep1;
	rep1.Menu();
	return 0;
}


