TARGET = txt_backuper



SRC_DIR = src
BIN_DIR = bin
CFLAGS = -Wall -Wextra -std=c11 -g
OBJS = $(BIN_DIR)/main.o $(BIN_DIR)/logger.o $(BIN_DIR)/scaner.o $(BIN_DIR)/files.o $(BIN_DIR)/backup.o

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BIN_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/logger.h $(SRC_DIR)/scaner.h $(SRC_DIR)/files.h $(SRC_DIR)/backup.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(BIN_DIR)/main.o

$(BIN_DIR)/logger.o: $(SRC_DIR)/logger.c $(SRC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/logger.c -o $(BIN_DIR)/logger.o

$(BIN_DIR)/scaner.o: $(SRC_DIR)/scaner.c $(SRC_DIR)/scaner.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/scaner.c -o $(BIN_DIR)/scaner.o

$(BIN_DIR)/files.o: $(SRC_DIR)/files.c $(SRC_DIR)/files.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/files.c -o $(BIN_DIR)/files.o

$(BIN_DIR)/backup.o: $(SRC_DIR)/backup.c $(SRC_DIR)/backup.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/backup.c -o $(BIN_DIR)/backup.o

clean:
	rm -f $(OBJS) $(TARGET)