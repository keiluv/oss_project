CC = gcc
CFLAGS = -g -Wall
TARGETS = main
OBJECTS = main.c requisition.o
.SUFFIXES = .c .o
main_debug : $(TARGETS)
main_debug : DEBUGOPTION = -DDEBUG

$(TARGETS) : $(OBJECTS)
	$(CC) $(CFLAGS) $(EDBUGOPTION) -o $@ $^

.c .o :
	$(CC) $(CFLAGS) $(EDBUGOPTION) -c $<

clean :
	rm *.o $(TARGETS)
