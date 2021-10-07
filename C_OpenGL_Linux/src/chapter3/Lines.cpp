// Lines.c
// Demonstrates primative GL_LINES
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com


#include "../common.h"
namespace chapter3_lines
{


// Define a constant for the value of PI
#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
	{
        GLfloat x,y,z,angle; // Storeage for coordinates and angles

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);//(角度,从原点到x,y,z 的直线);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Call only once for all remaining points
	glBegin(GL_LINES);//两个配对,第一线和第二线要相连必须有相同点,如果是奇数个点,最后一个丢弃

	z = 0.0f;
	for(angle = 0.0f; angle <= GL_PI; angle += (GL_PI / 20.0f))
		{
		// Top half of the circle
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		glVertex3f(x, y, z);

		// Bottom half of the circle
		x = 50.0f*sin(angle+GL_PI);
		y = 50.0f*cos(angle+GL_PI);
		glVertex3f(x, y, z);
		}

	// Done drawing points
	glEnd();

	//glutWireCone(20,20,5,3);//base底半径,高,slices圆形分段数,stacks高度分段数
	//glutWireSphere(20,5,3);
	//glutWireTorus(3,52,5,8);//第一个是环的粗细
	//glutWireTeapot(30.0f);//Solid 茶壶
	// Restore transformations
	glPopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
	}

///////////////////////////////////////////////////////////
// This function does any needed initialization on the 
// rendering context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);
	}

///////////////////////////////////////////////////////////
// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
	}

///////////////////////////////////////////////////////////
// Window has changed size, recalculate projection
void ChangeSize(int w, int h)
	{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

void MouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			//wprintf(L"abc左键按下了");//中文不显示???
			//printf("left buttion 按下了\n");//中文OK
			//printf("left buttion 按下了");//中文不行???
			fflush(stdout);
		}
	}
}
///////////////////////////////////////////////////////////
// Main Program Entry Point
int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);

	glutInitWindowPosition(200,800);
	glutCreateWindow("Lines Example");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);//按键事件
	glutMouseFunc(MouseFunc);//鼠标事件
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
};

