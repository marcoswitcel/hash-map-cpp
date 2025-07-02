# Configurações de compilação
## usando g++ não precisa do parâmetro -lstdc++
CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++2a
LFLAGS = -lSDL2 -lSDL2_ttf
DEF = -DDEV_CODE_ENABLED

# Configurações gerais
SOURCE_FOLDER_NAME=src
TESTS_FOLDER_NAME=tests
BUILD_FOLDER_NAME=target

build-folder-setup:
	@ mkdir -p $(BUILD_FOLDER_NAME)

main: build-folder-setup ./$(SOURCE_FOLDER_NAME)/main.cpp  
	$(CC) ./$(SOURCE_FOLDER_NAME)/main.cpp -o $(BUILD_FOLDER_NAME)/main $(CFLAGS) $(LFLAGS) $(DEF)

tests: build-folder-setup ./$(TESTS_FOLDER_NAME)/main.cpp  
	$(CC) ./$(TESTS_FOLDER_NAME)/main.cpp -o $(BUILD_FOLDER_NAME)/tests $(CFLAGS) $(LFLAGS) $(DEF)

run: main
	@echo "cd ./$(BUILD_FOLDER_NAME)"
	@echo ./main
	@echo "================"
	@cd ./$(BUILD_FOLDER_NAME) && ./main
	@echo "\n================\n"

run-tests: tests
	@echo "cd ./$(BUILD_FOLDER_NAME)"
	@echo ./tests
	@echo "================"
	@cd ./$(BUILD_FOLDER_NAME) && ./tests
	@echo "\n================\n"
