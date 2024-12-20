#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

int main(void) {
   int        comm_sz;               /* Número de processos    */
   int        my_rank;               /* Rank   do processo     */
   
   
   int a = 9;
   int b = 3;
   
      /*
   p0 -> r1 + r2*r2 - r3
   p1 -> r1 = a + b 
   p2 -> r2 = a -b 
   p3 -> r3 = a *b
   */

   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   
   if (comm_sz < 4) {
      printf("Este programa requer pelo menos 4 processos.\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
   }

   /* Obter rank (id) do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
   
   if(my_rank == 0){
      MPI_Status status; 
      
      int sum = 0;
      for (int q = 1; q < 4; q++) { 
         
         int res;
         
         MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         
         if(status.MPI_SOURCE == 1){
            
            sum += res;
         }
         else if(status.MPI_SOURCE == 2){
            sum += res * res;
         }
         else{
            sum -= res;
         }
         
         
         
      }
      
         printf("p0 = : %d \n",sum);

      
   }
   else{
      
      int res;
      
      
      if(my_rank == 1){
         res = a + b;
         MPI_Send(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
         
      }
      else if(my_rank == 2){
          res = a - b;
         MPI_Send(&res,1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
      }
         
      else if(my_rank == 3){
          res = a * b;
         MPI_Send(&res,1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
         
      }

   }

   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
