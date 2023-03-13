COMPILER= gcc
OPTIONS = -g
COMPILE = $(COMPILER) $(OPTIONS) 
BUILD = build
PROGRAM = data_av.c
data_av:  data_av.c
	$(COMPILER) data_av.c $(LDFLAGS) -pthread -g -o data_av

run: data_av
	./data_av

clean: 
	rm -f data_av
