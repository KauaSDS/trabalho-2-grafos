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
    }
      cidadeAtual = id_mais_proximo;
      rota[cidadesVisitadas_count] = cidades[cidadeAtual].ID;
      visitadas[cidadeAtual] = 1;

      cidadesVisitadas_count ++;
   
    
  }
  free (visitadas);
}


void otimizacao_2opt(Cidade *cidades, int dimens, int *rota){
  int melhorou;
  do{
    melhorou = 0;

  for(int i=1; i<dimens - 1; i++){
    for(int j=i+1; j<dimens; j++){
      int id_a = rota[i-1];
      int id_b = rota[i];
      int id_c = rota[j];
     int id_d = rota[(j+1) % dimens];

     Cidade cidA = cidades[id_a - 1];
     Cidade cidB = cidades[id_b - 1];
     
     Cidade cidC = cidades[id_c - 1];
     Cidade cidD = cidades[id_d - 1];

     int distanciaAntiga = calcular_distancia(cidA, cidB) + calcular_distancia(cidC, cidD);
     
     int distanciaNova = calcular_distancia(cidA, cidC) + calcular_distancia(cidB, cidD);

     int ehMelhor = distanciaNova - distanciaAntiga;



     if(ehMelhor < 0){
     int esquerda = i;
     int direita = j;
      while(esquerda < direita){
        int temp = rota[esquerda];
        rota[esquerda] = rota[direita];
        rota[direita] = temp;

        esquerda++;
        direita--;
      }
        melhorou = 1;
        break;
    
     }
    }
     if(melhorou){
      break;
     } 
    
  }
  }while(melhorou ==1);
}

int main(){
  int dimens = 0;
  while (1){

  char palavra[50];
    scanf("%s", palavra);
    if (strcmp(palavra, "DIMENSION:") == 0){
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
  for(int i=0; i<dimens; i++){
    scanf("%d %lf %lf", &cidades[i].ID, &cidades[i].x, &cidades[i].y);
  }

  int *rota;
  rota = (int*) malloc(dimens * sizeof(int));

  fazendo_vizinho_mais_proximo(cidades, dimens, rota);
  otimizacao_2opt(cidades, dimens, rota);

  printf("NAME: ch150\n");
  printf("TYPE: TOUR\n");
  printf("DIMENSION: %d\n", dimens);
  printf("COMMENT: Kauã, Hitalecio, Leticia. Vizinho mais proximo\n");

  printf("TOTAL WEIGHT: ");
  int custo_total = 0;
  for(int i=0; i<dimens - 1; i++){
    int id_cidadeAtual = rota[i];
    int id_cidadePosterior = rota[i + 1];

    Cidade cidade_a = cidades[id_cidadeAtual - 1];
    Cidade cidade_b = cidades[id_cidadePosterior - 1];

    custo_total += calcular_distancia(cidade_a, cidade_b);
  }
  int id_ultimaCidade = rota[dimens - 1];
  int id_primeiraCidade = rota[0];

  Cidade ultima_Cidade = cidades[id_ultimaCidade - 1];
  Cidade primeira_Cidade = cidades[id_primeiraCidade - 1];

  custo_total += calcular_distancia(ultima_Cidade, primeira_Cidade);

  printf("%d\n", custo_total);

  printf("TOUR_SECTION\n");
  for(int i=0; i<dimens; i++){
    printf("%d\n", rota[i]);
  }
  printf("EOF");

  free(cidades);
  free(rota);


}