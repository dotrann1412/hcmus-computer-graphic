MAKEFLAGS += --silent

compiler = g++
cflag = -c -std=c++2a
gllib = -lglut -lGLU -lGL
fslib = -lstdc++fs
exec = ../release/20120057

all_objects = ../release/string_tokenizer.o ../release/main.o \
	../release/utils.o ../release/Point.o ../release/path.o \
	../release/timer.o ../release/Color.o ../release/renderer.o \
	../release/screen.o ../release/Line.o ../release/Shape.o \
	../release/Arrow.o ../release/Circle.o ../release/Elipse.o \
	../release/Rectangle.o ../release/Square.o ../release/Triangle.o


../release/Shape.o: ./app/objects/Shape.cpp
	$(compiler) $(cflag) -o ../release/Shape.o ./app/objects/Shape.cpp

../release/Arrow.o: ./app/objects/Arrow.cpp
	$(compiler) $(cflag) -o ../release/Arrow.o ./app/objects/Arrow.cpp

../release/Circle.o: ./app/objects/Circle.cpp
	$(compiler) $(cflag) -o ../release/Circle.o ./app/objects/Circle.cpp

../release/Elipse.o: ./app/objects/Elipse.cpp
	$(compiler) $(cflag) -o ../release/Elipse.o ./app/objects/Elipse.cpp

../release/Rectangle.o: ./app/objects/Rectangle.cpp
	$(compiler) $(cflag) -o ../release/Rectangle.o ./app/objects/Rectangle.cpp

../release/Square.o: ./app/objects/Square.cpp
	$(compiler) $(cflag) -o ../release/Square.o ./app/objects/Square.cpp

../release/Triangle.o: ./app/objects/Triangle.cpp
	$(compiler) $(cflag) -o ../release/Triangle.o  ./app/objects/Triangle.cpp

../release/screen.o: ./app/utils/screen.cpp
	echo Compiling screen handler...
	$(compiler) $(cflag) -o ../release/screen.o ./app/utils/screen.cpp

../release/string_tokenizer.o: ./app/utils/string_tokenizer.cpp
	echo Compiling string tokenizer...
	$(compiler) $(cflag) -o ../release/string_tokenizer.o ./app/utils/string_tokenizer.cpp

../release/Point.o: ./app/objects/Point.cpp
	echo Compiling point object...
	$(compiler) $(cflag) -o ../release/Point.o ./app/objects/Point.cpp

../release/Color.o: ./app/objects/Color.cpp
	echo Compiling rgb color object...
	$(compiler) $(cflag) -o ../release/Color.o ./app/objects/Color.cpp

../release/utils.o: ./app/utils/utils.cpp
	echo Compiling utils...
	$(compiler) $(cflag) -o ../release/utils.o ./app/utils/utils.cpp $(gllib)

../release/timer.o: ./app/utils/timer.cpp
	echo Compiling timer...
	$(compiler) $(cflag) -o ../release/timer.o ./app/utils/timer.cpp 

../release/renderer.o: ./app/utils/renderer.cpp
	echo Compiling renderer...
	$(compiler) $(cflag) -o ../release/renderer.o ./app/utils/renderer.cpp $(fslib)

../release/path.o: ./app/utils/path.cpp
	echo Compiling path utils...
	$(compiler) $(cflag) -o ../release/path.o ./app/utils/path.cpp 

../release/main.o: ./app/main.cpp
	echo Compiling entry point...
	$(compiler) $(cflag) -o ../release/main.o ./app/main.cpp $(gllib) $(fslib)

../release/Line.o: ./app/objects/Line.cpp
	echo Compiling line object...
	$(compiler) $(cflag) -o ../release/Line.o ./app/objects/Line.cpp $(gllib) $(fslib)

clean:
	rm -rf ../release/*.o

all: $(all_objects)
	echo Compiling App...
	$(compiler) -o $(exec) $(all_objects) $(gllib) $(fslib) -std=c++17
	echo App compiled.

test: all
	echo App running...
	$(exec)

setup:
	echo setting up...
	sudo apt update
	sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
