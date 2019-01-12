#include<stdio.h>
int main(void)
{
	int rzad, stopnie, spacje;
	printf("Ile chcesz aby Twoja piramidka miala stopni: ");
	scanf("%d", &stopnie);

	for(rzad=1; rzad <= stopnie; rzad++)
	{
		for(spacje = rzad; spacje < stopnie; spacje++){
			printf(" ");}
		for(spacje = 1; spacje <= (2*rzad-1); spacje++){
			printf("*");}
		printf("\n");
	}
	return 0;
}
	
