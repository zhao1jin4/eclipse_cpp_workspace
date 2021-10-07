#include "../common.h"

int test(int argc, char **argv) {

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//重复贴图
	glEnable(GL_TEXTURE_2D);

	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);



	static GLint vertices[] = {25, 25,
	100, 325,
	175, 25,
	175, 325,
	250, 25,
	325, 325};
	static GLfloat colors[] = {1.0, 0.2, 0.2,
	0.2, 0.2, 1.0,
	0.8, 1.0, 0.2,
	0.75, 0.75, 0.75,
	0.35, 0.35, 0.35,
	0.5, 0.5, 0.5};

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_INT, 0, vertices);




	return 1;


}
