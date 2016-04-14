CC=g++-5
CFLAGS=-c -g -Wall -std=c++14
LDFLAGS=
SOURCES=geo_coordinate.cpp gason.cpp json_customer_source.cpp customer_provider.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
