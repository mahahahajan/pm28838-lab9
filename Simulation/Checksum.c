#include <stdio.h>
#include <string.h>

int getParity(unsigned int n){
    int parity = 0;
    while (n){
        parity = !parity;
        n = n & (n - 1);
    }       
    return parity;
}

int genChecksumViaParity(char* string){
   int checksum = 0;
   int length = strlen(string);
   for (int i = 0; i < length; i++){
      int bit = getParity(string[i]);
      checksum = checksum << 1;
      checksum |= bit;
   } 
   return checksum;
}

int genChecksumViaAdd(char* string){
   int sum = 0;
   int length = strlen(string);

   for (int i = 0; i < length; i++){
      sum += string[i];
   }
   sum = (-sum) & 0xFF;
   return sum;
}

int main(){
   printf("Checksum using Parity \n");
   char str[] = "Test"; 
   int test1 = genChecksumViaParity(str);
   printf("Checksum for string \'%s\': %d \n\n", str, test1);

   printf("Checksum using Addition \n");
   int test2 = genChecksumViaAdd(str);
   printf("Checksum for string \'%s\': %d \n\n", str, test2);
   
   int sum = 0;
   int length = strlen(str);
   for(int i = 0; i < length; i++){
     sum += str[i]; 
   }
   printf("Sum: %d\n", sum);
   sum = (-sum) & 0xFF;
   sum += test2;
   printf("Testing that it results in 0: %d\n", sum);

   return 0;
}
