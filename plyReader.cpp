#include"plyReader.h"
void plyRead(std::string path, GLfloat** Points, int** TriangleIndex, int* num)
{

	GLfloat none;
	int pointsNum, trianglesNum;
	ifstream is;
	is.open(path, ios::in);
	is >> pointsNum;
	int fixedPointsNum = pointsNum;

	is >> trianglesNum;
	int fixedTrianglesNum = trianglesNum;
	*num = trianglesNum;

	while (pointsNum)
	{
		is >> Points[fixedPointsNum - pointsNum][0];
		is >> Points[fixedPointsNum - pointsNum][1];
		is >> Points[fixedPointsNum - pointsNum][2];
		pointsNum--;
	}
	while (trianglesNum)
	{
		is >> none;
		is >> TriangleIndex[fixedTrianglesNum - trianglesNum][0];
		is >> TriangleIndex[fixedTrianglesNum - trianglesNum][1];
		is >> TriangleIndex[fixedTrianglesNum - trianglesNum][2];
		trianglesNum--;
	}

	is.close();

}