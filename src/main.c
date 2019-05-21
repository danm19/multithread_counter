#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS

pthread_mutex_t trava;
int primo = 0;

void* verifica_primo(void *argumento){ // Função que verifica se um determinado número é primo ou não.

	int x = 0,j = 2, fail = 0, aux = 0;

	x = *(int *)argumento;

	while (j < 10 && fail == 0){  // Caso tal número seja divisível por algum valor inferior a 10 ou seja igual a 1, podemos concluir que o mesmo não é primo com a varáivel fail.
	      
	      pthread_mutex_lock(&trava);

	      if (((x % j == 0) && (j != x)) || (x == 1)){ 
		    fail = 1; 
		 
	      }
	      
	      else if (j == 9)		
		    primo += 1;			
	      
	      pthread_mutex_unlock(&trava);
	      
	      j++;					

	 }

 return NULL;

}

int main (){

	int i = 0, qtde_num = 0, vet_aux, indice = 0, num[64];
	pthread_t thread[3];

	qtde_num = 0;
	indice = 0;

	while (scanf("%d", &num[i]) != (-1)){ 
		i++;    
		(qtde_num)++;
	}  

	i = 0;	

	while (indice < qtde_num){
	      
	      if (i < 3){
	      	 pthread_create(&(thread[i]), NULL, verifica_primo, (void*) (&num[indice]));
		 pthread_join(thread[i],NULL);
		 i++;
	     }
		
	     else{
		i = 0;
		indice--;
	     }
	    
	     indice++;   
	}
	
	printf("%d\n", primo);

	return 0;

}


