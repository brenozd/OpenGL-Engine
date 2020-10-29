#####################
##Compiler Settings##
#####################
CXX = g++
CXX_FLAGS = -std=c++11
LD_FLAGS = -lglfw -lGL -lGLEW
APPNAME = OpenGL

#####################
#### Dir Settings ###
#####################
BIN = bin
SRC = src
OBJ = obj

#####################
## Target Variables #
#####################
EXT = .cpp
SRC_FILES = $(wildcard $(SRC)/*$(EXT))
OBJ_FILES = $(SRC_FILES:$(SRC)/%$(EXT)=$(OBJ)/%.o)
DEP_FILES = $(OBJ_FILES:$(OBJ)/%.o=%.d)

#####################
###### Targets ######
#####################

all: clean $(APPNAME) run

# Build Application
$(APPNAME) : $(OBJ_FILES)
	@echo "🚧 Building..."
	$(CXX) $(CXX_FLAGS) -o $(BIN)/$@ $^ $(LD_FLAGS)

#Run executable
.PHONY: run
run:
	clear
	@echo "🚀 Running..."
	./$(BIN)/$(APPNAME)

#Clean executable
.PHONY: clean
clean:
	@echo "🧹 Cleaning executable..."
	-rm $(BIN)/*

#Clean dependencies
.PHONY: cleand
cleand:
	@echo "🧹 Cleaning dependencies..."
	-rm $(OBJ)/*.d $(OBJ)/*.o

#Create dependencie files
%.d: $(SRC)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJ)/%.o) >$(OBJ)/$@

#Includes .d
-include $(DEP_FILES)

#Create .o files
$(OBJ)/%.o: $(SRC)/%$(EXT)
	$(CXX) $(CXX_FLAGS) -o $@ -c $<