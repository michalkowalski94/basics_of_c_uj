#include <stdio.h>
int main(void)
{
	int liczba;
	printf("Podaj liczbe od 1 do 11: ");
	scanf("%d",&liczba);
	int i;
	int silnia = 1;
	for(i=1; i <= liczba; ++i){
		silnia = silnia * i;
	}
	printf("Silnia dla liczby %d wynosi %d\n", liczba, silnia);
	return 0;
}  
