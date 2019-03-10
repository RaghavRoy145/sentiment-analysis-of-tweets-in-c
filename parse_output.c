#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "mylibs.h"
void extract_required(char *tweet_text, char *tweet);
void deleteChars(char *s, char c);
int deleteWord(char *s, char *word);
char **processTweet(char *tweet);

int main()
{
    // Open output.json file to read
    FILE *fptr;
    size_t len = 10000;
    fptr = fopen("output.json", "r");
    char *tmp = malloc(sizeof(char) * 10000);
    // Get maximum number of tweets to extract from user
    int n;
    printf("Enter maximum number of tweets to extract: ");
    scanf("%d", &n);
    char tweet_texts[n][100000], tweet_usernames[n][1000];
    char tweets[n][10000], usernames[n][100];
    char *text_start = NULL, *text_end = NULL;
    char *username_start = NULL, *username_end = NULL;
    int i = 0;

    // Read output file line by line
    while (i < n && (getline(&tmp, &len, fptr)) != -1)
    {
        // Extract only tweet and username
        text_start = strstr(tmp, "\"text\"");
        text_end = strstr(tmp, ",\"source\"");
        username_start = strstr(tmp, "\"screen_name\":");
        username_end = strstr(tmp, ",\"location\"");

        if (strncmp("{\"created_at\":", tmp, 14) == 0 && strnstr(text_start, "\\u", text_end - text_start) == NULL && i < n)
        {
            strncpy(tweet_texts[i], text_start, text_end - text_start);
            //printf("%s\n", tweet_texts[i]);
            strncpy(tweet_usernames[i], username_start, username_end - username_start);
            i++;
        }
    }
    fclose(fptr);
    if(tmp) free(tmp);

    // print if no tweet is extracted
    if (strcmp(tweet_texts[0], "") == 0)
    {
        printf("Could not find a tweet\n");
        return 0;
    }

    //printf("%s\n", tweet_text);
    //printf("%s\n", tweet_username);
    char **words, *word;
    int k = 0;
    int count = 0;
    // Extract only tweet and process it
    for(int j=0; j < i; ++j)
    {
        extract_required(tweet_texts[j], tweets[j]);
        // printf("Tweet: %s\n", tweets[j]);
        words = processTweet(tweets[j]);
        if(words == NULL || words[0] == NULL) continue;
        else if(words != NULL)
        {
            printf("Tweet: ");
            k = 0;
            while((word = words[k]) != NULL)
            {
                // if(strcmp(word, "") == 0) continue;
                printf("%s ", word);
                ++k;
            }
            printf("\n");
            ++count;
            free(words);
        }
        // printf("Tweet: %s\n", tweets[j]);
        extract_required(tweet_usernames[j], usernames[j]);
        printf("Username: @%s\n", usernames[j]);
    }
    printf("%d tweets found.\n", count);
    return 0;
}


void extract_required(char *tweet_text, char *tweet)
{
    char delim[] = "\"";
	char *req = strtok(tweet_text, delim);
	req = strtok(NULL, delim); req = strtok(NULL, delim);
    strcpy(tweet, req);
}


void deleteChars(char *s, char c)
{
    int writer = 0, reader = 0;

    while (s[reader])
    {
        if (s[reader]!=c)
        {   
            s[writer++] = s[reader];
        }

        reader++;
    }

    s[writer]=0;
}

int deleteWord(char *s, char *word)
{
    char *substr = strstr(s, word);
    if(substr == NULL) return -1;
    char *lenptr = substr;
    int len = 0, i = 0;
    while(*lenptr && *lenptr != ' ')
    {
        lenptr++;
        len++;
    }
    while(*(substr+len+1+i))
    {
        *(s+i) = *(substr+len+1+i);
        ++i;
    }
    *(s+i) = '\0';
    return 0;
}

char **processTweet(char *tweet)
{
    if(strlen(tweet) < 5) return NULL;
    char *result = (char *) malloc(sizeof(char) * strlen(tweet)), *tmp;
    char stopwords[][32] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "you're", "you've", "you'll", "you'd", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it"};
    char punctuation[] = ".!,'?()/~_-\\:[]{}";
    strcpy(result, tweet);
    
    // to lowercase
    tmp = result;
    for(; *tmp; ++tmp) *tmp = tolower(*tmp);

    //remove link
    // tmp = strstr(result, "https:");
    // if(tmp != NULL) *tmp = '\0';
    deleteWord(result, "http");
    deleteWord(result, "rt");
    deleteWord(result, "@");

    //remove punctuatuon symbols
    for(int i = 0; i < strlen(punctuation); ++i)
    {
        deleteChars(result, punctuation[i]);
    }
    // separate words into a array of strings
    char **words = (char **) malloc(sizeof(char) * strlen(tweet) * 2);
    char *p;
    int i = 0;
    words[i] = (char *) malloc(64);
    p = strtok(result, " ");
    while(p != NULL)
    {
        words[i] = (char *) malloc(64);
        strcpy(words[i], p);
        i++;
        p = strtok(NULL, " ");
        // printf("%s\n", words[i-1]);
    }
    words[i] = NULL;
    // words[i+1] = NULL;
    // remove stopwords
    // i = 0;
    int a = 0;
    int k = 0;
    char **words2 = (char **) malloc(sizeof(char) * strlen(tweet) * 2);
    while(a < i)
    {
        for(int j = 0; j < 26; ++j)
        {
            if(strcmp(words[a], stopwords[j]) != 0)
            {
                words2[k] = (char *) malloc(strlen(words[a])+1);
                if(k==0)
                {
                    strcpy(words2[k], words[a]);
                    ++k;
                }
                else if(strcmp(words[a], words2[k-1]) != 0)
                {
                    strcpy(words2[k], words[a]);
                    ++k;
                }
            }
        }
        ++a;
    }
    words2[i] = NULL;
    free(words);
    free(result);
    if(i>3) return words2;
    else return NULL;
    // return words2;
}
// end 
