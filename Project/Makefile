CXX := g++-10
LDLIBS += -lglfw -lGL -lGLEW -lm
CXXFLAGS += -std=c++2a -MMD -MP -Iinclude -Ivendor/glm -Wall -Werror -pedantic

BND := bin
BIN := $(BND)/main.out
SRC := $(shell find src -name *.cpp)
OBD := obj
OBJ := $(patsubst src/%.cpp, $(OBD)/%.o, $(SRC))
DEP := $(patsubst src/%.cpp, $(OBD)/%.d, $(SRC))


$(BIN) : $(OBJ) | $(BND)/
	@printf "CC %s -> %s\n" "$^" "$@"
	@$(CXX) $^ -o $@ $(LDLIBS)

obj/%.o : src/%.cpp
	@$(MAKE) -s $(dir $@)
	@printf "CC %s -> %s\n" $< $@
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

run: $(BIN)
	@$(BIN)

dep:
	@sudo apt install g++-10 mesa-common-dev libglew-dev libglfw3-dev
	git submodule init
	git submodule update --recursive

%/:
	@printf "MKDIR %s\n" $@
	@mkdir -p $@

clean:
	@$(RM) -rf $(OBD) $(BND)

.PHONY : clean dep run dir


-include $(DEP)
