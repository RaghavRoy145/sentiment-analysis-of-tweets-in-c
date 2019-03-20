client.out: client.o mylibs.o get_tweets.o parse_output.o analyse_sentiment.o
	gcc client.o mylibs.o get_tweets.o parse_output.o analyse_sentiment.o -lcurl -lssl -lcrypto -o client.out
mylibs.o: mylibs.c mylibs.h
	gcc -c mylibs.c
get_tweets.o: get_tweets.c get_tweets.h
	gcc -c get_tweets.c
parse_output.o: parse_output.c parse_output.h
	gcc -c parse_output.c
analyse_sentiment.o: analyse_sentiment.c analyse_sentiment.h
	gcc -c analyse_sentiment.c