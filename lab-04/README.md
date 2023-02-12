# Computer Graphic - Lab 04

## General information

- Student: Tran Ngoc Do
- ID: 20120057

## **Sources code**

Project structure:
``` 
    ├─── app
    |   ├─── externals /
    |   ├─── objects /
    |   ├─── utils /
    |   └─── main.cpp
    └─── res / 
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
