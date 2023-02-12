# **Computer Graphic - Lab 01 - 2D Object Drawing**

## **Student Information**

- Name: Tran Ngoc Do
- ID: 20120057
- Class: 20TN

## **Source code**

Project structure
``` 
    ├─── app
    │   ├─── object/
    │   ├───utils/
    |   └─── main.cpp
    └─── Sample-Input/
```

- Source code is stored in `./sources/app`, the entry point is `int main(int, char**)` from `./sources/app/main.cpp`.

- `object` folder store all the class objects that make the source code structure more clearly and easy to follow.

- `utils` this folder contains all the code that handler main processing like **object-rendering**, **Algorithms**, or some helper functions such as **Timer**, **Path**, ...

## **Compiling**

### Linux or WSL - Use Makefile

Requirements:
- C++ version: C++17

- GNU make

The Makefile includes some helpful flags:

- `all`: compile all the dependencies if needed and link everything to binary executable file named `20120057`. The release file will be put on the `./Release` foler.

- `test`: Run program with default input file (multiple objects will be printed on the glut window). Program will be recompiled if needed. 

- `clean`: Clean all oject files that required by linker. 

- `setup`: Automatic setup all of the necessary.

### Windows OS or MacOS - Use Visual Vtudio

Requirements:
- `C++ version:` C++17

- `C version:` C14

First of all, glut and opengl must be installed on your machine. Follow this [link](https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/) to install glut and opengl on your machine. Then, open the project in Visual Studio 2019 and enjoy the source code.

`Note`: All the configurations of project and solution is set.

## **Application instruction**

To execute the program, use the following command:

```sh
  [path_to_executable] [algorithm] [extra parameters]
```

- Draw a single line in the glut windows:
  - algorithm code:
    - **-1**: Use built-in method
    - **0** : Use DDA algorithm
    - **1** : Use Bresenham algorithm
  - parameters: `x1, y1, x2, y2`; where `(x1, y1)`, `(x2, y2)` are the coordinates of the first and last vertices respectively.

- Draw a single circle in the glut windows:
  - algorithm code:
    - **2** : Use Midpoint algorithm
  - parameters: `xc, yc, r`; where `(xc, yc)` is the coordinate of the center, and `r` is the radius of the circle.

- Draw a single elipse in the glut windows:
  - algorithm code:
    - **3** : Use Midpoint algorithm
  - parameters: `xc, yc, rx, ry`; where `(xc, yc)` is the coordinate of the center, and `rx`, `ry` are the length of semi-major and semi-minor axis of the elipse in that order.

- Draw a single parapole in the glut windows:
  - algorithm code:
    - **4** : Use Midpoint algorithm
  - parameters: `xc, yc, p`; where `(xc, yc)` is the coordinate of the center, and `p` is the distance from center to focal point.

- Draw a single hyperpole in the glut windows:
  - algorithm code:
    - **5** : Use Midpoint algorithm
  - parameters: `xc, yc, rx, ry`; where `(xc, yc)` is the coordinates of the center then `rx` and `ry` are the semi-length of transverse axis.

To draw multiple objects, use the following command:

```sh
  [path_to_executable] -f [path_to_file]
```

- Input file is the a multiple-line where each line contains the information of an object. The format of each line as followed:

```sh
  [algorithm] [extra parameters]
```