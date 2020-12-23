#ifndef  triangle_
#define triangle_
#include<GL/glut.h>

struct triangle
{
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	triangle(GLfloat* a_, GLfloat* b_, GLfloat* c_)
	{
		for (int i = 0; i < 3; i++)
		{
			a[i] = a_[i];
			b[i] = b_[i];
			c[i] = c_[i];
		}
	}
	
};



#endif // ! triangle_
