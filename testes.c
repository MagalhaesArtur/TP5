#include <stdio.h>
#include "ABB.h"
#include <string.h>


int main(void) {
 
  No* No2 = abb_cria_no(20,"b");
    

  No* No1 = abb_cria_no(15,"v");
  No* No3 = abb_cria_no(44,"g");
  No* No4 = abb_cria_no(35,"h");
  No* No5 = abb_cria_no(34,"l");
  No* No6 = abb_cria_no(300,"x");
  No* No7 = abb_cria_no(334,"y");

  abb_insere_no(No2,No6);
  abb_insere_no(No2,No5);
  abb_insere_no(No2,No1);
  abb_insere_no(No2,No4);
  abb_insere_no(No2,No7);
  abb_insere_no(No2,No3);


  // No* no;
  // no = abb_busca_no(No2, 66);

  imprimir(No2);
  // abb_numero(No2);
  abb_libera_no(No6);
  // abb_numero(No2);

  imprimir(No2);



  return 0;
}