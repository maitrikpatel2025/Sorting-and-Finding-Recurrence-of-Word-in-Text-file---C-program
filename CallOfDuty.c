#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*To avoid the compiler warnings*/
#define _CRT_SECURE_NO_WARNINGS

/*Initialize the maximum numbers of words to 1000*/
#define MAX_WORDS 1000

/*Initializedthe file name by path directory*/
#define FILENAME "C:\Users\maitr\Desktop\PRG 255 project\data.txt"

int main (void) {
	/*Defined an input: data.txt and output: CallOfDuty.txt files*/
	FILE *input, *output;
	
	char ch, swap[1000];
	char str1[MAX_WORDS][100], str2[100];
	int i, j, temp = 0;
	int line = 0, word = 1, charctr = 1;
	int distinct = 0, len, index, isUnique, count[MAX_WORDS];
	
	/*Open the input file with an article inside for reading attribute*/
	input = fopen(FILENAME, "r");
	
	/*Check for the error, if the file exist or not*/
	if (input == NULL) {
		printf("\n\n\tFile unable to Open !");
		printf("\n\tPlease check the file directory !");
		return (-1);
	}
	
	/*Create the output empty file for writing attribute*/
	output = fopen("C:\Users\maitr\Desktop\PRG 255 project\CallOfDuty.txt", "w");
	
	/*Checkfor the error, if the file exist or not*/
	if (output == NULL) {
		printf("\n\n\tFile unable to Open !");
		printf("\n\tPlease check the file directory !");
		return (-1);
	}
	
	/*Taking input single character at a time*/
	ch = fgetc(input);
	printf("\n\n\tContent of the file: \n\n");
	
	while (ch != EOF) {
		/*Displays content on screen by character at a time*/
		printf("%c", ch);
		
		/*Counts for the number of lines*/
		if (ch == '\n') {
			line++;
		}
		/*Counts for the number of words*/
		if (ch == ' ' || ch == '\n') {
			word++;
		}
		/*Counts for the number of characters*/
		else {
			charctr++;
		}
		
		/*Inputs into the output file (writes into file)
		Single character at a time*/
		fputc(ch, output);
		
		/*Reading the character from input file*/
		ch = fgetc(input);
	}
	
	/*Close both input and output files*/
	fclose(input);
	fclose(output);
	
	/*Open the input file again to read the file*/
	input = fopen(FILENAME, "r");
	
	/*Initialize word count to 0*/
	for (i=0; i<MAX_WORDS; i++) {
		count[i] = 0;
	}

    index = 0;
    
    while (fscanf(input, "%s", str2) != EOF) {
        /*Convert word to lowercase*/
        strlwr(str2);

        /*Remove last punctuation character*/
        len = strlen(str2);
        if (ispunct(str2[len - 1])) {
            str2[len - 1] = '\0';
		}

        /*Check if word exits in list of all different words*/
        isUnique = 1;
        for (i=0; i<index && isUnique; i++) {
            if (strcmp(str1[i], str2) == 0) {
                isUnique = 0;
			}
        }

        /*If word is unique then add it to different words list
        and increment index. Otherwise increment occurrence 
        count of current word.*/
        if (isUnique) {
            strcpy(str1[index], str2);
            count[index]++;
            distinct++;
            index++;
        } else {
            count[i - 1]++;
        }
    }
    
    /*Close the input file*/
    fclose(input);
	
	/*Sort the different words array into descending
	order based on the number of counts for each word*/
	for(i = 0; i < distinct; i++) {
		for (j = (i + 1); j < distinct; j++) {
			if (count[i] < count[j]) {
				/*Swaping number of counts*/
				temp = count[i];
				count[i] = count[j];
				count[j] = temp;
				
				/*Swaping words*/
				strcpy(swap, str1[i]);
				strcpy(str1[i], str1[j]);
				strcpy(str1[j], swap);
			}
		}
	}
	
	/*Display line, word, character  counts
	Display number of different words
	Display top 10 most used words*/
	printf("\n\n\tNumber of lines: %d", line);
	printf("\n\n\tNumber of words: %d", (word - 2));
	printf("\n\n\tNumber of character: %d", (charctr - 1));
	printf("\n\n\tNumber of different words: %d", distinct);
	printf("\n\n\t10 Most Occured words:\n");
	for (i = 0; i < 10; i++) {
		printf("\n\t%-15s => %d", str1[i], count[i]);
	}

	printf("\n\n");
	system("pause");
	return (0);
}
