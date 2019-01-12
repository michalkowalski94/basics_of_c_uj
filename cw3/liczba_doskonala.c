#include<stdio.h>
int main(void)
{
	long int liczba, dzielnik, suma;
	long int dlugosc = 1;
	printf("Podaj liczbe, ktora chcesz sprawedzic: ");
	scanf("%ld", &liczba);

	suma = 0;
	for(dzielnik = 1; dzielnik < liczba; ++dzielnik){
		if((liczba % dzielnik) == 0){
			suma += dzielnik;}

		else continue;}
	if(liczba == suma){
		printf("liczba %ld jest liczba dosknonala\n", liczba);}
	else{
		printf("Liczba %ld nie jest liczba doskonala\n", liczba);}
	return 0;
}
		

	
		
	

