#include <stdio.h>
#include <math.h>
#include <string.h>
void printPowerSet(char set[][1000], int set_size)
{
  char data;
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
  int counter, j,i,n;
  int powerset_size=pow(2,set_size); //variable used to store the size of the power set
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
  printf("Powerset: {"); //starting the power set
  for(i=0; i<powerset_size;i++){ //for every number from 0 until the powerset size
    n=i;
    printf(" {");
    for(j=set_size-1; j>=0;j--){ 
      if ((n-pow(2,j))>=0){ 
        for(counter=0;counter<strlen(set[j])-1;counter++){
          printf("%c",set[j][counter]);
         data=set[j][counter];
        }
        n-=pow(2,j);
        if(n>0)
          printf(",");
      }
  }
  printf("}");
  if(i<(powerset_size-1))
    printf(", ");
  }
 printf("} ");

}
/*Driver program to test printPowerSet*/
int main()
{
    int i=-1, j=0; //initialise variables
    char set[1000][1000]; //allocate memory for a 2D array(an array of strings)
    printf("Enter a set( terminate by leaving a single space as the last element):\n");
    do{
      i++;
      fgets(&set[i][0], sizeof(set), stdin); //inputing an element of the set as a string form
    }while(set[i][0]!=' '); //if the string is not a space input another element

    //TESTING-used to output the set once entered- feedback that it is correct
  /* while(set[j][0]!='\0'){
      puts(set[j]);
      j++;
    }*/
    printPowerSet(set, i);//call the function to calculate and print the power set

    return 0;
}
