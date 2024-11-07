# Nombre del ejecutable final
TARGET = tcpServer

# Directorios
SRC_DIR = src
INCLUDE_DIR = inc
BUILD_DIR = bin

# Archivos fuente y objetos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Compilador y flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Regla para compilar el ejecutable final
$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^
	@echo "Ejecutable $@ creado."

# Regla para compilar cada archivo .c a .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado $< a $@"

# Crear el directorio de build si no existe
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Limpieza de archivos compilados
clean:
	rm -rf $(BUILD_DIR)/*
	@echo "Archivos en $(BUILD_DIR) eliminados."

# Ejecución del programa
run: $(BUILD_DIR)/$(TARGET)
	@echo "Ejecutando $<..."
	@./$(BUILD_DIR)/$(TARGET)

# PHONY para evitar conflictos con archivos llamados igual
.PHONY: clean run
