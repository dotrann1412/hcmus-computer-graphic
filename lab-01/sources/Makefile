MAKEFLAGS += --silent

compiler = g++
cflag = -c -std=c++17
gllib = -lglut -lGLU -lGL
exec = ./Release/20120057

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

all: ./Release/string_tokenizer.o ./Release/main.o ./Release/app_handler.o ./Release/utils.o ./Release/Point.o ./Release/timer.o ./Release/Color.o ./Release/renderer.o
	$(compiler) -o $(exec) ./Release/main.o ./Release/app_handler.o ./Release/string_tokenizer.o ./Release/utils.o ./Release/Point.o ./Release/timer.o ./Release/Color.o ./Release/renderer.o $(gllib) -std=c++17

test: all
	$(exec) 0 20 290 260 10 &

test_dda: all
	$(exec) 0 20 290 260 10 &

test_bresenham: all 
	$(exec) 1 20 290 260 10 &

test_midpoint_circle: all 
	$(exec) 2 150 150 70 & 

test_midpoint_elipse: all 
	$(exec) 3 150 150 70 100 &

test_midpoint_parabole: all 
	$(exec) 4 100 100 -10 &

test_midpoint_hyperbole: all 
	$(exec) 5 100 100 10 40 &