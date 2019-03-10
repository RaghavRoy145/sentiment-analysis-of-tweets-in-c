# Sentiment Analysis of Tweets in C

This C program gets tweets, processes the output and, in the future, performs basic sentiment analysis on it.

## Compiling

Run make to compile and generate .out files.

```bash
make -f makefile.mk
```
## Usage

* Save your Twitter API keys in file names `keys` in this format:
    ```bash
    Consumer Key
    Consumer Secret
    Access Token
    Access Token Secret
    ```

* Run `./get_tweets.out` to get Tweets from the Twitter API and save the json output to `output.json`
* Run `./parse_output.out` and enter the maximun number of tweets required. This will parse the `output.json` file and extract some number of tweets from it.