CXX = g++
CXXFLAGS = -Wall
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = chess

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

clean:
	rm -f *.o
	rm -f $(TARGET)
