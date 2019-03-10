get_tweets.out: mylibs.o get_tweets.o parse_output.out
	gcc mylibs.o get_tweets.o -lcurl -lssl -lcrypto -o get_tweets.out -g
mylibs.o: mylibs.c mylibs.h
	gcc -c mylibs.c -g
get_tweets.o: get_tweets.c mylibs.h
	gcc -c get_tweets.c -g
parse_output.out: parse_output.c
	gcc parse_output.c -o parse_output.out -g