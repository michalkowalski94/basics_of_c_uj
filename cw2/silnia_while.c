#include <stdio.h>
int main(void)
{
	int liczba;
	printf("Podaj liczbe od 1 do 11: ");
	scanf("%d",&liczba);
	int i = 1;
	int silnia = 1;
	while(i <= liczba){
		silnia = silnia * i;
		++i;
	}
	printf("Silnia dla liczby %d wynosi %d\n", liczba, silnia);
	return 0;
}  
