get_tweets.out: mylibs.o get_tweets.o parse_output.out
	gcc mylibs.o get_tweets.o -lcurl -lssl -lcrypto -o get_tweets.out
mylibs.o: mylibs.c mylibs.h
	gcc -c mylibs.c
get_tweets.o: get_tweets.c mylibs.h
	gcc -c get_tweets.c
parse_output.out: parse_output.c
	gcc parse_output.c -o parse_output.out