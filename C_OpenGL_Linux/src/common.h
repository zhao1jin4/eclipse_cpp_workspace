
#ifndef COMMON_H_
#define COMMON_H_



#ifdef __APPLE__
    #include <GLUT/GLUT.h>
#elif defined(_WIN32)
	#pragma comment (lib, "glew32.lib") //cl编译器读.lib
    #include <GL/glew.h> //注意顺序
    #include <GL/glut.h>
	//#define UNICODE //对cl, /D UNICODE /D _UNICODE
	#include <windows.h> //...
#else
    #include <GL/glut.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#endif /* COMMON_H_ */
