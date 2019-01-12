#include<stdio.h>
#include<stdlib.h>
#include<math.h>

unsigned int lcyfr(unsigned int num)
{
	double d_num;
	d_num = double num;
	unsigned int wykladnik;
	double wynik_dzielenia = 2;
	unsigned int wykladnik;
	for(wykladnik = 1; wynik_dzielenia >= 1 ; wykladnik++){
			double dzielnik = pow(10, wykladnik);
			wynik_dzielenia = d_num / dzielnik;
			if(wynik_dzielenia < 1){
				liczba_cyfr = wykladnik;}
			else continue;


	
	return liczba_cyfr
}
int main(void)
{	
