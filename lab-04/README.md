# Computer Graphic - Lab 04

## General information

- Student: Tran Ngoc Do
- ID: 20120057

## Source structure
- This project is developed based on lab-03 project structure:
    - `app/main.cpp`: entry point of the program
    - `res`: store all resources of program
    - `app/utils`: helpers
    - `app/objects/3d_objects`: includes Shape3D.cpp and others.
    - `app/commons`: includes object that can be used of both 2d and 3d rendering.
    - `app/externals/Simple-OpenGL-Image-Library`: SOIL project
    - `app/externals/glext`: glext libs

## Setup
- Add all files from `app/externals/Simple-OpenGL-Image-Library/src` to project.
- Copy `include` and `lib` folder from `app/externals/glext` to Visual Studio files, common: `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS`

## **Sources code**

Project structure:
``` 
    ├─── app
    |   ├─── externals /
    |   ├─── objects /
    |   ├─── utils /
    |   └─── main.cpp
    └─── res
```

- `app/externals/`: Store all external dependencies.
- `app/objects`: 3D-objects definition.
- `app/utils`: helper functions.
- `app/main.cpp`: store entry point of the program.
- `res`: store all resources to run the program.

## **Compiling**

Firstly, add all the source files of `Simple-OpenGL-Image-Library` to the project then. Follow these follow instruction: [here](../lab-01/README.md).

`Note`: the project required `glext` library, so you need to: 
- Copy `include` and `lib` folders from `app/externals/glext` to Visual Studio files: 
```sh
C:/Program Files (x86)/Microsoft Visual Studio/[VERSION]/[TYPE]/VC/Auxiliary/VS. 
```
- For example, I use Visual Studio 2019 Community, so the path should be: 

```sh
C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS
```


## **Demo**

<p align="center">
    <img src="demo/demo.gif">
</p>
