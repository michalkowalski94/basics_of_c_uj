#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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

typedef struct node_t {
	struct node_t *prev;
	struct node_t *next;
	unsigned int val;
}	node_t;
	
typedef struct {
	node_t *head;
	node_t *tail;
} list_t;

list_t *d_direction;
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
	// atoms_count-1 ??
	for (j=0; j < atoms_count; ++j)
	{
		cell[j].p = (int)(coordinate[j].x / (box.x / cell_box.p));
		if (cell[j].p == cell_box.p){cell[j].p--;}


		cell[j].q = (int)(coordinate[j].y / (box.y / cell_box.q));
		if (cell[j].q == cell_box.q){cell[j].q--;}


		cell[j].r = (int)(coordinate[j].z / (box.z / cell_box.r));
		if (cell[j].r == cell_box.r){cell[j].r--;}


	}
	d_direction = malloc(cell_box.p * cell_box.q * cell_box.r * sizeof(list_t));
	if (d_direction == NULL) return -1;
	int i;
	for(i=0; i<(cell_box.p*cell_box.q*cell_box.r); i++)
	{
		d_direction[i].head = (node_t *) NULL;
		d_direction[i].tail = (node_t *) NULL;
	}

	return 0;
}


//Funkcja zmieniajaca indeks komorki na numer 

int cidx2int(cell_t id, cell_t div)
{
	int n = (id.r * (div.p * div.q)) +(id.q * div.p) + id.p;
	return n;
}

int listput(list_t *l, unsigned int val)
{
	node_t *n;
	n = (node_t *) malloc(sizeof(node_t));
	if (n == (node_t *) NULL) return -1;
//	if (n == NULL) return -1;
	n->next = (node_t *) NULL;
	n->prev = l->tail;
	n->val = val;
	if(l->tail == (node_t *) NULL)
		l->head = n;
	else
		l->tail->next = n;
	l->tail = n;
	return 0;	
}


int buildlists(void)
{
	int i;
	for(i=0; i < atoms_count; ++i)
	{
		int c_num = cidx2int(cell[i], cell_box);
		if((c_num < 0) || (c_num > cell_box.p * cell_box.q * cell_box.r)) return -1;
		listput(&(d_direction[c_num]) ,i);		
	}


	return 0;
}

void printlist(list_t *l)
{
	node_t *n;
	int i;
	
	if (l->tail == (node_t *) NULL)
	{
		printf("empty list!\n");
		return;
	}
	
	for(i=0, n=l->head; n; n=n->next, i++){
	printf("element %d holds: %d\n", i, n->val);}
}


int printcell(void)
{ 
	cell_t indeks;
	printf("Podaj indeks X kmorki: ");
	if (scanf("%d", & indeks.p) !=1){
		printf("Wprowadzono ciag znakow nie bedacy liczba calkowita");
		return -1;}
        printf("Podaj indeks Y kmorki: ");
	if (scanf("%d", & indeks.q) !=1){
                printf("Wprowadzono ciag znakow nie bedacy liczba calkowita");
                return -1;}
        printf("Podaj indeks Z kmorki: ");
	if (scanf("%d", & indeks.r) !=1){
                printf("Wprowadzono ciag znakow nie bedacy liczba calkowita");
                return -1;}




	if((indeks.p<0) || (indeks.p>cell_box.p)) return -1;
	if((indeks.q<0) || (indeks.q>cell_box.q)) return -1;
	if((indeks.r<0) || (indeks.r>cell_box.r)) return -1;

	int cell_num = cidx2int(indeks, cell_box); 
	printlist(&(d_direction[cell_num]));
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

	float distance;
	printf("Podaj maksymalny dystans od innych atomow ");
	scanf("%f", &distance);
	int k;
	
	float X1 = coordinate[checked_number].x;	
        float Y1 = coordinate[checked_number].y;
        float Z1 = coordinate[checked_number].z;
	for(k=0; k<=atoms_count; k++)
	{
		float X2 = coordinate[k].x;
		float Y2 = coordinate[k].y;
		float Z2 = coordinate[k].z;

	
		float err1 = pow(X1-X2,2.);
		float err2 = pow(Y1-Y2,2.);
		float err3 = pow(Z1-Z2,2.);
		float sum = err1 + err2 + err3;
		float dist = sqrtf(sum);
		if(dist <= distance){printf("Numer atomu: %d\n",k);}

	}


	return 0;
}



int distanceCompute(void)
{
	int first_number;
	int second_number;
	printf("Podaj numer pierwszego punktu ");
	if (scanf("%d", &first_number) != 1) //Sanity check liczby staloprzecinkowej
	{
		printf("Wprowadzono ciag znakow nie bedacy liczba calkowita\n");
		return -1;
	}
	if (first_number > atoms_count) //Sanity check zakresu
	{
		printf("Podano liczbe wychodzaca poza dopuszczalny zakres\n");
		return -1;
	}
	
	float X1 = coordinate[first_number].x;
	float Y1 = coordinate[first_number].y;
	float Z1 = coordinate[first_number].z;


	printf("Podaj numer drugiego punktu ");
	if (scanf("%d", &second_number) != 1) //Sanity check liczby staloprzecinkowej
	{
		printf("Wprowadzono ciag znakow nie bedacy liczba calkowita\n");
		return -1;
	}
	if (second_number > atoms_count) //Sanity check zakresu
	{
		printf("Podano liczbe wychodzaca poza dopuszczalny zakres\n");
		return -1;
	}

	
	float X2 = coordinate[second_number].x;
	float Y2 = coordinate[second_number].y;
	float Z2 = coordinate[second_number].z;	

	float err1 = pow(X1-X2,2.);
	float err2 = pow(Y1-Y2,2.);
	float err3 = pow(Z1-Z2,2.);
	float sum = err1 + err2 + err3;
	float dist = sqrtf(sum);
	
	printf("Dystans pomiedzy atomem %d a atomem %d wynosi %f\n",first_number,
								    second_number,
								    dist);

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
	if (buildlists() == -1)
	{
		printf("Wystapil blad przy wykonywaniu funkcji getIdx");
		return -1;
	}
	if (printcell() == -1)
	{
		printf("Wystapil blad przy wykonywaniu funkcji printcell");
		return -1;	
	}
	if (distanceCompute() == -1)
	{
		printf("Wystapil blad przy wykonywaniu funkcji distanceCompute"); //Sanity check distanceCompute
		return -1;
	}


	if (coordinate != NULL){free(coordinate);}
	if (cell != NULL){free(cell);}
	
	return 0;
}
