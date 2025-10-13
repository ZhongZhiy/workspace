CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -MMD -MP

OBJ := main.o adder.o

app: $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

.PHONY: clean
clean:
	rm -f app $(OBJ) $(OBJ:.o=.d)

.PHONY: run
run: app
	./app

.PHONY: fmt
fmt:
	clang-format -i *.cpp *.hpp
