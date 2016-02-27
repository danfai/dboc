CXXFLAGS=-std=c++11
CC=gcc
CXX=g++
OUT=dboc
LIBS=
INCLUDES=
OBJDIR=obj

SRC=$(shell find -name '*.cpp')
OBJ=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

all: $(OUT)

debug: CXXFLAGS += -Wall -g3
debug: $(OUT)

dir:
	@ mkdir -p $(OBJDIR) $(BINDIR) 

$(OUT): dir $(OBJ)
	$(CXX) -o $(OUT) $(OBJ) $(LIBS)

$(OBJDIR)/%.o: %.cpp
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o "$@" -MMD -c "$<" 

clean:
	rm -rf $(OBJDIR) $(OUT)

# pull in dependency info for *existing* .o files
-include $(OBJ:.o=.d)

