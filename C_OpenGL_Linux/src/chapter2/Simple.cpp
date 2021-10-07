// Simple.c
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com
#include "../common.h"
namespace chapter2_simple
{

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
	{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);//清除使用设置的清除色


	// Flush drawing commands
    glFlush();//批量执行以上的命令
	}

///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
    {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);//设置清除时使用的颜色
    }

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(800,600);
        glutInitWindowPosition(200,800);//设置窗口显示位置,在 CreateWindow之前
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScene);//对需要重新显示,如切换窗口

	SetupRC();

	glutMainLoop();
	return 1;
    }

}
