CC=g++
CFLAGS=-Wall -pedantic -Wextra -std=c++17
LD=g++
LDFLAGS=-L/opt/homebrew/lib -lpng

SRC_DIR=src
TEST_DIR=test
BUILD_DIR=bin
DEPS_DIR=$(BUILD_DIR)/deps
BUILD_TEST_DIR=$(BUILD_DIR)/$(TEST_DIR)
TARGET=shapescape

SOURCES=$(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
HEADERS=$(wildcard $(SRC_DIR)/*.hpp $(SRC_DIR)/**/*.hpp)
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp, $(DEPS_DIR)/%.o, $(SOURCES))
TESTS=$(wildcard $(TEST_DIR)/*.cpp)

.PHONY: all
all: doc compile

.PHONY: doc
doc:
	doxygen

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: bin
bin:
	mkdir -p $(dir $(OBJECTS))

.PHONY: test
test: $(filter-out $(DEPS_DIR)/main.o, $(OBJECTS))
	mkdir -p $(BUILD_TEST_DIR)
	$(foreach TEST, $(TESTS), \
		$(CC) $(CFLAGS) $(TEST) $^ -o $(BUILD_TEST_DIR)/$(notdir $(TEST:.cpp=)) $(LDFLAGS); \
		$(BUILD_TEST_DIR)/$(notdir $(TEST:.cpp=)); \
	)

$(TARGET): $(OBJECTS)
	$(LD) $^ -o $@ $(LDFLAGS)

$(DEPS_DIR)/%.o: $(SRC_DIR)/%.cpp | bin
	$(CC) $(CFLAGS) $< -c -o $@

-include $(DEPS_DIR)/Makefile.d

$(DEPS_DIR)/Makefile.d: $(SOURCES) $(HEADERS) | bin
	$(CC) -MM $(SOURCES) > $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/ doc/ shapescape
