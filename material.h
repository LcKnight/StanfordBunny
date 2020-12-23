#ifndef material_
#define material_
#include<GL/glut.h>
struct material
{
	GLfloat specular[4];
	GLfloat diffuse[4];
	GLfloat ambient[4];
	GLfloat shiness;
	material(GLfloat* specular_, GLfloat* diffuse_, GLfloat* ambient_, GLfloat shiness_) :shiness(shiness_)
	{
		for (int i = 0; i < 4; i++)
		{
			specular[i] = specular_[i];
			diffuse[i] = diffuse_[i];
			ambient[i] = ambient_[i];

		}
	}
};








#endif
