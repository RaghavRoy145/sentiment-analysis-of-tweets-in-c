#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyse_sentiment.h"

double sentiment_analyse(char **words, int n, char **sentiwords, double *sentiment)
{
    int size = 155287;
    // FILE *fptr = fopen("SentiWords_1.1.txt", "r");
    // char **sentiwords = (char**) malloc(size * sizeof(char*));
    // for(int i = 0; i < size; ++i) sentiwords[i] = malloc(64 * sizeof(char));
    // double sentiment[155287];

    // int i = 0;
    // size_t len = 100;
    // char *tmp = malloc(100);
    // while((getline(&tmp, &len, fptr)) != -1) // while(i < n && (getline(&tmp, &len, fptr)) != -1)
    // {
    //     strcpy(sentiwords[i], strtok(tmp, "\t"));
    //     // printf("%s ", sentiwords[i]);
    //     sscanf(strtok(NULL, "\n"), "%lf", &sentiment[i]);
    //     // printf("%lf\n", sentiment[i]);
    //     ++i;
    // }
    // fclose(fptr);
    // free(tmp);

    int i = 0;
    double total_sentiment = 0.0;
    while(i < n && strcmp(words[i], ""))
    {
        // printf("%s\n", words[i]);
        for(int j = 0; j < size; ++j)
        {
            if(strcmp(words[i], sentiwords[j]) == 0)
            {
                // printf("%s: %lf\n", words[i], sentiment[j]);
                total_sentiment += sentiment[j];
            }
        }
        ++i;
    }
    // for(int j = 0; j < size; ++j) free(sentiwords[j]);
    // free(sentiwords);
    return total_sentiment;
}