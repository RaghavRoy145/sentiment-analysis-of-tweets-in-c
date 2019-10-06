CC?=gcc

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lcurl -lssl -lcrypto
DEBUG = -g -Wall -Wextra

sentiment: $(obj)
	    $(CC) -o $@ $^ $(LDFLAGS)

.PHONY: debug

debug: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS) $(DEBUG)

.PHONY: clean

clean:
	rm -f ./*.o ./sentiment
