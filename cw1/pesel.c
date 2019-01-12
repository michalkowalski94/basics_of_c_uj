#include <stdio.h>
int main(void)
{
	printf("Podaj swoj numer PESEL\n");
	
	double pesel;
	scanf("%lf",&pesel);

	double rokf;
	int dzielnik1 = 1000000000;
	rokf = pesel / dzielnik1;
	unsigned int rok_ = rokf;
	unsigned int rok = rok_ + 1900;

	double miesiacf;
	int dzielnik2 = 10000000;
	miesiacf = pesel / dzielnik2;
	unsigned int miesiac_ = miesiacf;
	unsigned int miesiac = miesiac_ - (rok_ * 100);

	double dzienf;
	int dzielnik3 = 100000;
	dzienf = pesel / dzielnik3;
	unsigned int dzien_ = dzienf;
	unsigned int dzien = dzien_ - (miesiac_ * 100);

	printf("Data urodzenia: %u.%u.%u \n", dzien, miesiac, rok);
}

