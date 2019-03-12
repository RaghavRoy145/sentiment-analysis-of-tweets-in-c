parse_output.out: parse_output.o analyse_sentiment.o
	gcc parse_output.o analyse_sentiment.o -o parse_output.out -g
parse_output.o: parse_output.c analyse_sentiment.h
	gcc -c parse_output.c -g
analyse_sentiment.o: analyse_sentiment.c analyse_sentiment.h
	gcc -c analyse_sentiment.c -g