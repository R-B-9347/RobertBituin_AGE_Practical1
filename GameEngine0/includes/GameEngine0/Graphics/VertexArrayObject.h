#pragma once
#include "GameEngine0/CoreMinimal.h"

const PositionMatrix TrianglePositions{
	// x	// y	// z
	-0.5f,	-0.5f,	0.0f,	1.0f,0.0f,0.0f,	//bottom left
	 0.5f,  -0.5f,  0.0f,	0.0f,1.0f,0.0f,	//bottom right
	 0.0f,   0.5f,  0.0f,	0.0f,0.0f,1.0f	// top
};
const IndexMatrix TriangleIndex{
	0,1,2
};

const PositionMatrix PolyPositions{
	// x	// y	// z		//colour
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//bottom left 0
	 0.5f,  -0.5f,  0.0f,	1.0f, 1.0f, 0.0f,	//bottom right 1
	 0.5f,   0.5f,  0.0f,	1.0f, 1.0f, 0.0f,  //top right 2
	-0.5f,   0.5f,  0.0f,	1.0f, 1.0f, 0.0f	//Top left 3
};
const IndexMatrix PolyIndex{
	0,3,1, //triangle 1
	3,2,1  //Triangle 2
};

const PositionMatrix CiclePositions{
	// x	// y	// z
	 0.0f,	 0.0f,	0.0f,	0.0f,1.0f,0.0f,//Cebter 0
	 0.2f,  -0.5f,  0.0f,   0.0f,1.0f,0.0f,//bottom right 1
	-0.2f,  -0.5f,  0.0f,	0.0f,1.0f,0.0f,// bottom left 2
    -0.3f,   0.1f,  0.0f,	0.0f,1.0f,0.0f,//3
	 0.0f,	 0.0f,	0.0f,	0.0f,1.0f,0.0f,//4
	 0.2f,   0.5f,  0.0f,	0.0f,1.0f,0.0f,//5
	 0.3f,  -0.2f,  0.0f,	0.0f,1.0f,0.0f,// 6
    -0.2f,   0.5f,  0.0f,	0.0f,1.0f,0.0f,//Top left 7
     0.2f,   0.5f,  0.0f,	0.0f,1.0f,0.0f//Top right 8
};
const IndexMatrix CircleIndex{
	0,7,8, 
	0,2,1,  
	0,2,3,
	0,3,4,
	0,5,6,
	0,8,7,
	0,6,1,
	0,7,3

};

const PositionMatrix FreePositions{
	// x	// y	// z
	-0.10f,	-0.5f,	0.0f, //bottom left 0
	 0.5f,  -0.5f,  0.0f, //bottom right 1
	 0.0f,   0.5f,  0.0f, // top right 2
	-0.5f,   0.5f,  0.0f  //Top left 3
};
const IndexMatrix FreeIndex{
	0,1,3, //triangle 1
	0,2,1  //Triangle 2
};

class VertexArrayObject {
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	~VertexArrayObject();

	void Draw();
private:
	ShapeData Shape;
	//ID - VAO
	//VAB - Vertices
	//EAB - Indicies
	GE0uint ID, VAB, EAB;
};