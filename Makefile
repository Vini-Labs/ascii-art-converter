CC     = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c \
      src/image.c \
      src/gray.c  \
      src/ascii.c \
      src/output.c

TARGET = ascii

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm -f $(TARGET)