//
//  main.m
//  wwfmax
//
//  Created by Bion Oren on 10/1/12.
//  Copyright (c) 2012 Llama Software. All rights reserved.
//

#define BUILD_DATASTRUCTURES 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CWG-Creator.h"
#include "Justin-CWG-Search.h"
#include "DictionaryManager.h"
#include "assert.h"


int main(int argc, const char * argv[]) {
#if BUILD_DATASTRUCTURES
    {
        printf("You have entered %d arguments:\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        if (argc < 2) {
            printf("please provide the file name  of the input file ");
        }
        FILE* fp;
        int count = 0;
        char ch;

        fp = fopen(argv[1], "r");

        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '\n') {
                count++;
            }
        }

        fclose(fp);

        printf("The number of lines in the file is: %d\n", count);
        int numWords = count+1;
        FILE* wordFile = fopen(argv[1], "r");
        assert(wordFile);
        // int numWords = 172820;
        char* words = calloc(numWords * WORD_LENGTH, sizeof(char));
        assert(words);
        int* wordLengths = (int*)malloc(numWords * sizeof(int));
        assert(wordLengths);


        char buffer[40];
        int i = 0;
        char *word = words;
        while(fgets(buffer, 40, wordFile)) {
            int len = (int)strlen(buffer);
            if (buffer[len - 1] == '\n') {
                --len;
            }
            if (len <= WORD_LENGTH && len > 1) {
                strncpy(word, buffer, len);
                wordLengths[i++] = len;
                //assert(i < numWords);
                word += WORD_LENGTH * sizeof(char);
            }
        }
        numWords = i;

        printf("evaluating %d words\n", numWords);

        const WordInfo info = { .words = words, .numWords = numWords, .lengths = wordLengths };
        createDataStructure(&info);
        free(words);
        free(wordLengths);
    }
#endif
#ifdef DEBUG
    debug();
#endif
    
    DictionaryManager *mgr = createDictManager();

    char word[WORD_LENGTH];
    int length;
    while((length = nextWord(mgr, word))) {
        printf("%.*s\n", length, word);
    }
    resetManager(mgr);
    while((length = nextWord(mgr, word)));

    freeDictManager(mgr);
    destructDictManager();
    return 0;
}
