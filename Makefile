CC=gcc
CFLAGS=-O2 -march=native
TARGET=brainfucc

all: $(TARGET)

$(TARGET): brainfuck.c
	$(CC) $(CFLAGS) $< -o $@

test: $(TARGET)
	test `echo a | ./$(TARGET) test/testinput.bf` = "b"
	test `echo a | ./$(TARGET) test/looptest.bf` = "ac"
	test "`./$(TARGET) test/hello.bf`" = "Hello World!"
	test "`./$(TARGET) test/hellocomp.bf`" = "Hello World!"
	./$(TARGET) test/cellwidth.bf

clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean test
