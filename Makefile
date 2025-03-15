
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
SRCS = $(wildcard src/*.cpp)  # detect all .cpp files in src
TARGET = main

$(TARGET): $(SRCS)
	g++ $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	/bin/rm -f $(TARGET)
