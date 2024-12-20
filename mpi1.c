#include <stdio.h>
#includ <string.h>  
#include <mpi.h>     

int main(void) {
   int comm_sz;  /* Número de processos */
   int my_rank;  /* Rank do processo */

   int a = 9;
   int b = 3;
   
   // P0 ---> r1 + r2*r2 - r3 = ?
   // P1 ---> a + b = r1
   // P2 ---> a - b = r2
   // P3 ---> a * b = r3
   
   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Verificar se há pelo menos 4 processos */
   if (comm_sz < 4) {
      printf("Este programa requer pelo menos 4 processos.\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
   }

   /* Obter rank (id) do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank == 1) {
      int res = a + b;
      printf("Soma de %d e %d = %d\n", a, b, res);
      MPI_Send(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   } else if (my_rank == 2) {
      int res = a - b;
      printf("Subtração de %d e %d = %d\n", a, b, res);
      MPI_Send(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   } else if (my_rank == 3) {
      int res = a * b;
      printf("Multiplicação de %d e %d = %d\n", a, b, res);
      MPI_Send(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   } else if (my_rank == 0){
      int sum = 0;
      for (int q = 1; q < 4; q++) {
         /* Recepção da mensagem do processo q */
         int res;
         MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         sum = sum + res;
      }
      
      
      printf("Resultado FINAL: %d\n", sum);
   }

   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */