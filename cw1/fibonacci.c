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
	for(i=1; i<=len; ++i){
		printf("Ciag Fibonaciego o zadanej dlugosci to:\n");
		if(len <= 1 ){
			fibonacci = len;
			printf("%d\n", fibonacci);}
		else{
			fibonacci = a + b;
			printf("%d\n", fibonacci);
			a = b;
			b = fibonacci;}
	}
	return 0;
}
 
