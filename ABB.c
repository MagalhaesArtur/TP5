#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABB.h"


struct node {
  int chave;
  char *conteudo;
  No *esq;
  No *dir;
  No *pai;

};
typedef struct node No;




/* Aloca e retorna um No com os dados passados por parâmetro. Retorna no nó
 * criado ou NULL caso não seja posivel criar o nó. */
No *abb_cria_no(int chave, char *conteudo) {
  No *novoNo = (No*) malloc(sizeof(No));

  if(novoNo == NULL){
    printf("Erro de alocacao");
    return NULL;
  }

  novoNo->chave = chave;
  novoNo->conteudo = *conteudo;
  novoNo->dir = NULL;
  novoNo->esq = NULL;
  novoNo->pai = NULL;
  return novoNo;
  
}

/* Libera a memória de um nó e toda as suas sub-árvores. Retorna 1 se for
 * possivel fazer a liberação ou 0 caso o nó seja NULL. */
int abb_libera_no(No *no) {
  if(no != NULL){
    abb_libera_no(no->esq);
    abb_remove_no(no->pai,no->chave);
    abb_libera_no(no->dir);
    return 1;
  }
  return 0;
}

/* Retorna a chave do nó ou -1 caso o nó seja NULL.  */
int abb_chave_no(No *no) {
  if(no == NULL){
    return -1;
  }
  return no->chave;
}

/* Retorna o conteúdo do no ou '#' caso o nó seja NULL. */
char* abb_conteudo_no(No *no) {
    if(no == NULL){
    return "#";
  }
  return no->conteudo;
}

/* Adiciona um nó à esquerda ou à direita do no raiz. Retorna a raiz da árvore
 * resultante ou NULL caso (i) a raiz e o nó sejam NULL e (ii) caso o nó possua
 * mesma chave que outro nó previamente inserido na árvore. */
No *abb_insere_no(No *raiz, No *no) {
  if(raiz == NULL && no == NULL){
    return NULL;
  }else if(raiz == NULL){
   return no;
  }else if(abb_busca_no(raiz,no->chave) == no){
    return NULL;
  }else{
     if(no->chave < raiz->chave){
      inserirEsquerda(raiz,no);
    }else{
      inserirDireita(raiz,no);
    }
  }
}

void inserirEsquerda(No* raiz,No* no){
      if(raiz->esq == NULL){
        no->pai = raiz;
        raiz->esq = no;
      }else{
         if(no->chave < raiz->esq->chave){
          inserirEsquerda(raiz->esq,no);
         }else{
          inserirDireita(raiz->esq,no);
      }
}
}

void inserirDireita(No* raiz,No* no){
      if(raiz->dir == NULL){
        no->pai = raiz;
        raiz->dir = no;
      }else{
          if(no->chave > raiz->dir->chave){
          inserirDireita(raiz->dir,no);
         }else{
          inserirEsquerda(raiz->dir,no);
      }
}
}


void imprimir(No *raiz){

  if(raiz != NULL){

    imprimir(raiz->esq);
    printf("%i\n",raiz->chave);

    imprimir(raiz->dir);

  }
   

}

/* Procura o nó pela chave. Retorna o nó caso a busca obtenha sucesso ou NULL
 * em caso contrário. */
No *abb_busca_no(No *raiz, int chave) {
  if(raiz == NULL){
    return NULL;
  }else{
    if(raiz->chave == chave){
      return raiz;
    }else{
      if(chave < raiz->chave){
        return abb_busca_no(raiz->esq,chave);
      }else{
        return abb_busca_no(raiz->dir,chave);

      }
    }
  }

}


/* Remove o nó com a chave fornecida. Retorna a raiz da arvore atualizada ou
 * NULL em caso a raiz fornecida seja NULL. */
No *abb_remove_no(No *raiz, int chave) {

  if(raiz == NULL){
    return NULL;
  }else{
    if(raiz->chave == chave){
      if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        return NULL;
      }else if(raiz->esq != NULL && raiz->dir != NULL){
        No* aux = raiz->esq;
        while (aux->dir != NULL){
          aux = aux->dir;
        }
        raiz->chave = aux->chave;
        aux->chave = chave;
        raiz->esq = abb_remove_no(raiz->esq,chave);
        return raiz;

        
      }else{
        No* aux;
        if(raiz->esq != NULL){
          aux = raiz->esq;
        }else{
          aux = raiz->esq;
        }
        free(raiz);
        return aux;
      }
    }else{
      if(chave < raiz->chave){
        raiz->esq = abb_remove_no(raiz->esq,chave);
      }else{
        raiz->dir = abb_remove_no(raiz->dir,chave);
      }
      return raiz;
    }
  }
}

/* Retorna a altura da árvore ou -1 caso araiz seja NULL. */
int abb_altura(No *raiz) {
    if(raiz == NULL){
    return -1;
  }else{
    int esq = abb_altura(raiz->esq);
    int dir = abb_altura(raiz->dir);
    if(esq > dir){
      return esq + 1;
    }else{
      return dir + 1;
    }

  }
}

/* Retorna o número de nós da árvore ou -1 caso araiz seja NULL. */


int abb_numero(No *raiz) {
  int *aux;
  int r = 0;
  aux = &r;

  if(raiz == NULL){
    return -1;
  }

  abb_numero_aux(raiz,aux);
  printf("%i",r);


}

int abb_numero_aux(No *raiz, int* num){
  if(raiz != NULL){

    abb_numero_aux(raiz->esq,num);
    *num = *num + 1;

    abb_numero_aux(raiz->dir,num);
  }
  

  

}


char *abb_pre_ordem_aux(No *no,char* texto){

  if(no != NULL){
  char ff[20]= "";
  converterChar(no,ff);
  strcat(texto,ff);
  abb_pre_ordem_aux(no->esq,texto);
  abb_pre_ordem_aux(no->dir,texto);

  }
}

char *abb_ordem_aux(No *no,char* texto){

   if(no != NULL){
  char ff[20]= "";
  abb_ordem_aux(no->esq,texto);
  converterChar(no,ff);
  strcat(texto,ff);
  abb_ordem_aux(no->dir,texto);

  }
}

char *abb_pos_ordem_aux(No *no,char* texto){

  if(no != NULL){



  char ff[20]= "";
  abb_pos_ordem_aux(no->esq,texto);
 
  abb_pos_ordem_aux(no->dir,texto);
  converterChar(no,ff);
  strcat(texto,ff);

  }
}


/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pré-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */

char *abb_pre_ordem(No *no) {
  if(no== NULL){
    return "#";
  }
char texto[100] = "";
  char* res=(char*) malloc(abb_numero(no)*sizeof(char));
  abb_pre_ordem_aux(no,texto);
  for(int i = 0; i< strlen(texto);i++){
  res[i] = texto[i];
  }
  return res;

}



/*Retorna a concatenação do conteúdo da árvore fazendo percurso em ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_ordem(No *no) {
  if(no== NULL){
    return "#";
  }
  char texto[100] = "";
  char* res=(char*) malloc(abb_numero(no)*sizeof(char));
  abb_ordem_aux(no,texto);
  for(int i = 0; i< strlen(texto);i++){
  res[i] = texto[i];
  }
  return res;
}

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pós-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pos_ordem(No *no) {
  if(no== NULL){
    return "#";
  }
  char texto[100] = "";
  char* res=(char*) malloc(abb_numero(no)*sizeof(char));
  abb_pos_ordem_aux(no,texto);
  for(int i = 0; i< strlen(texto);i++){
  res[i] = texto[i];
  }
  return res;
}




void converterChar(No *no, char x[2]){
 
  char a[2] = "a";
  char b[2] = "b";
  char c[2] = "c";
  char d[2] = "d";
  char e[2] = "e";
  char f[2] = "f";
  char g[2] = "g";
  char h[2] = "h";
  char ii[2] = "i";
  char j[2] = "j";
  char k[2] = "k";
  char l[2] = "l";
  char m[2] = "m";
  char n[2] = "n";
  char o[2] = "o";
  char p[2] = "p";
  char q[2] = "q";
  char r[2] = "r";
  char s[2] = "s";
  char t[2] = "t";
  char u[2] = "u";
  char v[2] = "v";
  char w[2] = "w";
  char xx[2] = "x";
  char y[2] = "y";
  char z[2] = "z";

if(no->conteudo ==   (char*) 'a'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = a[i];
    }
  }

  if(no->conteudo ==  (char*) 'b'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = b[i];
    }
  }

   if(no->conteudo == (char*) 'c'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = c[i];
    }
  }

   if(no->conteudo == (char*) 'd'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = d[i];
    }
  }

   if(no->conteudo == (char*) 'e'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = e[i];
    }
  }

   if(no->conteudo == (char*) 'f'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = f[i];
    }
  }

   if(no->conteudo == (char*) 'g'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = g[i];
    }
  }

   if(no->conteudo == (char*) 'h'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = h[i];
    }
  }

   if(no->conteudo == (char*) 'i'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = ii[i];
    }
  }

   if(no->conteudo == (char*) 'j'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = j[i];
    }
  }

   if(no->conteudo == (char*) 'k'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = k[i];
    }
  }

   if(no->conteudo == (char*) 'l'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = l[i];
    }
  }

   if(no->conteudo == (char*) 'm'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = m[i];
    }
  }

   if(no->conteudo == (char*) 'n'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = n[i];
    }
  }

   if(no->conteudo == (char*) 'o'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = o[i];
    }
  }

   if(no->conteudo == (char*) 'p'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = p[i];
    }
  }

   if(no->conteudo == (char*) 'q'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = q[i];
    }
  }

   if(no->conteudo == (char*) 'r'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = r[i];
    }
  }


   if(no->conteudo == (char*) 's'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = s[i];
    }
  }

   if(no->conteudo == (char*) 't'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = t[i];
    }
  }

   if(no->conteudo == (char*) 'u'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = u[i];
    }
  }

   if(no->conteudo == (char*) 'v'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = v[i];
    }
  }

   if(no->conteudo == (char*) 'w'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = w[i];
    }
  }

   if(no->conteudo == (char*) 'x'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = xx[i];
    }
  }

   if(no->conteudo == (char*) 'y'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = y[i];
    }
  }

   if(no->conteudo == (char*) 'z'){
    for(int i = 0; i< strlen(a); i++){
      x[i] = z[i];
    }
  }
 

  

}

