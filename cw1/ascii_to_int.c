#include <stdio.h>
int main(void)
{
	printf("Podaj znak z tablicy ASCII \n");
	char znak_ascii;
	int znak_int;
	scanf("%c",&znak_ascii);
	znak_int = znak_ascii;
	printf("Numer tego znaku to: %d \n", znak_int);

	printf("Podaj liczbe calkowita do konwersji na ASCII \n");
	int liczba_int;
	char liczba_ascii;
	scanf("%d",&liczba_int);
	liczba_ascii = liczba_int;
	printf("Znak przypisany do tej liczby calkowitej to: %c \n", liczba_ascii);


	return 0;
}
