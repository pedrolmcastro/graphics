CXX := g++
LDLIBS += -lglfw -lGL -lGLEW -lm
CXXFLAGS += -std=c++2a -MMD -MP -Iinclude -Ivendor/glm -Wall -Werror -pedantic

BIN := bin/main.out
SRC := $(shell find src -name *.cpp)
OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC))
DEP := $(patsubst src/%.cpp, obj/%.d, $(SRC))


$(BIN) : $(OBJ)
	@$(CXX) $^ -o $@ $(LDLIBS)

obj/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

run: $(BIN)
	@$(BIN)

dep:
	@apt install g++ mesa-common-dev libglew-dev libglfw3-dev


clean:
	@$(RM) $(OBJ) $(DEP) $(BIN)

.PHONY : clean


-include $(DEP)
