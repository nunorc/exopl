
CXX       := g++
CXX_FLAGS := -Wall -std=c++11

SRC := src
LIB := -lcurl -ljsoncpp
BIN := exopl

OBJ = $(SRC)/exoplanet.o $(SRC)/ysapi.o $(SRC)/exopl.o $(SRC)/main.o

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(LIB) $^ -o $@ $(LIBRARIES)

$(SRC)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	-rm -f $(BIN) $(SRC)/*.o
