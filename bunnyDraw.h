#ifndef bunnyDraw_
#define bunnyDraw_
enum drawMode { points, faces, select };
#include<GL/glut.h>
#include "triangle.h"
int processHits(GLint hits, GLuint selectBuf[]);
void drawBunny(GLfloat** Points, int** TriangleIndex,int PointsNum, int TriangleIndexNum,drawMode mode,GLdouble mouseX=0,GLdouble mouseY=0);





#endif // !bunnyDraw

