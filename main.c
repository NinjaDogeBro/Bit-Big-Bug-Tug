/*-------------------------------------------
Program: Bit Big Bug Tug - Word Ladder Builder
Course: CS 211, Fall 2024, UIC
Author: Guillermo Ramirez III
Date: 10/8/2024
UIN:664042145

This C code allows users to build a word ladder, where each word in the sequence changes by 1 character
from the previous word.
The program checks user inputs, completion of the ladder, and provides a fun experiance to make sure
the final word matches with the user's goal.

------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int strCmpCnt(char* word1, char* word2) {
    // returns the count of character differences between two words 
    
    int wordLen1 = 0;
    int wordLen2 = 0;
    int wordLen = 0;
    
    //For loops to store number of  letters in word 1 and 2
    for(char* cpyWord1 = word1; *cpyWord1 != '\0'; cpyWord1++){
        wordLen1++;
    }
    
    for(char* cpyWord2 = word2; *cpyWord2 != '\0'; cpyWord2++){
        wordLen2++;
    }

    //If word 1 or 2 is bigger then we compare the difference of the words based on the bigger number of letters
    if(wordLen1 > wordLen2){
        wordLen = wordLen1 - wordLen2;
        for(int i = 0; i < wordLen2; i++){
            if(*word1 != *word2){
                wordLen++;
            }
            word1++;
            word2++;
        }
    }
    else if(wordLen1 < wordLen2){
        wordLen = wordLen2 - wordLen1;
        for(int i = 0; i < wordLen1; i++){
            if(*word1 != *word2){
                wordLen++;
            }
            word1++;
            word2++;
        }
    }
    else if(wordLen1 == wordLen2){
        for(int i = 0; i < wordLen1; i++){
                if(*word1 != *word2){
                    wordLen++;
                }
                word1++;
                word2++;
            }
    }
    
    return wordLen; 
}


int strCmpInd(char* word1, char* word2) {
    // Returns the index of the character where two strings first 
    // differ, & returns -1 if there are no differences
    

    int wordLen1 = 0;
    int wordLen2 = 0;
    int index = -1;
    int countIndex = 0;
    
    //For loops to store number of  letters in word 1 and 2
    for(char* cpyWord1 = word1; *cpyWord1 != '\0'; cpyWord1++){
        wordLen1++;
    }
    
    for(char* cpyWord2 = word2; *cpyWord2 != '\0'; cpyWord2++){
        wordLen2++;
    }

    //If word 1 or 2 is bigger then we compare the difference of the words based on the bigger number of letters
    if(wordLen1 > wordLen2){
        for(int i = 0; i < wordLen1; i++){
            if(*word1 != *word2){
                index = countIndex;
                break;
            }
            word1++;
            word2++;
            countIndex++;
        }
    }
    else if(wordLen1 < wordLen2){
        for(int i = 0; i < wordLen2; i++){
            if(*word1 != *word2){
                index = countIndex;
                break;
            }
            word1++;
            word2++;
            countIndex++;
        }
    }
    else if(wordLen1 == wordLen2){
        for(int i = 0; i < wordLen1; i++){
                if(*word1 != *word2){
                    index = countIndex;
                    break;
                }
                word1++;
                word2++;
                countIndex++;
            }
    }

    //if there were no changes, index will be left with -1, otherwise it will include the numder index that was changed
    return index;
}


void appendWord(char*** pWords, int* pNumWords, int* pMaxWords, char* newWord) {
    // Adds a new word to a dynamic heap-allocated array of C-strings

    //      if adding a new word pushes *pNumWords greater than *pMaxWords, 
    //      then realloate the *pWords array with double the capacity.
    if(*pNumWords >= *pMaxWords){
        *pMaxWords = *pNumWords * 2;
        char **ptr = (char**)malloc((*pMaxWords) * sizeof(char*));

        for(int i = 0; i < *pNumWords; i++){
            ptr[i] = (*pWords)[i];
        }

        free(*pWords);
        *pWords = ptr;
    }
    //heap-space must be allocated for the new word inside this function
    (*pWords)[*pNumWords] = (char*)malloc((strlen(newWord) + 1) * sizeof(char));
    
    //then copy the chars from [newWord] to the newly allocated heap-space
    strcpy((*pWords)[*pNumWords], newWord);
    (*pNumWords)++;
}


int linSearchForWord(char** words, int numWords, char* findWord) { 
    // returns the index in the [words] C-string array where a match to the 
    // C-string [findWord] is found, using a linear search; 
    // return -99 if [findWord] is NOT found in [words] array

    int index = 0;

    for(int i = 0; i < numWords; i++){
        if(strcmp(words[i], findWord) == 0){
            return index;
        }
        index++;
    }
    return -99; 
}


bool checkForValidWord(char** words, int numWords, int wordLen, char** ladder, int ladderHeight, char* aWord) {
    //checks if [aWord] is valid for the next word in the word ladder
    
    // - Returns true if [aWord] is "DONE" beacuse the user wants to stop;
    if(strcmp(aWord, "DONE") == 0){
        printf("Stopping with an incomplete word ladder...\n");
        return true;
    }

    // - Returns false if [aWord] is invalid because it has the wrong word length
    if(strlen(aWord) != wordLen){
        printf("Entered word does NOT have the correct length. Try again...");
        return false;
    }

    // - Returns false if [aWord] is invalid because it is not in the words array
    int wordIndex = linSearchForWord(words, numWords, aWord);
    if(wordIndex == -99){
        printf("Entered word NOT in dictionary. Try again...");
        return false;
    }

    // - Returns false if [aWord] is invalid because it is NOT a single-char 
    // difference from the previous word in the ladder; 
    
    if(strCmpCnt(ladder[ladderHeight - 1], aWord) != 1){
        printf("Entered word is NOT a one-character change from the previous word. Try again...");
        return false;
    }

    // - Returns true if [aWord] is valid and will be added to the word ladder
    printf("Entered word is valid and will be added to the word ladder.\n");

    return true; // modify this
}


bool isLadderComplete(char** ladderWords, int height, char* finalWord) {
    // Returns true if the final word in [ladderWords] is a match to 
    // [finalWord]; otherwise, return false; the number of words in
    // the word ladder is [height]

    if(strcmp(ladderWords[height-1], finalWord) == 0){
        return true;
    }

    return false;
}


void displayIncompleteLadder(char** ladderWords, int height) {

    // To signify the ladder as incomplete, display three lines of  
    // "..." at the top of the ladder. The ladder must be displayed 
    // with an indentation of two whitespaces on every line;
    printf("  ...\n");
    printf("  ...\n");
    printf("  ...\n");

    //Displays the C-strings in the [ladderWords] 
    // array with the first word at the bottom of the ladder, and 
    // each successive C-string one rung higher on the ladder.     
    for(int i = height - 1; i >= 0; i--){
        if(strlen(ladderWords[i]) > 0 ){
            printf("  %s\n", ladderWords[i]);
        }
    }

}


void displayCompleteLadder(char** ladderWords, int height) {
    // Displays the C-strings in the [ladderWords] array 
    // with the first word at the bottom of the ladder, and each 
    // successive C-string one rung higher on the ladder. 

    char** cpyLadderWords = ladderWords;
    int startIndex = 0;
    int strLength = strlen(cpyLadderWords[0]);

    for(int i = height - 1; i > 0; i--){
        int changeIndex = strCmpInd(cpyLadderWords[i], cpyLadderWords[i - 1]);
            // In between each ladder rung, display the symbol '^' to 
            // signify the character that changes between the two rungs of 
            // the ladder. The ladder should be displayed with an indentation 
            // of two whitespaces to the left of every word;
            printf("  %s\n", cpyLadderWords[i]);
            for(int i = 0; i < changeIndex + 2; i++){
                printf(" ");
            }
            printf("^");
            for(int i = 0; i < strLength - changeIndex - 1; i++){
                printf(" ");
            }
            printf("\n");
        
    }

    printf("  %s\n", cpyLadderWords[0]);
}


int main(int argc, char* argv[]) {

    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";     
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid"; 

    
    for(int i = 1; i < argc; i++){
        //  [-n wordLen] = sets word length for word ladder
        if(strcmp(argv[i], "-n") == 0){
            wordLen = atoi(argv[i+1]);
        }

        // [-m maxLadder] = sets maximum word ladder height
        if(strcmp(argv[i], "-m") == 0){
            maxLadder = atoi(argv[i+1]);
        }

        // [-d dictFile] = sets dictionary file
        if(strcmp(argv[i], "-d") == 0){
            strcpy(dict, argv[i+1]);
        }
        
        // [-s startWord] = sets the starting word
        if(strcmp(argv[i], "-s") == 0){
            strcpy(startWord, argv[i+1]);
        }

        // [-f finalWord] = sets the final word
        if(strcmp(argv[i], "-f") == 0){
            strcpy(finalWord, argv[i+1]);
        }
    }

    printf("Interactively (re)setting invalid parameters:\n");

    // set word length using interactive user-input if necessary
    int numInputs = 1;
    while (numInputs > 0 && (wordLen < 2 || wordLen > 20)) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        numInputs = scanf("%d",&wordLen);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    // set max ladder height using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        numInputs = scanf("%d",&maxLadder);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    numInputs = 1;
    while (numInputs > 0 && fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: ");
        numInputs = scanf("%s", dict);
        printf("\n");
        fileTry = fopen(dict,"r");
    }
    fclose(fileTry);
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }
    
    // build the [words] array, a heap-allocated array of C-strings
    // where the words are a read-in from the dictionary file
    // and only those words of the desired length [wordLen] 

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4

    char** words = (char**)malloc(maxWords*sizeof(char*));
    //file-read the word list from the dictionary file 
    // [dict], storing only words of length set by 
    // [wordLen] in [words], which is a dynamically 
    // growing heap-allocated array of C-strings

    FILE *file = fopen(dict, "r");
    char buffer[100];
    while(fscanf(file, "%s", buffer) == 1){
        if(strlen(buffer) == wordLen){
            appendWord(&words, &numWords, &maxWords, buffer);
        }
    }

    fclose(file);

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords);
    printf("\n");

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    // resetting start word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,startWord) < 0) {
        printf("Start word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        numInputs = scanf("%s", startWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // resetting final word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,finalWord) < 0 ) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        numInputs = scanf("%s", finalWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  
    
    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; // initially, the ladder is empty
    
    // add the start word to the ladder, i.e. the "bottom rung"
    appendWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");

    //The while loop conditions are running but it'll stop if...
    // 1. the ladder still has at least one available rung
    // before reaching the maximum allowed height
    // 2. the user is NOT attempting to stop the word ladder
    // building process, which occurs if the entered word 
    // [aWord] from the last iteration is "DONE"
    // 3. the ladder is still incomplete; i.e. the last word
    // added to ladder is not the final word; 
    while ((ladderHeight != maxLadder) && (strcmp(aWord,"DONE") != 0) && (!isLadderComplete(ladder, ladderHeight, finalWord))) {   // modify this line 
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        // Make sure the entered word is valid for the next ladder rung;
        // if not, repeatedly allow user to enter another word until one is valid
        while (!checkForValidWord(words, numWords, wordLen, ladder, ladderHeight, aWord)) {
            printf("\nEnter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }


        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {
            appendWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");
    }
    

    // Check if the built word ladder is complete and 
    // display the word ladder appropriately. 
    if (isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }
    
    
    // free all heap-allocated memory to avoid potential memory leaks. 
    for(int i = 0; i < ladderHeight; i++){
        free(ladder[i]);
    }
    free(ladder);

    for(int i = 0; i < numWords; i++){
        free(words[i]);
    }
    free(words);

    return 0;
}