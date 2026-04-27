CXX      = g++
CXXFLAGS = -Wall -std=c++17 -O2
TARGET   = rocket

all: $(TARGET)

$(TARGET): rocket.cpp
	$(CXX) $(CXXFLAGS) rocket.cpp -o $(TARGET) -lm

clean:
	rm -f $(TARGET) ascent.csv
