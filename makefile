DEBUG = gdb
CC = g++
CC_FLAG = -std=c++0x -g -Wall -I
INCLUDE = include 
LIB = pthread
SRC = src/*.cpp
TARGET = bin/dealstr
TEMPFILE = source/test.txt.tmp
TESTFILE = source/test.txt
OUTFILE = source/result.txt

$(TARGET):$(SRC)
	ctags -R
	$(CC) $(CC_FLAG) $(INCLUDE) -l $(LIB) $(SRC) -o $(TARGET)

clean:				
	rm $(TARGET)

test:
#@./$(TARGET) $(TESTFILE) $(OUTFILE)
	@./$(TARGET) 10
debug:
	@$(DEBUG) ./$(TARGET) $(TESTFILE) $(OUTFILE)

.PHONY:test debug
