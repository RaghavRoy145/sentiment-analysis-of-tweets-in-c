#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char *replaceWord(const char *s, const char *oldW, 
                                 const char *newW) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
} 

void split_string(char *data_text, char *data, int n)
{
    char delim[] = "\"";
	char *req = strtok(data_text, delim);
    for(int i=0; i < n; ++i)
    {
	    req = strtok(NULL, delim); //req = strtok(NULL, delim);
    }
    strcpy(data, req);
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
    while(*lenptr != ' ')
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
    char *result = (char *) malloc(sizeof(char) * strlen(tweet)), *tmp;
    char stopwords[][32] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "you're", "you've", "you'll", "you'd", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it"};
    char punctuation[] = ".!,'@?()/~_-";
    strcpy(result, tweet);
    
    // to lowercase
    tmp = result;
    for(; *tmp; ++tmp) *tmp = tolower(*tmp);

    //remove link
    // tmp = strstr(result, "https:");
    // if(tmp != NULL) *tmp = '\0';
    deleteWord(result, "http");

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
    // result = replaceWord(tweet, )
    if(i>3) return words2;
    else return NULL;
}

int main()
{
    clock_t start = clock();
    FILE *file = fopen("training.1600000.processed.noemoticon.csv", "r");
    FILE *file2 = fopen("onlyTweets.txt", "w");
    size_t len;
    char *tmp = malloc(sizeof(char)*10000), *tmp2 = malloc(sizeof(char)*10000), *tweet = malloc(sizeof(char)*10000), *sentiment = malloc(sizeof(char)*100); 
    char *word = malloc(sizeof(char) * 64), **words;
    int count = 0, i = 0;
    getline(&tmp, &len, file);
    while(count < 100) // while((getline(&tmp, &len, file)) != -1) // while(count < 1000)
    {
        //printf("%s\n", tmp);
        getline(&tmp, &len, file);
        strcpy(tmp2, tmp);
        split_string(tmp, sentiment, 0);
        split_string(tmp2, tweet, 10);
        // strcpy(tweet, processTweet(tweet));
        // fprintf(file2, "%s\n", processTweet(tweet));
        i = 0;
        words = processTweet(tweet);
        if(words != NULL)
        {
            while((word = words[i]) != NULL)
            {
                printf("%s ", word);
                ++i;
            }
            printf("\n");
            // if(strcmp(sentiment, "0") == 0) printf("Negative --- %s\n", tweet);
            // else if(strcmp(sentiment, "4") == 0) printf("Positive --- %s\n", tweet);
            count++;
        }
    }
    fclose(file);
    fclose(file2);
    clock_t end = clock();
    printf("Time taken to execute: %.3lfms\n", ((double) (end - start) / CLOCKS_PER_SEC)*1000);
    return 0;
}