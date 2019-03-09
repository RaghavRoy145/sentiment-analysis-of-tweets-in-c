#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "mylibs.h"


void extract_required(char *tweet_text, char *tweet)
{
    char delim[] = "\"";
	char *req = strtok(tweet_text, delim);
	req = strtok(NULL, delim); req = strtok(NULL, delim);
    strcpy(tweet, req);
}

int main()
{
    FILE *fptr;
    size_t len;
    fptr = fopen("output.json", "r");
    char *tmp = malloc(sizeof(char) * 10000);
    int n = 10;
    printf("Enter maximum number of tweets to extract: ");
    scanf("%d", &n);
    char tweet_texts[n][100000], tweet_usernames[n][1000];
    char tweets[n][10000], usernames[n][100];
    char *text_start = NULL, *text_end = NULL;
    char *username_start = NULL, *username_end = NULL;
    int cont = 0, i = 0;
    while ((getline(&tmp, &len, fptr)) != -1)
    {
        //printf("%s\n", tmp);
        text_start = strstr(tmp, "\"text\"");
        text_end = strstr(tmp, ",\"source\""); //",\"source\"");
        username_start = strstr(tmp, "\"screen_name\":");
        username_end = strstr(tmp, ",\"location\"");

        if (strncmp("{\"created_at\":", tmp, 14) == 0 && strnstr(text_start, "\\u", text_end - text_start) == NULL && i < n)
        {
            //strcpy(tweet_texts[i], "");
            //printf("%p\n", strnstr(text_start, "\\u", text_end-text_start));
            strncpy(tweet_texts[i], text_start, text_end - text_start);
            //printf("%s\n", tweet_texts[i]);
            strncpy(tweet_usernames[i], username_start, username_end - username_start);
            i++;
            //printf("%s\nSelect another tweet?: ", tweet_text);
            //scanf("%d", &cont);
            //if(cont == 0) break;
        }
    }
    if (strcmp(tweet_texts[0], "") == 0)
    {
        printf("Could not find a tweet\n");
        return 0;
    }
    //printf("%s\n", tweet_text);
    //printf("%s\n", tweet_username);
    fclose(fptr);
    if (tmp)
        free(tmp);
    for(int j=0; j < i; ++j)
    {
        extract_required(tweet_texts[j], tweets[j]);
        printf("Tweet: %s\n", tweets[j]);
        extract_required(tweet_usernames[j], usernames[j]);
        printf("Username: @%s\n", usernames[j]);
    }
    printf("%d tweets found.\n", i);
    return 0;
}