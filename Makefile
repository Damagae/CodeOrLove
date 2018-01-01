CC       	=  g++
CFLAGS   	= -Wall -O2 -g --std=c++11

APP_BIN 	= story-game

SRC_PATH 	= src
OBJ_PATH 	= obj
INC_PATH = -I include
BIN_PATH 	= bin

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC_FILES))

all : $(APP_BIN)

$(APP_BIN) : $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./bin/$(APP_BIN) &"
	@echo "--------------------------------------------------------------"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)
