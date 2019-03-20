#include <stdio.h>
#include "get_tweets.h"
#include "parse_output.h"

int main()
{
    int get = 2;
    long timeout = 10L;
    int n = 0;
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
                printf("Enter maximum number of tweets to extract: ");
                scanf("%d", &n);
                extract_analyse_tweets(n);
                break;
            default:
                break;
        }
    } while (get != 0);
    
    return 0;
}