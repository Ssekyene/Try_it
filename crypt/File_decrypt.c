/**A program to decrypt each line in the ciphertext file*/
#include <stdio.h>
#define MAX_LINE_LENGTH 1024

int main() {
    FILE *file1 = fopen("ciphertext.dat", "r"); // open file in read mode
    if (file1 == NULL) 
        {
            perror("Error opening file1");
            return 1;
        }
    FILE* file2 = fopen("plaintext.dat","w+");// open file in read and write mode
         if (file2 == NULL) 
            {
                perror("Error opening file2");
                return 1;
            }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file1) != NULL) // read each line in the file
        { 
            for (int i = 0;line[i] !='\0'; i += 1)
                {

                    if(line[i]!= ' ')//space character excluded
                        {
                            if(line[i]=='\n')
                                {
                                    line[i] ==10;//enter character(new line)
                                }
                            else// decrypting the characters  
                                {
                                    line[i] = line[i] - 1;
                                }    
                        }
        
                }
            fprintf(file2,"%s", line); // print the line to file2(plaintext)
        }

    // close the files
    fclose(file1); 
    fclose(file2);
    return 0;
}
