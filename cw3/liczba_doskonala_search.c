#include<stdio.h>
int main(void)
{
	long int liczba_;
	int ilosc;
	int i;
	printf("Ile chcesz znalezc doskonalych liczb? ");
	scanf("%d", &ilosc);
	liczba_ = 1;
	for(i = 1; i <= ilosc; ++i){
		long int liczba;
		for(liczba = liczba_; i <= ilosc; ++liczba){
			long int dzielnik, suma;
			long int dlugosc = 1;
			suma = 0;
			for(dzielnik = 1; dzielnik < liczba; ++dzielnik){
				if((liczba % dzielnik) == 0){
					suma += dzielnik;}
		
				else continue;}
			if(liczba == suma){
				printf("%ld\n", liczba);
				}
			else continue;}}

	return 0;

}		

	
		
	

