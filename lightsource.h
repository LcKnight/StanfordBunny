#ifndef lightsource_
#define lightsource_
#include<GL/glut.h>


struct lightsource
{
	GLfloat position[4];
	GLfloat specular[4];
	GLfloat diffuse[4];
	GLfloat ambient[4];
	lightsource(GLfloat* position_, GLfloat* specular_, GLfloat* diffuse_, GLfloat* ambient_) {
		for (int i = 0; i < 4; i++)
		{
			position[i] = position_[i];
			specular[i] = specular_[i];
			diffuse[i] = diffuse_[i];
			ambient[i] = ambient_[i];

		}
	}
};









#endif
