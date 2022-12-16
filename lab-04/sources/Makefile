MAKEFLAGS += --silent

compiler = g++
cflag = -c -std=c++2a
gllib = -lglut -lGLU -lGL
fslib = -lstdc++fs
execlib = -ltbb
use_async = -lpthread

exec = ../release/linux/20120057

all_objects = ../release/main.o \
	../release/utils.o ../release/Point.o ../release/path.o \
	../release/timer.o ../release/Color.o \
	../release/screen.o ../release/Line.o ../release/Shape.o \
	../release/Arrow.o ../release/Circle.o ../release/Elipse.o \
	../release/Rectangle.o ../release/Square.o ../release/Triangle.o

../release/Shape.o: ./app/objects/2d_objects/Shape.cpp
	$(compiler) $(cflag) -o ../release/Shape.o ./app/objects/2d_objects/Shape.cpp

../release/Arrow.o: ./app/objects/2d_objects/Arrow.cpp
	$(compiler) $(cflag) -o ../release/Arrow.o ./app/objects/2d_objects/Arrow.cpp

../release/Circle.o: ./app/objects/2d_objects/Circle.cpp
	$(compiler) $(cflag) -o ../release/Circle.o ./app/objects/2d_objects/Circle.cpp

../release/Elipse.o: ./app/objects/2d_objects/Elipse.cpp
	$(compiler) $(cflag) -o ../release/Elipse.o ./app/objects/2d_objects/Elipse.cpp

../release/Rectangle.o: ./app/objects/2d_objects/Rectangle.cpp
	$(compiler) $(cflag) -o ../release/Rectangle.o ./app/objects/2d_objects/Rectangle.cpp

../release/Square.o: ./app/objects/2d_objects/Square.cpp
	$(compiler) $(cflag) -o ../release/Square.o ./app/objects/2d_objects/Square.cpp

../release/Triangle.o: ./app/objects/2d_objects/Triangle.cpp
	$(compiler) $(cflag) -o ../release/Triangle.o  ./app/objects/2d_objects/Triangle.cpp

../release/screen.o: ./app/utils/screen.cpp
	echo Compiling screen handler...
	$(compiler) $(cflag) -o ../release/screen.o ./app/utils/screen.cpp $(use_async)

../release/Point.o: ./app/objects/2d_objects/Point.cpp
	echo Compiling point object...
	$(compiler) $(cflag) -o ../release/Point.o ./app/objects/2d_objects/Point.cpp

../release/Color.o: ./app/objects/commons/Color.cpp
	echo Compiling rgb color object...
	$(compiler) $(cflag) -o ../release/Color.o ./app/objects/commons/Color.cpp

../release/utils.o: ./app/utils/helpers.cpp
	echo Compiling utils...
	$(compiler) $(cflag) -o ../release/utils.o ./app/utils/helpers.cpp $(gllib)

../release/timer.o: ./app/utils/timer.cpp
	echo Compiling timer...
	$(compiler) $(cflag) -o ../release/timer.o ./app/utils/timer.cpp 

../release/path.o: ./app/utils/path.cpp
	echo Compiling path utils...
	$(compiler) $(cflag) -o ../release/path.o ./app/utils/path.cpp 

../release/main.o: ./app/main.cpp
	echo Compiling entry point...
	$(compiler) $(cflag) $(gllib) $(fslib)  -o ../release/main.o ./app/main.cpp 

../release/Line.o: ./app/objects/2d_objects/Line.cpp
	echo Compiling line object...
	$(compiler) $(cflag) -o ../release/Line.o ./app/objects/2d_objects/Line.cpp $(gllib) $(fslib)

clean:
	rm -rf $(all_objects)

$(exec): $(all_objects)
	$(compiler) -o $(exec) $(all_objects) $(gllib) $(fslib) -std=c++17  $(use_async)
	
all: $(exec)
	echo App compiled.

test: all $(exec)
	echo App running...
	$(exec)

setup:
	echo setting up...
	sudo apt update
	sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
