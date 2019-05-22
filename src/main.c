#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 3
#define MAX_SIZE 64

pthread_mutex_t trava;
int primo = 0;

void* verifica_primo(void *argumento){ // Função que verifica se um determinado número é primo ou não.

	int x = 0,j = 2, fail = 0, aux = 0;

	x = *(int *)argumento;
	
	while (j < 10 && fail == 0){  // Caso tal número seja divisível por algum valor inferior a 10 ou seja igual a 1, podemos concluir que o mesmo não é primo com a varáivel fail.
	      
	  
	      pthread_mutex_lock(&trava);	      
	      

	      if (((x % j == 0) && (j != x)) || (x == 1))
		    fail = 1; 	      
	      
	      else if (j == 9)		
		    primo++;			
	      
	      pthread_mutex_unlock(&trava);
	      
	      j++;					

	 }

 	 return NULL;
}

int main (){

	int i = 0, k = 0, qtde_num = 0, indice = 0, num[MAX_SIZE];
	pthread_t thread[MAX_THREADS];

	while (scanf("%d", &num[i]) != (-1)){ 
		i++;    
		(qtde_num)++;
	}  

        i = 0;
      
	while (indice < qtde_num){
	      	
	      if (i < MAX_THREADS){ // Cria Thread para cada número a ser verificado se o número de threads existentes forem menores que 4
	      	 pthread_create(&(thread[i]), NULL, verifica_primo, (void*) (&num[indice]));
		 i++;
	    	 indice++;
	     }
		
	     else{
		for (i = 0; i < MAX_THREADS; i++) // Caso existam três threads em operação e mais números a serem analisados. Espera as threads em operação encerrarem.
		    pthread_join(thread[i],NULL);

		i = 0;		
	     }
	    	      
	}

	k = i;

	for (k = 0; k < i; k++) // Encerra todas as threads em operação
	     pthread_join(thread[k],NULL); 
	
	printf("%d\n", primo); // Informa a quantidade de números primos existentes.

	return 0;

}
