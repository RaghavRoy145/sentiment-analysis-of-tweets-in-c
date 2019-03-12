# Sentiment Analysis of Tweets in C

This C program gets tweets, processes the output and, in the future, performs basic sentiment analysis on it.

## Compiling

Run make to compile and generate .out files.

```bash
make -f makefile.mk
make -f makefile2.mk
```
## Usage

* Save your Twitter API keys in file named `keys` in this format:
    ```bash
    Consumer Key
    Consumer Secret
    Access Token
    Access Token Secret
    ```
* Download `SentiWords_1.1.txt` from [here](https://hlt-nlp.fbk.eu/technologies/sentiwords) and save it to the same directory.
* Run `./get_tweets.out` to get Tweets from the Twitter API and save the output to `output.json`.
* Run `./parse_output.out` and enter the maximum number of tweets required. This will parse the `output.json` file and will try to extract some tweets from it. It will then try to calculate the sentiment of tweet by looking at it word by word. It then displayed the tweets along with username and sentiment.