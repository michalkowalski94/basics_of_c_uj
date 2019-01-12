#include<stdio.h>
#include<stdlib.h>

typedef struct{
	unsigned int p;
	unsigned int q;
	unsigned int r;
}	cell_t;


typedef struct{
	float x; //Tablica koordynatow x
	float y; //Tablica koordynatow y
	float z; //Tablica koordynatow z
}	position_t;

cell_t *cell;
cell_t cell_box;
position_t *coordinate;
position_t box;
int atoms_count; //Liczba atomow

//Funckja wczytujaca dane z pliku


int getIdx(void)
{
	printf("Podaj ilosc podzialow pudla obliczeniowego wzdzluz osi X: ");
	if (scanf("%d", &cell_box.p) !=1){
		printf("Wprowadzono ciag znakow ie bedac liczba calkowita");
		return -1;}
	printf("Podaj ilosc podzialow pudla obliczeniowego wzdzluz osi Y: ");
	if (scanf("%d", &cell_box.q) !=1){
		printf("Wprowadzono ciag znakow ie bedac liczba calkowita");
		return -1;}
	printf("Podaj ilosc podzialow pudla obliczeniowego wzdzluz osi Z: ");
	if (scanf("%d", &cell_box.r) !=1){
		printf("Wprowadzono ciag znakow ie bedac liczba calkowita"); 
		return -1;}
	int j;
	for (j=0; j <= atoms_count-1; ++j)
	{
		cell[j].p = (int)(coordinate[j].x / (box.x / cell_box.p));
		if (cell[j].p == cell_box.p){cell[j].p--;}


		cell[j].q = (int)(coordinate[j].y / (box.y / cell_box.q));
		if (cell[j].q == cell_box.q){cell[j].q--;}


		cell[j].r = (int)(coordinate[j].z / (box.z / cell_box.r));
		if (cell[j].r == cell_box.r){cell[j].r--;}


	}

	return 0;
}
int readData(char *filename)
{
	FILE *f; //zmienna pliku
	f = fopen(filename, "r");
	if (f == NULL) return -1; //Wypluwanie bledu przy bledzie otwarcia pliku

	if (fscanf(f,  "%d", &atoms_count) != 1) return -1; //Wypluwanie bledu przy bledzie formatu
	coordinate = malloc(atoms_count*sizeof(position_t));
	if (coordinate == NULL) return -1;
	cell = malloc(atoms_count*sizeof(cell_t));
	if (cell == NULL) return -1;


	if (fscanf(f, "%f %f %f", &box.x,
				  &box.y,
				  &box.z) != 3) return -1; //Wypluwanie bledu przy roznej wielkosci
							 	  // pudla obliczeniowego
	int i; //Stala iteratora

	for (i = 0; i <= atoms_count -1; ++i) //Petla iteratora wczytywania danych do tablic
	{
		if (fscanf(f, "%f %f %f",&(coordinate[i].x),
					 &(coordinate[i].y),
					 &(coordinate[i].z)) != 3) return -1; //Wypluwanie bledu przy bledzie formatu

		if ((coordinate[i].x <0) || (coordinate[i].x > box.x)) return -1; //Poza pudlem check
		if ((coordinate[i].y <0) || (coordinate[i].y > box.y)) return -1; //Poza pudlem check
		if ((coordinate[i].z <0) || (coordinate[i].z > box.z)) return -1; //Poza pudlem check
		

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

	printf("X: %f\nY: %f\nZ: %f\n", coordinate[checked_number].x,
					coordinate[checked_number].y,
					coordinate[checked_number].z);
	printf("Pozycja komorki:\nP: %d\nQ: %d\n R: %d\n", cell[checked_number].p,
							   cell[checked_number].q,
							   cell[checked_number].r);
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
	if (getIdx() == -1)
	{	
		printf("Wystapil blad przy wykonywaniu funkcji getIdx");
		return -1;
	}
	if (pointCheck() == -1)
	{
		printf("Wystapil blad przy wykonywaniu fukcji pointCheck"); //Sanity check pointCheck
		return -1;
	}
	if (coordinate != NULL){free(coordinate);}
	if (cell != NULL){free(cell);}
	return 0;
}
