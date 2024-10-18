CXXFLAGS ?= -fsycl -g -O0

SOURCES= $(wildcard *-device-discovery.cpp) $(wildcard *-vector-add-*.cpp)
EXAMPLES= $(patsubst %.cpp,%,$(SOURCES))
BUILD_DIR=build

.PHONY: all pre-build format clean

all: $(EXAMPLES)

pre-build: ; @mkdir $(BUILD_DIR)

$(EXAMPLES) : % : %.cpp | pre-build; icpx $< -o $(BUILD_DIR)/$@ $(CXXFLAGS)

format: ; clang-format -i *.cpp

clean: ; @$(RM) -rf $(BUILD_DIR)

print-% : ; @echo $* = $($*)
