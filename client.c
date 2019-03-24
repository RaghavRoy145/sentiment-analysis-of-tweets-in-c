#include <stdio.h>
#include "get_tweets.h"
#include "parse_output.h"

int main()
{
    int get;
    long timeout = 10L;
    int n = 0;
    int readmore = 0;
    FILE *fp = fopen("output.json", "r");
    if(fp == NULL) return -1;
    do
    {
        printf("Select option:\n");
        printf("1. Get Tweets from Twitter API.\n");
        printf("2. Extract tweets and analyse sentiment.\n");
        printf("0. Exit\n");
        scanf("%d", &get);
        switch (get)
        {
            case 1:
                printf("Please wait %ld seconds\n", timeout);
                tweets_get(timeout);
                break;
            case 2:
                printf("Enter number of lines to parse: ");
                scanf("%d", &n);
                // n = 2;
                extract_analyse_tweets(n, fp);
                // do
                // {
                //     printf("Do you want to continue? (0 for no, 1 for yes): ");
                //     scanf("%d", &readmore);
                //     if(readmore) extract_analyse_tweets(n, fp);
                // } while (readmore != 0);
                fclose(fp);
                break;
            default:
                break;
        }
    } while (get != 0);
    
    return 0;
}