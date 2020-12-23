#include"bunnyDraw.h"
#include<GL/GL.h>
#include<stdio.h>
//triangle 数据类型为
//第一个点a 0 0 0（例
//第二个点b 0 0 0
//第三个点c 0 0 0
void normalVector(triangle t, GLfloat* Vector)
{
	GLfloat X1[3];//ab向量
	GLfloat X2[3];//ac向量
	for (int i = 0; i < 3; i++)
	{
		X1[i] = t.a[i] - t.b[i];
		X2[i] = t.a[i] - t.c[i];
	}
	Vector[0] = X1[1] * X2[2] - X1[2] * X2[1];
	Vector[1] = X2[0] * X1[2] - X2[2] * X1[0];
	Vector[2] = X1[0] * X2[1] - X1[1] * X2[0];


}

void drawBunny(GLfloat** Points, int** TriangleIndex, int PointsNum,int TriangleIndexNum, drawMode mode, GLdouble mouseX , GLdouble mouseY)
{

	if (mode == faces)
	{
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < TriangleIndexNum; i++)
		{
			GLfloat a[3] = { Points[TriangleIndex[i][0]][0], Points[TriangleIndex[i][0]][1], Points[TriangleIndex[i][0]][2] };
			GLfloat b[3] = { Points[TriangleIndex[i][1]][0], Points[TriangleIndex[i][1]][1], Points[TriangleIndex[i][1]][2] };
			GLfloat c[3] = { Points[TriangleIndex[i][2]][0], Points[TriangleIndex[i][2]][1], Points[TriangleIndex[i][2]][2] };
			GLfloat norVector[3];
			triangle t = triangle(a, b, c);
			normalVector(t, norVector);
			glNormal3f(norVector[0], norVector[1], norVector[2]);
			glVertex3f(a[0], a[1], a[2]);
			glVertex3f(b[0], b[1], b[2]);
			glVertex3f(c[0], c[1], c[2]);
		}
		glEnd();
	}
	else if (mode == points)
	{
		glPointSize(1.0f);
		for (int i = 0; i < PointsNum; i++)
		{
			if (mode == GL_SELECT)
			{
				glLoadName(i + 1);
			}
			glBegin(GL_POINTS);
			glVertex3f(Points[i][0], Points[i][1], Points[i][2]);
			glEnd();
		}
	}
	else if (mode == select)
	{
		//glBegin(GL_TRIANGLES);
		//for (int i = 0; i < TriangleIndexNum; i++)
		//{
		//	GLfloat a[3] = { Points[TriangleIndex[i][0]][0], Points[TriangleIndex[i][0]][1], Points[TriangleIndex[i][0]][2] };
		//	GLfloat b[3] = { Points[TriangleIndex[i][1]][0], Points[TriangleIndex[i][1]][1], Points[TriangleIndex[i][1]][2] };
		//	GLfloat c[3] = { Points[TriangleIndex[i][2]][0], Points[TriangleIndex[i][2]][1], Points[TriangleIndex[i][2]][2] };
		//	GLfloat norVector[3];
		//	triangle t = triangle(a, b, c);
		//	normalVector(t, norVector);
		//	glNormal3f(norVector[0], norVector[1], norVector[2]);
		//	glVertex3f(a[0], a[1], a[2]);
		//	glVertex3f(b[0], b[1], b[2]);
		//	glVertex3f(c[0], c[1], c[2]);
		//}
		//glEnd();
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < TriangleIndexNum; i++)
			{
				GLfloat a[3] = { Points[TriangleIndex[i][0]][0], Points[TriangleIndex[i][0]][1], Points[TriangleIndex[i][0]][2] };
				GLfloat b[3] = { Points[TriangleIndex[i][1]][0], Points[TriangleIndex[i][1]][1], Points[TriangleIndex[i][1]][2] };
				GLfloat c[3] = { Points[TriangleIndex[i][2]][0], Points[TriangleIndex[i][2]][1], Points[TriangleIndex[i][2]][2] };
				GLfloat norVector[3];
				triangle t = triangle(a, b, c);
				normalVector(t, norVector);
				glNormal3f(norVector[0], norVector[1], norVector[2]);
				glVertex3f(a[0], a[1], a[2]);
				glVertex3f(b[0], b[1], b[2]);
				glVertex3f(c[0], c[1], c[2]);
			}
			glEnd();

		GLint hits;
		GLint viewport[4];
		GLuint selectBuf[512] = { 0 };
		glGetIntegerv(GL_VIEWPORT, viewport);
		glSelectBuffer(512, selectBuf);
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(0);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(mouseX, viewport[3] - mouseY, 5, 5, viewport);
		glOrtho(-15.0, 15.0, -15.0, 15.0, -50.0, 50.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		for (int i = 0; i < 34834; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			GLfloat a[3] = { Points[i][0], Points[i][1], Points[i][2] };
			glVertex3f(a[0], a[1], a[2]);
			glEnd();
		}

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glFlush();
		glMatrixMode(GL_MODELVIEW);
		hits = glRenderMode(GL_RENDER);
		if (hits > 0) {

			glColor3f(1.0, 0, 0);
			glPointSize(5.0f);
			int selectedPoint=processHits(hits, selectBuf);

			
			glBegin(GL_POINTS);
			GLfloat a[3] = { Points[selectedPoint][0], Points[selectedPoint][1], Points[selectedPoint][2] };
			glVertex3f(a[0], a[1], a[2]);
			glEnd();





		}


		}
	
	}



}
void drawSelected(GLfloat** Points, int** TriangleIndex, int TriangleIndexNum, int selectedFace,GLfloat* color_selected)
{


	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glPointSize(100);
	glBegin(GL_POINTS);
	GLfloat a[3] = { Points[TriangleIndex[selectedFace][0]][0], Points[TriangleIndex[selectedFace][0]][1], Points[TriangleIndex[selectedFace][0]][2] };
	GLfloat b[3] = { Points[TriangleIndex[selectedFace][1]][0], Points[TriangleIndex[selectedFace][1]][1], Points[TriangleIndex[selectedFace][1]][2] };
	GLfloat c[3] = { Points[TriangleIndex[selectedFace][2]][0], Points[TriangleIndex[selectedFace][2]][1], Points[TriangleIndex[selectedFace][2]][2] };
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(a[0], a[1], a[2]);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(b[0], b[1], b[2]);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(c[0], c[1], c[2]);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);

	glEnd();
}
int processHits(GLint hits, GLuint selectBuf[])
{
	if (hits >= 1) {


		GLuint minz = selectBuf[1];
		GLuint selectedId = selectBuf[3];
		size_t i = 0;
		for (GLint n = 0; n < hits; ++n) {
			if (selectBuf[i] == 0) {
				printf("name: <None>\n");
				printf("min z: %u\n", selectBuf[i + 1]);
				printf("max z: %u\n", selectBuf[i + 2]);
				i += 3;
			}
			else {
				printf("name: ");
				for (GLuint m = i + 3; m < i + 3 + selectBuf[i]; ++m) {
					printf("%u ", selectBuf[m]);
				}
				printf("\n");
				printf("min z: %u\n", selectBuf[i + 1]);
				printf("max z: %u\n", selectBuf[i + 2]);
				if (selectBuf[i + 1] < minz) {
					minz = selectBuf[i + 1];
					selectedId = selectBuf[i + 3];
				}
				i += 3 + selectBuf[i];
			}
		}
		printf("selected id: %d\n", selectedId);
		return selectedId;

	}
	return 0;
}