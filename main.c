#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int ID;
  double x;
  double y;
} Cidade;

int calcular_distancia(Cidade c1, Cidade c2){
  return floor( 0.5 + sqrt((((c1.x - c2.x) * (c1.x - c2.x)) + ((c1.y - c2.y) * (c1.y - c2.y)))));
}

void fazendo_vizinho_mais_proximo(Cidade *cidades, int dimens, int *rota){
  int *visitadas;
  visitadas = (int*) malloc(dimens * sizeof(int));

  for(int i=0; i<dimens; i++){
    visitadas[i] = 0;
  }

  int cidadeAtual = 0;

  rota[0] = cidades[cidadeAtual].ID;

  visitadas[cidadeAtual] = 1;
  int cidadesVisitadas_count = 1;

  while(cidadesVisitadas_count < dimens){
    int id_mais_proximo = -1;
    double menor_distancia = INFINITY;

    for(int i=0; i< dimens; i++){
      if (visitadas[i] == 0)
      {
        double distanc = calcular_distancia(cidades[cidadeAtual], cidades[i]);

        if(distanc < menor_distancia){
          menor_distancia = distanc;
          id_mais_proximo = i;
        }
      }

      cidadeAtual = id_mais_proximo;
      rota[cidadesVisitadas_count] = cidades[cidadeAtual].ID;
      visitadas[cidadeAtual] = 1;

      cidadesVisitadas_count ++;
    }

    free (visitadas);

    
    
  }
  

}

int main(){
  int dimens = 0;

  while (1){

  char palavra[50];
    scanf("%s", palavra);
    if (strcmp(palavra, "DIMENSION") == 0){
      scanf("%d", &dimens);
      break;
    }
  }

  Cidade *cidades;
  cidades = (Cidade*) malloc(dimens * sizeof(Cidade));

  while(1){
    char palavra[50];
    scanf("%s", palavra);
    if(strcmp(palavra, "NODE_COORD_SECTION") ==0){  
      break;
    }
  }
  for(int i=0; i<=dimens; i++){
    scanf("%d %lf %lf", cidades->ID, cidades->x, cidades->y);
  }

  int *rota;
  rota = (int*) malloc(dimens * sizeof(int));

  vizinho_mais_proximo(cidades, dimens, rota);

  printf("NAME: ch150\n");
  printf("TYPE: \n");
  printf("DIMENSION: \n");
  printf("COMMENT: Kauã, Hitalecio, Leticia. Vizinho mais proximo\n");

  printf("TOTAL WEIGHT: ");
  int custo_total = 0;
  for(int i=0; i<dimens; i++){
    int id_cidadeAtual = rota[i];
    int id_cidadePosterior = rota[i + 1];

    Cidade cidade_a = cidades[id_cidadeAtual - 1];
    Cidade cidade_b = cidades[id_cidadePosterior - 1];

    custo_total += calcular_distancia(cidade_a, cidade_b);
  }
  custo_total += calcular_distancia(cidades[rota[dimens - 1] - 1], cidades[rota[0] - 1]);

  printf("%d", custo_total);

  printf("TOUR SECTION\n");
  for(int i=0; i<dimens - 1; i++){
    printf("%d\n, rota[i]");
  }
  printf("EOF");

  free(cidades);
  free(rota);




}