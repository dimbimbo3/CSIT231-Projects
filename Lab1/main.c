#include <stdio.h> //io
#include <stdlib.h> //exit()
#include <ctype.h> //toupper()

//global variables
FILE *fptr1, *fptr2;
char fname1[] = "input.txt";
char fname2[] = "output.txt";
char nextChar;

//function declarations
void encode();
void decode();

int main() {
  char input[100];
  printf("Input the message to be written to input.txt:\n");
	fgets(input, 100, stdin); //retrieves user input

  //switch user input to upper case
  for (int i = 0; i < 100; i++) {
    input[i] = toupper(input[i]);
  }

  //opens input.txt
  fptr1 = fopen(fname1, "w"); //write access
	if (fptr1 == NULL){
		printf("File does not exist or cannot be opened.");
		exit(0);
	}

  fprintf(fptr1,"%s",input); //writes input string to input.txt
	fclose(fptr1); //closes input.txt
  printf("\n"); //newline for formatting

  encode();
  decode();
  
  return 0;
}

void encode(){
  char encoded;

  //opens input.txt
  fptr1 = fopen(fname1, "r"); //read acccess
	if (fptr1 == NULL){
		printf("File does not exist or cannot be opened.");
		exit(0);
	}

  //opens output.txt
  fptr2 = fopen(fname2,"w"); //write access
  if(fptr2 == NULL){
    printf("File does not exist or cannot be opened.");   
    exit(0);             
  }

	printf("The encoded message of %s is:\n",fname1);
	nextChar = fgetc(fptr1); //retrieves first char from 1st file
  //loops until end of file is found
	while (nextChar != EOF){
    //checks if the character is a letter or a punctuation
    if(nextChar >= 65 && nextChar <= 90){
      //if a letter, then stores the letter+3 in encoded, however if the letter+3 would go past Z then it is set manually
      switch(nextChar){
        case'X': encoded = 'A'; break;
        case'Y': encoded = 'B'; break;
        case'Z': encoded = 'C'; break;
        default: encoded = nextChar + 3;
      }
    }
    else{
      //else it is a puncutuation and is not changed
      encoded = nextChar;
    }

    printf("%c",encoded); //prints char to console
		fprintf(fptr2,"%c",encoded); //writes char to 2nd file
		nextChar = fgetc(fptr1); //retrieves next character from 1st file
	}
  
  printf("\n"); //newline for formatting

  //closes file streams
	fclose(fptr1);
  fclose(fptr2);
}

void decode(){
  char decoded;

  //opens output.txt
  fptr2 = fopen(fname2, "r"); //read access
	if (fptr2 == NULL){
		printf("File does not exist or cannot be opened.");
		exit(0);
	}

	printf("The decoded message of %s is:\n",fname2);
	nextChar = fgetc(fptr2); //retrieves first char from 1st file
  //loops until end of file is found
	while (nextChar != EOF){
    //checks if the character is a letter or a punctuation
    if(nextChar >= 65 && nextChar <= 90){
      //if a letter, then stores the letter-3 in decoded, however if the letter-3 would go past A then it is set manually
      switch(nextChar){
        case'A': decoded = 'X'; break;
        case'B': decoded = 'Y'; break;
        case'C': decoded = 'Z'; break;
        default: decoded = nextChar - 3;
      }
    }
    else{
      //else it is a puncutuation and is not changed
      decoded = nextChar;
    }

    printf("%c",decoded); //prints char to console
		nextChar = fgetc(fptr2); //retrieves next character from 1st file
	}
  
  printf("\n"); //newline for formatting

	fclose(fptr2); //closes output.txt
}