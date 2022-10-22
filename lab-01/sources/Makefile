MAKEFLAGS += --silent

compiler = g++
cflag = -c -std=c++17
gllib = -lglut -lGLU -lGL
fslib = -lstdc++fs
exec = ./Release/20120057

all_objects = ./Release/string_tokenizer.o ./Release/main.o \
	./Release/utils.o ./Release/Point.o ./Release/path.o \
	./Release/timer.o ./Release/Color.o ./Release/renderer.o \

./Release/string_tokenizer.o: ./app/utils/string_tokenizer.cpp
	$(compiler) $(cflag) -o ./Release/string_tokenizer.o ./app/utils/string_tokenizer.cpp

./Release/Point.o: ./app/object/Point.cpp
	$(compiler) $(cflag) -o ./Release/Point.o ./app/object/Point.cpp

./Release/Color.o: ./app/object/Color.cpp
	$(compiler) $(cflag) -o ./Release/Color.o ./app/object/Color.cpp

./Release/utils.o: ./app/utils/utils.cpp
	$(compiler) $(cflag) -o ./Release/utils.o ./app/utils/utils.cpp $(gllib)

./Release/timer.o: ./app/utils/timer.cpp
	$(compiler) $(cflag) -o ./Release/timer.o ./app/utils/timer.cpp 

./Release/renderer.o: ./app/utils/renderer.cpp
	$(compiler) $(cflag) -o ./Release/renderer.o ./app/utils/renderer.cpp $(fslib)

./Release/path.o: ./app/utils/path.cpp
	$(compiler) $(cflag) -o ./Release/path.o ./app/utils/path.cpp 

./Release/main.o: ./app/main.cpp
	$(compiler) $(cflag) -o ./Release/main.o ./app/main.cpp $(gllib) $(fslib)

clean:
	rm -rf ./Release/*.o

all: $(all_objects)
	$(compiler) -o $(exec) $(all_objects) $(gllib) $(fslib) -std=c++17

test: all
	$(exec) -f ./Sample-Input/default.in 

test_line_dda: all
	$(exec) 0 20 290 450 10

test_line_bresenham: all 
	$(exec) 1 20 290 450 10

test_circle_midpoint: all 
	$(exec) 2 300 300 300

test_elipse_midpoint: all 
	$(exec) 3 450 450 100 300

test_parabole_midpoint: all 
	$(exec) 4 400 400 10

test_hyperbole_midpoint: all 
	$(exec) 5 350 350 50 100

setup:
	echo setting up...
	sudo apt update
	sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
