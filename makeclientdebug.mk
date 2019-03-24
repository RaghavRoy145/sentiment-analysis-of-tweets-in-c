client.out: client.o mylibs.o get_tweets.o parse_output.o analyse_sentiment.o
	gcc client.o mylibs.o get_tweets.o parse_output.o analyse_sentiment.o -lcurl -lssl -lcrypto -o client.out -g -Wall -Wextra 
mylibs.o: mylibs.c mylibs.h
	gcc -c mylibs.c -g -Wall -Wextra 
get_tweets.o: get_tweets.c get_tweets.h
	gcc -c get_tweets.c -g -Wall -Wextra 
parse_output.o: parse_output.c parse_output.h
	gcc -c parse_output.c -g -Wall -Wextra 
analyse_sentiment.o: analyse_sentiment.c analyse_sentiment.h
	gcc -c analyse_sentiment.c -g -Wall -Wextra 