#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//definicja typu struktury
typedef struct {
  float x;
  float y;
  float z;
} pos_t;

//indeks komórki w pudełku obliczeniowym
typedef struct {
  unsigned int p;
  unsigned int q;
  unsigned int r;
} cell_t;

//typ strukturalny elementu listy
typedef struct node_t {
  struct node_t *prev;
  struct node_t *next;
  unsigned int val;
} node_t;

//typ strukturalny listy
typedef struct {
  node_t *head;
  node_t *tail;
} list_t;

//tabela typu pos_t (zmienna-tablica-polozenia)
pos_t *tab;

//N atomów (zmienna-przechowujaca-ilosc-atomow)
int ile_at;

//wymiary pudełka obliczeniowego
pos_t calcbox;

//ilosc-komorek-w-ukladzie
unsigned int ile_kom = 0;

//tablica indeksów komórek (zmienna indeksy komórek)
cell_t *id;

//sposób podziału pudła obliczeniowego na komórki (zmienna podziału pudła)
cell_t division;

//deklaracja listy (zmienna-tablica-list)
list_t *l_tab;



//////////////////////////////////////////////////////////////////////////////////////////

//funkcja wypisująca kordynaty konkretnego atomu
int printCoords (void){
//numer zmiennej
  int n;
  printf("Podaj numer punktu: ");
  if (scanf("%d", &n) != 1 && n <= ile_at) {
  printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
  return -1;
  }
//wypisanie kordynatów
  printf("X: %f\nY: %f\nZ: %f\n", tab[n-1].x, tab[n-1].y, tab[n-1].z);

//wypisanie indeksów
  printf("Komorka = P: %d\nQ: %d\nR: %d\n", id[n-1].p, id[n-1].q, id[n-1].r);

  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////

//funkcja czytajaca plik
int readData (char *filename){
//deklaracja zmiennej f jako pliku
  FILE *f;
//otwarcie f
  f=fopen(filename, "r");
  if (f == NULL) return -1;

//odczytanie liczby atomów
  if (fscanf(f, "%d", &ile_at) != 1) return -1;

//przydzielanie pamięci dla tabeli współrzędnych
  tab = (pos_t*) malloc (ile_at * sizeof(pos_t));
  if (tab == NULL) return -1;

//przydzielenie pamięci dla tabeli inteksów komórek
  id = (cell_t*) malloc (ile_at * sizeof(cell_t));
  if (id == NULL) return -1;

//odczytanie wielkosci pudelka obliczeniowego
  if (fscanf(f, "%f %f %f", &calcbox.x, &calcbox.y, &calcbox.z) != 3) return -1;

//przypisanie kordynatów do tabel
  for (int i=0;i < ile_at-1;i++){
    if (fscanf(f, "%f %f %f", &(tab[i].x), &(tab[i].y), &(tab[i].z)) != 3) return -1;
//sprawdzenie kordynatów czy mieszczą się w pudełku obliczeniowym
    if ((tab[i].x < 0) || (tab[i].x > calcbox.x)) return -1;
    if ((tab[i].y < 0) || (tab[i].y > calcbox.y)) return -1;
    if ((tab[i].z < 0) || (tab[i].z > calcbox.z)) return -1;
  }

//zamknięcie f
  fclose(f);
  return 0;

}
//////////////////////////////////////////////////////////////////////////////////////////

//funkcja wyznaczająca indeksy komórek dla kazdego atomu w układzie
int idFunc (void) {

//wczytywanie ilości podzialów pudła obliczeniowego
  printf("Podaj ilosc podzialow pudla obliczeniowego wzdluz osi X: ");
  if (scanf("%d", &division.p) != 1) {
    printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
    return -1;
  }
  printf("Podaj ilosc podzialow pudla obliczeniowego wzdluz osi Y: ");
  if (scanf("%d", &division.q) != 1) {
    printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
    return -1;
  }
  printf("Podaj ilosc podzialow pudla obliczeniowego wzdluz osi Z: ");
  if (scanf("%d", &division.r) != 1) {
    printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
    return -1;
  }

  ile_kom = division.p*division.q*division.r;

//pętla przypisująca indeksy do tablicy globalnej
for (int i = 0; i<ile_at; i++){

  id[i].p = (int) (tab[i].x / (calcbox.x/division.p));
  if (id[i].p == division.p)
  id[i].p--;

  id[i].q = (int) (tab[i].y / (calcbox.y/division.q));
  if (id[i].q == division.q)
  id[i].q--;

  id[i].r = (int) (tab[i].z / (calcbox.z/division.r));
  if (id[i].r == division.r)
  id[i].r--;
  }

//przydzielenie pamięci dla TABLICY LIST inteksów komórek
  l_tab = (list_t*) malloc (ile_kom * sizeof(list_t));
  if (l_tab == NULL) return -1;

  for(int i=0; i<ile_kom; i++) {
    l_tab[i].head = (node_t *) NULL;
    l_tab[i].tail = (node_t *) NULL;
  }

  return ile_kom;
}

//////////////////////////////////////////////////////////////////////////////////////////

//funkcja zwracająca numer wskazanej komórki w pudle obliczeniowym
unsigned int cidx2int (cell_t ide, cell_t divx) {

int n = 0;
n = ide.r*(divx.p*divx.q)+ide.q*divx.p+ide.p;
return n;
}

//////////////////////////////////////////////////////////////////////////////////////////
//      funkcje listy


//wrzucenie na ogon
int listPut (list_t *l, unsigned int val) {
  node_t *n;
  n = (node_t *) malloc(sizeof(node_t));
  if (n == (node_t *) NULL)
    return -1;
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

/////////////////////////////////////////
//zbudowanie listy indeksów (przypisanie wartości do listy)
int buildLists () {
  for (int i=0; i<ile_at; i++){
    int num = cidx2int (id[i], division);
    if (num < 0) return -1;
    if ((listPut(&(l_tab[num]), i)) != 0) return -1;
  }
  return 0;
}

/////////////////////////////////////////
//wypisanie listy na ekran
void printList (list_t *l) {
  node_t *n;
  int i;
  if (l->tail == (node_t *) NULL) {
    printf("empty list!\n");
    return;
  }
    for(i = 0, n=l->head; n; n=n->next, i++)
    printf("Element %d: Atom [%d]\n", i, n->val+1);
  return;
}

/////////////////////////////////////////
//wypisanie komórki na ekran
int printCell () {
  int cell_id;
  cell_t a;

  //wczytywanie ilości podzialów pudła obliczeniowego
  printf("Indeks X: ");
  if (scanf("%d", &a.p) != 1) {
    printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
    return -1;
  }
  printf("Indeks osi Y: ");
  if (scanf("%d", &a.q) != 1) {
    printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
    return -1;
  }
  printf("Indeks Z: ");
  if (scanf("%d", &a.r) != 1) {
    printf("Wprowadzono ciąg znaków nie bedacy liczba calkowita");
    return -1;
  }

//wyliczenie numeru komórki podziałowej i wypisanie jej zawartości na ekran
  cell_id = cidx2int (a, division);
  printList (&(l_tab[cell_id]));
  return 0;
}

/////////////////////////////////////////
//usunięcie listy
void listFree (list_t *l){
  node_t *n;
  if (l->tail == (node_t *) NULL)
    return;
  while (l->tail != (node_t *) NULL){
    n = l->tail;
    l->tail = l->tail->prev;
    free (n);
  }
  l->head = (node_t *) NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
/*
//obliczanie odległości między atomami a i b
  float distanceCalc (pos_t at, int b) {
    float result = 0;
    float component[3];
    for (int i = 0; i<3; i++){
      component[i] = 0;
    } 
    component[0] = ((at.x-tab[b].x)*(at.x-tab[b].x));
    component[1] = ((at.y-tab[b].y)*(at.y-tab[b].y));
    component[2] = ((at.x-tab[b].z)*(at.z-tab[b].z));
    result = sqrt(component[0]+component[1]+component[2]);
    return result;
  }
*/
//////////////////////////////////////////////////////////////////////////////////////////

int neighborsFromCell (pos_t at, list_t *l_1, float r1, list_t *l_result){
  node_t *n;
  float result = 0;
  int i;
  
  for (i = 0, n = l_1->head; n ; i++, n=n->next) 
  {
    float component[3];
    for (int j = 0; j<3; j++){
      component [j] = 0;
    } 
    
    component[0] = ((at.x-tab[i].x)*(at.x-tab[i].x));
    component[1] = ((at.y-tab[i].y)*(at.y-tab[i].y));
    component[2] = ((at.x-tab[i].z)*(at.z-tab[i].z));
    result = sqrt(component[0] + component[1] + component[2]);
    
    if (result <= r1 && result > 0) {
      printf ("%f\n", result);
      listPut (l_result, n->val);
    }
  }
  return 0;
}   

//////////////////////////////////////////////////////////////////////////////////////////

//int neighbors (unsigned int (numer atomu w układzie), 
//float (promień odcięcia), list_t *t);
int neighbors (unsigned int a, float r1, list_t *l_result) {
  cell_t id_result = id[a];
  int i, ii, j, jj, k, kk; 

  if (id_result.p > 0) ii = id_result.p-1;
  else ii = id_result.p;
  if (id_result.q > 0) jj = id_result.q-1;
  else jj = id_result.q;
  if (id_result.r > 0) kk = id_result.r-1;
  else kk = id_result.r;

  for (i=ii; (i<=id_result.p+1) && (i<division.p); i++)
    for (j=jj; (j<=id_result.q+1) && (j<division.q); j++)
      for (k=kk; (k<=id_result.r+1) && (k<division.r); k++) {
        cell_t neighbors_id;
          neighbors_id.p=i;
          neighbors_id.q=j;
          neighbors_id.r=k;

        unsigned int id_ijk = cidx2int(neighbors_id, division);
        
        if (neighborsFromCell(tab[a], &l_tab[id_ijk], r1, l_result) != 0) return -1;
      }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

//funkcja wypisujaca kordynaty konkretnego atomu
int printngh (void){
//numer zmiennej
  int v;
  list_t *atomlist;
//promien odciecia
  float r2;

//inicjalizacja listy
  atomlist = (list_t*) malloc (sizeof(list_t));
  atomlist->head = (node_t *) NULL;
  atomlist->tail = (node_t *) NULL;

//wczytanie numeru atomu
  printf("Podaj numer atomu: ");
    if (scanf("%d", &v) != 1) {
      printf("Wprowadzono ciąg znaków nie bedacy liczba staloprzecinkowa");
      return -1;
    }  else if (v < 0 || v > ile_at){
      printf("Wprowadzony numer nie miesci sie w dopuszczalnym zakresie");
      return -1;
    }

//wczytanie promienia odciecia
  printf("Podaj promien odciecia: ");
    if (scanf("%f", &r2) != 1) {
      printf("Wprowadzono ciąg znaków nie bedacy liczba zmiennoprzecinkowa");
      return -1;
    } else if ((r2 >= (calcbox.x/division.p)) || 
               (r2 >= (calcbox.y/division.q)) ||
               (r2 >= (calcbox.z/division.r))) {
      printf("Promien odciecia jest wiekszy od dlugosci krawedzi komorek w ukladzie");
      return -1;
    }
  if ((neighbors (v, r2, atomlist)) != 0){ 
    return -1;
  } else { 
    printList (atomlist); 
  }
  listFree (atomlist);
  free (atomlist);
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
//  char filename[512];

//URUCHAMIANIE! ./a.out
//coords.dat

/*  printf("Podaj nazwę pliku: ");

  if (scanf("%s", filename) != 1) {
    printf("Blad w nazwie pliku\n");
    return -1;
  }*/

//URUCHAMIANIE! ./a.out coords.dat


  readData /*(filename)*/(argv[1]);
  ile_kom = idFunc();
  if (ile_kom < 0) return -1;
    
  printCoords ();
  buildLists ();
  printCell ();
  if (printngh () != 0) return -1;



//zwalnianie pamięci przydzielonej dla tablicy list
  for (int i = 0; i<ile_kom ;i++){
    listFree (&(l_tab[i]));
  }
  free (l_tab);
//zwalnianie pamięci przydzielonej dla tabeli współrzędnych
  if (tab != NULL)
  free (tab);
//zwalnianie pamięci przydzielonel dla tabeli indeksów komórek
  if (id != NULL)
  free (id);
  return 0;
}
































