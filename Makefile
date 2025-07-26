# Nome do executável
TARGET = output/programa

# Diretórios
SRC_DIR = src
OBJ_DIR = output

# Arquivos-fonte
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/funcoes.c

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc -Iinclude

# Regra principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Limpar arquivos compilados
clean:
	rm -f $(TARGET)