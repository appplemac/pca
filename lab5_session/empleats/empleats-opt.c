#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM 40
#define MAX_DIAS_MES 31
#define MAX_CATEGORIA 40
#define MAX_ADDRESS 100
/*#define EXTES 1*/

typedef struct
{
  long long int NID;              /* Número d'identificació: clau d'ordenació */
  char * Nom;  
  char * Cognoms;  
  int  * horesMes;
  char * Categoria;
  unsigned int ptrClauForaneaDepartament;
  unsigned int ptrClauCategoria;
#ifdef EXTES
  char * Address;
  char * Nom_parella;
  char * Cognoms_parella;
#endif
} Templeat;

int compare(const void *p1, const void *p2)
{
    if (((Templeat*) p1)->NID > ((Templeat*) p2)->NID) return(1);
    else if (((Templeat*) p1)->NID < ((Templeat*) p2)->NID) return(-1);
    else return(0);

}

int main(int argc, char *argv[])
{
  Templeat *empleats;
  unsigned int N = 4000000, i;

  if (argc > 1) N = atoi(argv[1]);

  char * addresses = (char *)malloc(MAX_ADDRESS*N);
  char * couple_names = (char *)malloc(MAX_NOM*N);
  char * couple_surnames = (char *)malloc(MAX_NOM*N);

  int * month_hours = (int *)malloc(MAX_DIAS_MES*N*sizeof(int));
  char * categories = (char *)malloc(MAX_CATEGORIA*N);

  char * names = (char *)malloc(MAX_NOM*N);
  char * surnames = (char *)malloc(MAX_NOM*N);

  empleats = (Templeat *) malloc(N*sizeof(Templeat));
  if (empleats == NULL) { fprintf(stderr, "Out of memory\n"); exit(0); }
  memset(empleats, 0, N*sizeof(Templeat));

  /* Random generation */
  for (i=0; i<N; i++) {
		empleats[i].NID = rand();
    empleats[i].Nom = &names[i];
    empleats[i].Cognoms = &surnames[i];
		empleats[i].Nom[0] = 'A' + ((i>>3) + (i<<2)) & 0x15;
		empleats[i].Cognoms[0] = 'a' + ((i>>2) + (i<<3)) & 0x15;
    empleats[i].horesMes = &month_hours[i];
		empleats[i].horesMes[i % MAX_DIAS_MES] = i;
    empleats[i].Categoria = &categories[i];
		empleats[i].Categoria[i % MAX_CATEGORIA] = (i << 2) * i;
		empleats[i].ptrClauForaneaDepartament = i<<10 + i<<14 + i>>3;
		empleats[i].ptrClauCategoria = i<<24 + i<< 18 + i<<10 + i>>2;
#ifdef EXTES
                empleats[i].Address = &addresses[i];
                empleats[i].Nom_parella = &couple_names[i];
                empleats[i].Cognoms_parella = &couple_names[i];
                empleats[i].Address[0] = 'A' + ((i>>4) + (i<<2)) & 0x15;
                empleats[i].Nom_parella[0] = 'a' + ((i>>5) + (i<<2)) & 0x15;
      empleats[i].Cognoms_parella[0] = 'A' + ((i>>5) + (i<<3)) & 0x15;
#endif
  }

  qsort(empleats, N, sizeof(Templeat), compare);
  for (i=0; i<N; i+=2000){
          write(1, &empleats[i],2000*sizeof(Templeat));
  }

  return 0;
}
