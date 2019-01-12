#include <stdio.h>
int main(void)
{
	int len;
	printf("Podaj dlugosc ciagu: ");
	scanf("%d", &len);
	int a = 0;
	int b = 1;
	int i;
	int fibonacci;
	printf("Ciag Fibonacciego o zadanej dlugosci to:\n");
	printf("0\n");
	printf("1\n");
	for(i=1; i<=(len-2); ++i){
		if((len-2) <= 1 ){
			fibonacci = (len-2);
			printf("%d\n", fibonacci);}
		else{
			fibonacci = a + b;
			printf("%d\n", fibonacci);
			a = b;
			b = fibonacci;}
	}
	return 0;
}
 
