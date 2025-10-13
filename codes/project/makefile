#basic setting
CXX := g++
CXXFLAGS := -std=17 -Wall -MMD -MP

#debug module
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g -O0 -DDEGBG
	BUILD_DIR :=build/debug
else
	CXXFLAGS += -O2
	BUILD_DIR := build/release
endif

#file collect

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

#default target
.PHONY: all run clean

all: $(BUILD_DIR)/app


#link rule
$(BUILD_DIR)/app: $(OBJ)
	$(CXX) $(OBJ) -o $@
	@exho "Build succes: $@"

#assert rule
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#auto deps
-include $(OBJ:.o=.d)

#cmd
run: $(BUILD_DIR)/app
	@echo "running program..."
	./$(BUILD_DIR)/app

clean:
	rm -rf build
	@echo "cleaned all build files."
	

