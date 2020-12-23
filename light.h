#ifndef lightinit_
#define lightinit_

#include"material.h"
#include"lightsource.h"


void lightInit(material m,lightsource ls)
{
	//设置灯光 这里只设置了一个光源
	glEnable(GL_NORMALIZE);
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, ls.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ls.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ls.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, ls.position);



	//设置物体材质
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.shiness);





	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	//glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0);  /* enable light 0 */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */

}





#endif // !lightinit_
