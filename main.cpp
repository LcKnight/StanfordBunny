#include"plyReader.h"
#include"light.h"
#include "bunnyDraw.h"
#include <stdlib.h>
#include <GL/freeglut_ext.h>
//声明二维数组
GLfloat Points_[40000][3];
int TrianglesIndex_[70000][3];

// 由于二维数组不可直接作为二维指针使用 此处使用了指针数组
//真实不知大小的规模的模型 也可以在plyReader.h处 改用new方法分配空间 此处时间不够 就这样了
GLfloat* Points [40000];
int* TrianglesIndex[70000];

//此处同理 表示三角形片元总数
int TriangleIndexNum;
const string path = "bunny_iH.ply2";

//缩放倍数
GLdouble scaleTimes = 1;
//事件flag
bool mouseLeftDown;
bool mouseRightDown;
bool mouseWheelDown;

//当前指针X，Y
double pointX,pointY;


//物体平移量
GLfloat objectDistanceX;
GLfloat objectDistanceY;

//光源平移量
GLfloat lightSourceDistanceX;
GLfloat lightSourceDistanceY;

//摄像机旋转量
GLfloat cameraAngleX;
GLfloat cameraAngleY;


//摄像机视点z值
double r = 100;

//设置右键模式
//objectTranslate 表示当前为物体旋转模式
//lightTranslate 表示当前为光源旋转模式
enum mouseRightMode {objectTranslate,lightTranslate};
mouseRightMode mode= (mouseRightMode)objectTranslate;
//啦啦啦
drawMode drawmode = (drawMode)faces;

//此处用来设置拾取模式
#define SIZE 512
int selectedId=0;
GLfloat color_selected[3]={ 1.0,0.0,0.0 };
GLuint selectedPoint=-1;






void init()
{
	for (int i = 0; i < 40000; i++)
	{
		Points[i] = Points_[i];
	}
	for (int i = 0; i < 70000; i++)
	{
		TrianglesIndex[i] = TrianglesIndex_[i];
	}
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_diffuse[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat material_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat material_shiness = { 60.0 };
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 0.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat light_position[] = { 0,0,20,1 };
	lightsource ls = lightsource(light_position, light_specular, light_diffuse, light_ambient);
	material m = material(material_specular, material_diffuse, material_ambient, material_shiness);

	lightInit(m, ls);


	gluLookAt(0, 0, 50, 0, 0, -1, 0, 1, 0);
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glColor3f(0.0, 0.0, 0.0);
	plyRead(path, Points, TrianglesIndex, &TriangleIndexNum);

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(objectDistanceX, -objectDistanceY, 0);
	if (mode == lightTranslate)
	{
		GLfloat light_position[] = { lightSourceDistanceX,lightSourceDistanceY,20,1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	/*
	* 之前以为两种模式必须分开 后来发现 必须继承已经实现过的平移变换
	*/
	//else if (mode == objectTranslate)
	//{
	//	glTranslatef(objectDistanceX, -objectDistanceY, 0);
	//}

	//gluLookAt(objectDistanceX, objectDistanceY, r, 0, 0, -1, 0, 1, 0);
	//glTranslatef(dTransX, -dTransY, 0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	glScalef(scaleTimes, scaleTimes, scaleTimes);
	/*if (selectedId != 0)
	{
		drawBunny(Points, TrianglesIndex, TriangleIndexNum,);
		{
			glPointSize(5.0f);
			glBegin(GL_POINTS);
			for (int i = 0; i < selectedNum; i++)
			{
				GLfloat a[3] = { Points[selected_points[i]][0], Points[selected_points[i]][0], Points[selected_points[i]][2] };
				
				glVertex3fv(a);
				glColor3f(1.0, 1.0, 1.0);
			}


			glDisable(GL_COLOR_MATERIAL);

			glEnd();


		}



		glEnd();
	}
	else
	{}*/

		

	drawBunny(Points, TrianglesIndex, 34834, TriangleIndexNum, drawmode, pointX, pointY);


	glutSwapBuffers();


}



void mouse(int button, int state, int x, int y) {

	pointX = x;
	pointY = y;
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
			
		}
		else if (state == GLUT_UP)
		{
			mouseLeftDown = false;
		}

	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
		{
			mouseRightDown = false;
		}
		
	}


}
void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		//放大
		scaleTimes *= 1.1;
	}
	else if (dir < 0)
	{
		//缩小
		scaleTimes *= 0.9;

	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y) {

	
	//假设左右键同时按下会有啥现象发生 两个flag都是true
	if (mouseLeftDown)
	{
		cameraAngleY += (x - pointX) * 0.1f;
		cameraAngleX += (y - pointY) * 0.1f;

	}
	else if (mouseRightDown)
	{
		if (mode == objectTranslate)
		{
			objectDistanceX += (x - pointX) * 0.03f;
			objectDistanceY += (y - pointY) * 0.03f;
		}
		if (mode == lightTranslate)
		{
			lightSourceDistanceX += (x - pointX) * 0.03f;
			lightSourceDistanceY += (y - pointY) * 0.03f;
		}

	}
	pointX = x;
	pointY = y;

	glutPostRedisplay();


}

void keyboard(unsigned char key, int x, int y) {

	
	
	//表示 zoom in
	if (key == 'i') {
		scaleTimes *= 1.1;
		glutPostRedisplay();
	}
	//表示 zoom out
	else if (key == 'q') 
	{
		drawmode = (drawMode)((drawmode+1)%2);
		glutPostRedisplay();

	}
	else if (key == 'o') {
		scaleTimes *= 0.9;
		glutPostRedisplay();
	}
	//表示 switch s
	else if (key == 's')
	{
		mode = (mouseRightMode)((mode + 1) % 2);
		glutPostRedisplay();
	}
	else if (key == 'p') 
	{
		if (drawmode != select) {
			drawmode = select;
		}
		else {
			drawmode = faces;
		}
		glutPostRedisplay();
	}

		


	
}
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-15.0, 15.0, -15.0, 15.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);

}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("StanfordBunny-金泽辉-2018302120094");
	


	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboard);
	glutMainLoop();



}
