#include<stdio.h>

float particles_x[100000]; //Tablica koordynatow x
float particles_y[100000]; //Tablica koordynatow y
float particles_z[100000]; //Tablica koordynatow z

int atoms_count; //Liczba atomow

float coordinate_x; //Zmienna rozmiaru koordynatu x
float coordinate_y; //Zmienna rozmiaru koordynatu y
float coordinate_z; //Zmienna rozmiaru koordynatu z

//Funckja wczytujaca dane z pliku

int readData(char *filename)
{
	FILE *f; //zmienna pliku
	f = fopen(filename, "r");
	if (f == NULL) return -1; //Wypluwanie bledu przy bledzie otwarcia pliku

	if (scanf(f,  "%d", &atoms_count) != 1) return -1; //Wypluwanie bledu przy bledzie formatu

	if (fscanf(f, "%f %f %f", &coordinate_x,
				  &coordinate_y,
				  &coordinate_z) != 3) return -1; //Wypluwanie bledu przy roznej wielkosci
							 	  // pudla obliczeniowego
	int i; //Stala iteratora

	for (i = 0; i <= atoms_count -1; ++i) //Petla iteratora wczytywania danych do tablic
	{
		if (fscanf(f, "%f %f %f",&(particles_x[i]),
					 &(particles_y[i]),
					 &(particles_z[i])) != 3) return -1; //Wypluwanie bledu przy bledzie formatu

		if ((particles_x[i] <0) || (particles_x[i] > coordinate_x)) return -1; //Poza pudlem check
		if ((particles_y[i] <0) || (particles_y[i] > coordinate_y)) return -1; //Poza pudlem check
		if ((particles_z[i] <0) || (particles_z[i] > coordinate_z)) return -1; //Poza pudlem check
		

	}
	fclose(f); //Zamkniecie pliku
	return 0; //Koniec
}	

//Funkcja wypisujaca koordynaty po wskazaniu numeru poprzez input z klawiatury

int pointCheck(void)
{
	int checked_number;
	printf("Podaj numer punktu: ");
	if (scanf("%d", &checked_number) != 1) //Sanity check liczby staloprzecinkowej
	{
		printf("Wprowadzono ciag znakow nie bedacy liczba calkowita\n");
		return -1;
	}
	if (checked_number > atoms_count) //Sanity check zakresu
	{
		printf("Podano liczbe wychodzaca poza dopuszczalny zakres\n");
		return -1;
	}

	printf("X: %f\nY: %f\nZ: %f\n", particles_x[checked_number],
					particles_y[checked_number],
					particles_z[checked_number]);
	return 0;
}




int main(int argc, char *argv[])
{
	char filename[512]; //Zmienna filename
	printf("Podaj nazwe pliku: ");
	if (scanf("%s", filename) != 1) //Sanity check nazwy pliku
	{
		printf("Blad w nazwie pliku\n");
		return -1;
	}
	if (readData(filename) == -1)
	{
		printf("Wystapil blad przy wykonywaniu funkcji readData"); //Sanity check readData
		return -1;
	}
	if (pointCheck() == -1)
	{
		printf("Wystapil blad przy wykonywaniu fukcji pointCheck"); //Sanity check pointCheck
		return -1;
	}
	return 0;
}
