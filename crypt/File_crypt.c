/**A program that encrypts text not more than 100,000 characters
 captured from standard input to a file
 */
#include<stdio.h>
#define MAX_NUM_CHAR 100000

int main()
{
    char text[MAX_NUM_CHAR];

//prompt for text from keyboard
    printf("Enter some text:(press enter twice to stop typying)\n");

    for(int i=0;!feof(stdin); i+=1)
       {
           text[i] = getchar();
           //terminating input by capturing the enter key twice
           if(text[i] == 10)
               {
                   if(text[i-1] == 10)
                       {
                           break;
                       }
               }
           
       }

       //encrypt
    for(int i=0; ;i+=1)
       {    
            //end encryption when enter key is consecutively twice
            if(text[i]==10 &&  text[i+1]==10)
                {
                    break;
                }
            // skip the enter and space characters
            else if(text[i] == 10 || text[i]== ' ')
                {
                   continue;

                } 
             text[i] = text[i]+1;
            
            
        }      
    //opening a file for keeping input text from keyboard
    FILE* fp = fopen("ciphertext.dat", "w+");

    if(fp == NULL)
        {
            perror("Error in file opening!!!");
            return(1);
        }

    //puting the encrypted text into the ciphertext file
    for(int i=0;text[i]!=EOF; i+=1)
       {
           if(text[i]==10 &&  text[i+1]==10)
               {
                   break;
               }
           fputc(text[i], fp);
       }
    fclose(fp);  


    return(0);
}