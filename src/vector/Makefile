.PHONY: all clean

CC                   := g++
CPPFLAGS             := -g -Wall -std=c++17

BINARIES_PATH        := ../../bin
INCLUDES_PATH        := ../includes

VECTOR_TEST_PROG     := vector_test
VECTOR_TEST_SRCS     := vector_test.cpp
VECTOR_TEST_OBJS     := $(patsubst %.cpp,%.o,$(VECTOR_TEST_SRCS))

all: build_vector_test

build_vector_test:
	$(CC) $(CPPFLAGS) -fno-elide-constructors -I$(INCLUDES_PATH) -o $(VECTOR_TEST_PROG) $(VECTOR_TEST_SRCS)

clean: