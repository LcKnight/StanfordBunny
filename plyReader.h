
//本函数为了将.ply2中文件读取 读出点集 读出片元的点集索引
//从0开始索引
#ifndef plyReader_
#define plyReader_

#include<gl/glut.h>
#include<fstream>
#include<string>
using namespace std;

void plyRead(std::string path, GLfloat** Points, int** TriangleIndex, int* num);





#endif // plyReader
