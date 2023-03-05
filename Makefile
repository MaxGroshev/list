TARGET = list
CC=gcc
CFLAGS = -c -std=c++11

PREF_OBJ  = ./obj/
PREF_STAT = ./dump_info/

SRC    = $(wildcard *.cpp)                         #include of all files with .cpp
OBJ    = $(patsubst %.cpp, $(PREF_OBJ)%.o, $(SRC)) #turn .cpp into .o

all:     $(TARGET)



$(TARGET):  $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

$(PREF_OBJ)%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@


valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(TARGET)

graphviz:
	dot $(PREF_STAT)list_dump.dot -T pdf -o $(PREF_STAT)list_dump.pdf
	dot $(PREF_STAT)list_dump.dot -T png -o $(PREF_STAT)list_dump.png

.PHONY : clean
clean:
	rm -rf $(PREF_OBJ)*.o $(TARGET)
