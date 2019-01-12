#include <stdio.h>
int main(void)
{
	float masa;
	float wzrost;
	float wzrost_kwadrat;
	float BMI;
	printf("Podaj swoja mase w kilogramach\n");
	scanf("%f", &masa);
	printf("Podaj swoj wzrost w metrach\n");
	scanf("%f", &wzrost);
	wzrost_kwadrat = wzrost * wzrost;
	BMI = masa / wzrost_kwadrat;
	printf("Twoje BMI wynosi %f \n", BMI);
	return 0;
}
