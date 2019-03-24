#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyse_sentiment.h"
#define datasize 155287

int binary_search(char **sentiwords, char *word)
{
    int low = 0, high = datasize, mid, res;
    while(low <= high)
    {
        mid = (low+high)/2;
        res = strcmp(word, sentiwords[mid]);
        if(res == 0) return mid;
        else if(res > 0)
        {
            low = mid + 1;
        }
        else if(res < 0)
        {
            high = mid - 1;
        }
    }
    return -1;
}

double sentiment_analyse(char words[20][wordlength], int n, char **sentiwords, double *sentiment)
{
    // int datasize = 155287;
    // FILE *fptr = fopen("SentiWords_1.1.txt", "r");
    // char **sentiwords = (char**) malloc(datasize * datasizeof(char*));
    // for(int i = 0; i < datasize; ++i) sentiwords[i] = malloc(64 * datasizeof(char));
    // double sentiment[155287];

    // int i = 0;
    // datasize_t len = 100;
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
    int bin;
    double total_sentiment = 0.0;
    while(i < n)// && strcmp(words[i], "") != 0) //&& words[i] != NULL && strlen(words[i]) > 3)
    {
        // printf("%s\n", words[i]);
        // 
        // linear search
        // for(int j = 0; j < datasize; ++j)
        // {
        //     if(strcmp(words[i], sentiwords[j]) == 0)
        //     {
        //         // printf("%s: %lf\n", words[i], sentiment[j]);
        //         total_sentiment += sentiment[j];
        //     }
        // }
        // 
        // Binary search
        bin = binary_search(sentiwords, words[i]);
        if(bin != -1)
        {
            // printf("Word:%s Binary search:%d Sentiment:%lf\n", words[i], bin, sentiment[bin]);
            total_sentiment += sentiment[bin];
        }
        // 
        ++i;
    }
    // for(int j = 0; j < datasize; ++j) free(sentiwords[j]);
    // free(sentiwords);
    return total_sentiment;
}