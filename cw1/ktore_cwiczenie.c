#include <stdio.h>
int main(void)
{
	printf("Ktore dzisiaj jest cwiczenie?\n");
	int dzisiaj;
	int koniec = 12;
	scanf("%d",&dzisiaj);
	printf("Do konca zostalo %d\n", koniec-dzisiaj);
	return 0;
}

