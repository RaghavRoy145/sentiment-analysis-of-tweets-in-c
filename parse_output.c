#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "mylibs.h"
#include "analyse_sentiment.h"
#include "get_tweets.h"
#define wordlength 128
#define linelength 10000

void extract_required(char *tweet_text, char *tweet);
void deleteChars(char *s, char c);
int deleteWord(char *str, char *rem);
char **processTweet(char *tweet, int *n);
int deleteWordn(char *s, char *word, int len);

int extract_analyse_tweets(int n)
{
    time_t start = clock();
    // Open output.json file to read
    FILE *fptr;
    size_t len = linelength;
    fptr = fopen("output.json", "r");
    char *tmp = malloc(sizeof(char) * linelength);
    // Get maximum number of tweets to extract from user
    // int n;
    // printf("Enter maximum number of tweets to extract: ");
    // scanf("%d", &n);
    char tweet_texts[n][100000], tweet_usernames[n][1000];
    char tweets[n][linelength], usernames[n][100];
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

    int size = 155287;
    FILE *sentiwordsfile = fopen("SentiWords_Sorted.txt", "r");
    char **sentiwords = malloc(size * sizeof(char*));
    for(int i = 0; i < size; ++i) sentiwords[i] = malloc(wordlength * sizeof(char));
    double sentiment[155287];
    int l = 0;
    len = 100;
    char *tmp2 = malloc(100);
    while((getline(&tmp2, &len, sentiwordsfile)) != -1) // while(i < n && (getline(&tmp, &len, sentiwordsfile)) != -1)
    {
        strcpy(sentiwords[l], strtok(tmp2, "\t"));
        sscanf(strtok(NULL, "\n"), "%lf", &sentiment[l]);
        ++l;
    }
    fclose(sentiwordsfile);
    if(tmp2) free(tmp2);

    //printf("%s\n", tweet_text);
    //printf("%s\n", tweet_username);
    char **words, *word;
    int k = 0, n2 = 0;
    int count = 0;
    double senti = 0;
    // Extract only tweet and process it
    for(int j=0; j < i; ++j)
    {
        extract_required(tweet_texts[j], tweets[j]);
        extract_required(tweet_usernames[j], usernames[j]);
        // printf("Tweet: %s\n", tweets[j]);
        words = processTweet(tweets[j], &n2);
        if(words == NULL || words[0] == NULL) continue;
        else if(words != NULL)
        {
            k = 0;
            while((word = words[k]) != NULL)
            {
                ++k;
            }
            senti = sentiment_analyse(words, k, sentiwords, sentiment);
            if(senti != 0.0)
            {
                printf("Username: @%s\n", usernames[j]);
                printf("Tweet: ");
                while((word = words[k]) != NULL)
                    printf("%s ", word);
                printf("\n");
                printf("Sentiment: %lf\n\n", senti);
                ++count;
            }
            for(int j = 0; j <= n2; ++j){ if(words[j]) free(words[j]); }
            if(words) free(words);
        }
        // printf("Tweet: %s\n", tweets[j]);
        // extract_required(tweet_usernames[j], usernames[j]);
        // printf("Username: @%s\n\n", usernames[j]);
    }
    printf("%d tweets found.\n", count);
    for(int j = 0; j < size; ++j){ if(sentiwords[j]) free(sentiwords[j]); }
    if(sentiwords) free(sentiwords);
    time_t end = clock();
    double totaltime = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %lfs\n", totaltime);
    // int ex = 0;
    // while(ex != 1)
    //     scanf("%d", &ex);
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

// int deleteWord(char *s, char *word)
// {
//     char *substr = strstr(s, word);
//     if(substr == NULL) return -1;
//     char *lenptr = substr;
//     int len = 0, i = 0;
//     while(*lenptr && *lenptr != ' ')
//     {
//         lenptr++;
//         len++;
//     }
//     while(*(substr+len+1+i))
//     {
//         *(substr+i) = *(substr+len+1+i);
//         ++i;
//     }
//     *(s+i) = '\0';
//     return 0;
// }

// int deleteWordn(char *s, char *word, int len)
// {
//     char *substr = strstr(s, word);
//     if(substr == NULL) return -1;
//     int i = 0;
//     // while(*lenptr && *lenptr != ' ')
//     // {
//     //     lenptr++;
//     //     len++;
//     // }
//     while(*(substr+len+1+i))
//     {
//         *(substr+i) = *(substr+len+1+i);
//         ++i;
//     }
//     *(substr+i) = '\0';
//     return 0;
// }

int deleteWord(char *str, char *rem)
{
    char *tmp2 = malloc(strlen(str) + 2);
    strcpy(tmp2, str);
    char *substr = strstr(tmp2, rem);
    if(substr == NULL)
    {
        if(tmp2) free(tmp2);
        return -1;
    }
    char *toRemove = strtok(substr, " ");
    if(toRemove == NULL) toRemove = strtok(substr, "\0");
    int i, j, stringLen, toRemoveLen;
    int found;
    if(tmp2) free(tmp2);

    stringLen   = strlen(str);      // Length of string
    toRemoveLen = strlen(toRemove); // Length of word to remove

    for(i=0; i <= stringLen - toRemoveLen; i++)
    {
        /* Match word with string */
        found = 1;
        for(j=0; j<toRemoveLen; j++)
        {
            if(str[i + j] != toRemove[j])
            {
                found = 0;
                break;
            }
        }
        if(found == 1)
        {
            for(j=i; j<=stringLen - toRemoveLen; j++)
            {
                str[j] = str[j + toRemoveLen];
            }
            stringLen = stringLen - toRemoveLen;
            i--;
        }
    }
    return 0;
}

int delete_word(char str[], char word[])
{
    int i, l;
    char *ptr = strstr(str, word);
    int index = 0;
    if(ptr != NULL) 
        index = str - strstr(str, word);
    else
        return -1;
    // for (l = 0; word[l] != '\0'; l++);
    l = strlen(word);

    for (i = index; str[i] != '\0'; i++)
    {
        str[i] = str[i + l + 1];
    }
    return 0;
}

char **processTweet(char *tweet, int *n)
{
    if(strlen(tweet) < 5) return NULL;
    // printf("Tweeeeeeeet: %s\n", tweet);
    char *result = malloc(sizeof(char) * strlen(tweet)), *tmp;
    // char stopwords[][32] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "you're", "you've", "you'll", "you'd", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it"};
    // char stopwords[][32] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
    char punctuation[] = ".!,'?()/~_-:[]{}#";
    strcpy(result, tweet);
    
    // to lowercase
    tmp = result;
    for(; *tmp; ++tmp) *tmp = tolower(*tmp);

    //remove link
    // tmp = strstr(result, "https:");
    // if(tmp != NULL) *tmp = '\0';
    // deleteWord(result, "http");
    // deleteWord(result, "rt");
    //// deleteWord(result, "@");
    // deleteWord(result, "$");
    // deleteWordn(result, "\\n", 2);
    delete_word(result, "\n");

    //remove punctuatuon symbols
    for(int i = 0; i < strlen(punctuation); ++i)
    {
        deleteChars(result, punctuation[i]);
    }
    // separate words into a array of strings
    char **words = malloc(sizeof(char) * strlen(tweet) * 2);
    char *p;
    int i = 0;
    words[i] = malloc(wordlength);
    p = strtok(result, " ");
    while(p != NULL)
    {
        words[i] = malloc(wordlength);
        strcpy(words[i], p);
        i++;
        p = strtok(NULL, " ");
        // printf("%s\n", words[i-1]);
    }
    words[i] = NULL;
    // words[i+1] = NULL;
    // remove stopwords
    // i = 0;

    // int a = 0;
    // int k = 0;
    // char **words2 = (char **) malloc(sizeof(char) * strlen(tweet) * 2);
    // while(a < i)
    // {
    //     for(int j = 0; j < 26; ++j)
    //     {
    //         if(strcmp(words[a], stopwords[j]) != 0)
    //         {
    //             words2[k] = (char *) malloc(strlen(words[a])+1);
    //             if(k==0)
    //             {
    //                 strcpy(words2[k], words[a]);
    //                 ++k;
    //             }
    //             else if(strcmp(words[a], words2[k-1]) != 0)
    //             {
    //                 strcpy(words2[k], words[a]);
    //                 ++k;
    //             }
    //         }
    //     }
    //     ++a;
    // }
    // words2[i] = NULL;
    // free(words);
    *n = i;
    if(result) free(result);
    if(i>3) return words;
    else
    {
        for(int j = 0; j < i; ++j) if(words[j]) free(words[j]);
        if(words) free(words);
        return NULL;
    }
    // return words2;
}