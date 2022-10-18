MAKEFLAGS += --silent

compiler = g++
cflag = -c -std=c++17
gllib = -lglut -lGLU -lGL
exec = ./Release/20120057

all_objects = ./Release/string_tokenizer.o ./Release/main.o ./Release/app_handler.o ./Release/utils.o ./Release/Point.o ./Release/timer.o ./Release/Color.o ./Release/renderer.o

./Release/string_tokenizer.o: ./app/utils/string_tokenizer.cpp
	$(compiler) $(cflag) -o ./Release/string_tokenizer.o ./app/utils/string_tokenizer.cpp

./Release/Point.o: ./app/object/Point.cpp
	$(compiler) $(cflag) -o ./Release/Point.o ./app/object/Point.cpp

./Release/Color.o: ./app/object/Color.cpp
	$(compiler) $(cflag) -o ./Release/Color.o ./app/object/Color.cpp

./Release/app_handler.o: ./app/app_handler.cpp
	$(compiler) $(cflag) -o ./Release/app_handler.o ./app/app_handler.cpp $(gllib)

./Release/utils.o: ./app/utils/utils.cpp
	$(compiler) $(cflag) -o ./Release/utils.o ./app/utils/utils.cpp $(gllib)

./Release/timer.o: ./app/utils/timer.cpp
	$(compiler) $(cflag) -o ./Release/timer.o ./app/utils/timer.cpp 

./Release/renderer.o: ./app/utils/renderer.cpp
	$(compiler) $(cflag) -o ./Release/renderer.o ./app/utils/renderer.cpp 

./Release/main.o: ./app/main.cpp
	$(compiler) $(cflag) -o ./Release/main.o ./app/main.cpp $(gllib)

clean:
	rm -rf ./Release/*.o

all: $(all_objects)
	$(compiler) -o $(exec) $(all_objects) $(gllib) -std=c++17

test: all
	$(exec) 0 20 290 500 10 | $(exec) 0 20 290 500 10 | $(exec) 1 20 290 500 10 | $(exec) 2 500 500 300 | $(exec) 3 650 650 100 300 | $(exec) 4 100 100 10 | $(exec) 5 500 500 50 100

test_line_dda: all
	$(exec) 0 20 290 450 10 | $(exec) 0 20 20 450 600

test_line_bresenham: all 
	$(exec) 1 20 290 450 10 | $(exec) 1 20 20 450 600

test_circle_midpoint: all 
	$(exec) 2 300 300 300

test_elipse_midpoint: all 
	$(exec) 3 450 450 100 300

test_parabole_midpoint: all 
	$(exec) 4 400 400 10 | $(exec) 4 400 400 \-30

test_hyperbole_midpoint: all 
	$(exec) 5 350 350 50 100