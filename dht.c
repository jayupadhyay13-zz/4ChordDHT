# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>

#define Read            0
#define Write           1
#define ParentRead      read_pipe[0]
#define ParentWrite     write_pipe[1]
#define ChildRead       write_pipe[0]
#define ChildWrite      read_pipe[1]

int main(int args, char *argv[]){

   FILE *file = fopen("key.dat", "r");

   /* Pipe for reading for subprocess */
   int read_pipe[2];
   /* Pipe for writing to subprocess */
   int write_pipe[2];

   int num;
   int fileRead[64];
   int fileSorted[64];
   int fileReadIndex=0; // file index while reading a file
   int fileSortedIndex=0; // secnod array index (after sorting fileSorted from file)
   int nodeIndex=0; // array index for new created node

   int c, d, e, temp; 
  int c1, d1, e1, temp1;

   int menuInput;  // menu menuInput index
   time_t t; // used for random menuInput generator

   int nodeTracker=0; // will calculate how many nodes are inserted

   int newKey; // new inserted key by user

   int index;
   index=0;

   //printf("Before assending order\n");
   //printf("Readed from file and stored into first array\n");
   while(fscanf(file, "%d", &num) > 0)
   {
      fileRead[fileReadIndex] = num;
      fileSorted[fileSortedIndex] = num;
    //printf(" %d - file index %d\n", fileRead[fileReadIndex], i);
    //printf(" %d", fileRead[fileReadIndex]);
      nodeIndex++;
     fileSortedIndex++;
   }
   fclose(file);

   //printf("\n------------------\nReaded from second array (copy) \n");
   //for(int u=0; u<fileSortedIndex;u++){
   //printf("%d ", fileSorted[u]);
   //}
   //printf("\n-----------------------\n");

   void insertKey (int key)
      {
         fileSorted[fileSortedIndex] = key;
         fileSortedIndex++;
         printf("Key added Sucessfully");
      }

   for (c = 0; c < fileSortedIndex; ++c)
   {
      for (d = c + 1; d < fileSortedIndex; ++d)
      {
         if (fileSorted[c] > fileSorted[d])
            {
               temp =  fileSorted[c];
               fileSorted[c] = fileSorted[d];
               fileSorted[d] = temp;
            }
       }
   }

//   printf("The menuInputs arranged in ascending order are given below \n");
//   for (e = 0;  e< fileSortedIndex; ++e)
//   printf(" %d", fileSorted[e]);

/*
I was trying to call fork and creating a parent and child process. However, as soon as I try to call
fork() function, after some moments user input gets duplicated, and then somehow terminal goes into infinite loop and my linux system gets Freezed.

*/ 

// Sample fork call for testing the the parent and child process creation
  void forkCall(void)
   {
      printf("\nProcess ID before fork call: %d\n", (int) getpid());
     
      pid_t pid = fork();
      printf("Fork retured: %d\n", (int) pid);

      if (pid < 0){
      perror("Fork failed");
      }
      if(pid == 0){  
      printf("I am the child pid %d\n", (int) getpid());
      }
      else
      printf("I am the parent\n");

      printf("I am :%d\n", (int) getpid());

     sleep(1);
      
   }

/*
Therefore I use the arrays to store the node values and key values.
*/

   int newNode[64];
   int newNodeIndex = 0;

   // first node is set as 63
   newNode[newNodeIndex] = 63;
   newNodeIndex++;

   void swaping(void)
   {
      for (c1 = 0; c1 <= nodeTracker; ++c1)
      { 
         for (d1 = c1 + 1; d1 <= nodeTracker; ++d1)
         {
            if (newNode[c1] > newNode[d1])
            {
                temp1 = newNode[c1];
                newNode[c1] = newNode[d1];
                newNode[d1] = temp1;
            } 
         }    
      } 
   }

   printf("\n-----Simulation of DHT-----\n");
   printf("Press 1: Create new Node\n");
   printf("Press 2: List Contents\n");
   printf("Press 3: Add Key\n");
   printf("Press 4: Delete Key\n");
   printf("Press 5: Quit Program\n");
   printf("---------------------------\n");

   printf("\ninput = ");
   scanf("%d", &menuInput);

   while(menuInput!=5)
   {
      printf("\n-----Simulation of DHT-----\n");
      printf("Press 1: Create new Node\n");
      printf("Press 2: List Contents\n");
      printf("Press 3: Add Key\n");
      printf("Press 4: Delete Key\n");
      printf("Press 5: Quit Program\n");
      printf("---------------------------\n");
      switch(menuInput)
      {

      case 1:
      printf("create node\n\n");
       
      // generated random numbers for creating nodes in an array.
      srand((unsigned) time(&t));
      newNode[newNodeIndex] = (rand() % 63);
      printf("New Created node = %d\n", newNode[newNodeIndex]);
      printf("Total nodes = %d", newNodeIndex+1); // 63 + new created nodes
      
      newNodeIndex++;
      nodeTracker++;

/*
This is fork function implemented which will generate parent and child process.
Pipe can be set up  for each child process so that each child writes to the parent
communication can be done using the file descriptors

int fileDescriptor[2] ;  -> Defining one file descriptor
  			 -> The number of file descriptors will depend upon the number of pipes we create

fileDescriptor[0]; -> 0 used for reading
fileDescriptor[1]; -> 1 used for writing

First we have to create pipe and then call fork.

I was trying to proceed to create pipes using fork function but as I describe above the function forkCall(), i was unable to go further .

*/

  //    forkCall();

  //    sleep(3);     input was geting duplicated so I put sleep to wait for sometime and try to see if i can able to resovle error for any reason. 

      printf("\ninput = ");
      scanf("%d", &menuInput);
      break;

      case 2:
      printf("\nNode with associated keys created as a List is as given below\n");

      index=0;
      nodeIndex=0;

      swaping();

      for(nodeIndex=0; nodeIndex<=nodeTracker; nodeIndex++)
      {
         if(newNode[nodeIndex] == 0)
         { // node as 0 will be skipped
         	nodeIndex++;
         }

         if(newNode[nodeIndex] == newNode[nodeIndex+1])
         { // this will skip identical nodes
            printf("%d:", newNode[nodeIndex]);
            nodeIndex++;
         }
         else // this will print new created nodes
            printf("%d:", newNode[nodeIndex]);

         // key value less then node value , key grater then 0 , key less than 63
         while(fileSorted[index]<newNode[nodeIndex] && fileSorted[index]>0 && fileSorted[index<63])
         {
            if(fileSorted[index] == 0){
		//printf("Error: key value is found as 0");		
		index++;
	    }
             
	    while(newNode[nodeIndex] == fileSorted[index])
	    { // Identical node value and key value will be skipped	
		index++;
	    }
  
            if(fileSorted[index]==newNode[nodeIndex])
            {
            // this will remove identical value of node and key value
		//printf("Error: identical key value and node value found");
		index++; 
            }
            else
            {
               // this will skip identical key values
               if(fileSorted[index] == fileSorted[index + 1])
               {
                  //printf("Error: identical key value found");
                  index++;
               }
            }// printing key values 
            printf(" %d", fileSorted[index]);
            index++;
         } // end for loop
         printf("\n");
      }

      printf("\ninput = ");
      scanf("%d", &menuInput);
      break;

      case 3:
      printf("add key\n");
 
      printf("\nInsert new key = ");
      scanf("%d", &newKey);

      // insert key into array (fileSorted[fileSortedIndex])
      insertKey(newKey);
      //  printf("New key inserted successfully");


      printf("\ninput = ");
      scanf("%d", &menuInput);
      break;

      case 4:
      printf("delete key\n");
      printf("\ninput = ");
      scanf("%d", &menuInput);
      break;

      case 5:
      printf("quit\n");
      break;

      default:
      printf("Invalid Input\n");
      printf("\ninput = ");
      scanf("%d", &menuInput);
      } // switch case ends

   } // while loop ends

return 0;
}


