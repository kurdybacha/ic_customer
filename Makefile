CC=g++-5
CFLAGS=-c -g -Wall -std=c++14
LDFLAGS=
SOURCES=geo_coordinate.cpp gason.cpp json_customer_source.cpp customer_provider.cpp
TST_COORDINATE_SOURCES=tst_geo_coordinate.cpp
TST_JSON_SOURCES=tst_json_customer_source.cpp
MAIN_EXE_SOURCE=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

MAIN_EXE_OBJECTS=$(OBJECTS) $(MAIN_EXE_SOURCE:.cpp=.o)
MAIN_EXE=main

TST_COORDINATE_OBJECTS=$(OBJECTS) $(TST_COORDINATE_SOURCES:.cpp=.o)
TST_COORDINATE_EXE=tst_geo_coordinate

TST_JSON_OBJECTS=$(OBJECTS) $(TST_JSON_SOURCES:.cpp=.o)
TST_JSON_EXE=tst_json_source

all: $(MAIN_EXE) $(TST_COORDINATE_EXE) $(TST_JSON_EXE)
	
$(MAIN_EXE): $(OBJECTS) $(MAIN_EXE_OBJECTS)
	$(CC) $(LDFLAGS) $(MAIN_EXE_OBJECTS) -o $@

$(TST_COORDINATE_EXE): $(OBJECTS) $(TST_COORDINATE_OBJECTS)
	$(CC) $(LDFLAGS) $(TST_COORDINATE_OBJECTS) -o $@

$(TST_JSON_EXE): $(OBJECTS) $(TST_JSON_OBJECTS)
	$(CC) $(LDFLAGS) $(TST_JSON_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(MAIN_EXE)
	./$(MAIN_EXE)

tests: $(TST_COORDINATE_EXE) $(TST_JSON_EXE)
	./$(TST_COORDINATE_EXE)
	./$(TST_JSON_EXE)


clean:
	rm *.o $(MAIN_EXE) $(TST_COORDINATE_EXE) $(TST_JSON_EXE)
