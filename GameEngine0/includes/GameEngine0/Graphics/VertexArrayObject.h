#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Graphics/Vertex.h"
const PositionMatrix TrianglePositions{
	// x	// y	// z
	-0.5f,	-0.5f,	0.0f,	1.0f,0.0f,0.0f,		0.0f,0.0f,//bottom left
	 0.5f,  -0.5f,  0.0f,	0.0f,1.0f,0.0f,		1.0f,0.0f,//bottom right
	 0.0f,   0.5f,  0.0f,	0.0f,0.0f,1.0f,		0.5f,1.0f// top
};
const IndexMatrix TriangleIndex{
	0,1,2
};

const PositionMatrix PolyPositions{
	// x	// y	// z		//colour
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	0.0f,0.0f,	//bottom left 0
	 0.5f,  -0.5f,  0.0f,	1.0f, 1.0f, 0.0f, 	1.0f,0.0f,//bottom right 1
	 0.5f,   0.5f,  0.0f,	1.0f, 1.0f, 0.0f,	1.0f,1.0f,//top right 2
	-0.5f,   0.5f,  0.0f,	1.0f, 1.0f, 0.0f,	0.0f,1.0f //Top left 3
};
const IndexMatrix PolyIndex{
	0,3,1, //triangle 1
	3,2,1  //Triangle 2
};

const PositionMatrix CiclePositions{
	// x	// y	// z
	 0.0f,	 0.0f,	0.0f,	0.0f,1.0f,0.0f,		0.0f,0.0f,//Cebter 0
	 0.2f,  -0.5f,  0.0f,   0.0f,1.0f,0.0f,		0.0f,0.0f,//bottom right 1
	-0.2f,  -0.5f,  0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,// bottom left 2
    -0.3f,   0.1f,  0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,//3
	 0.0f,	 0.0f,	0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,//4
	 0.2f,   0.5f,  0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,//5
	 0.3f,  -0.2f,  0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,// 6
    -0.2f,   0.5f,  0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,//Top left 7
     0.2f,   0.5f,  0.0f,	0.0f,1.0f,0.0f, 	0.0f,0.0f,//Top right 8
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

const PositionMatrix CubePositions{
	// x	// y	// z	// r	// g	// b	// tex coords
	-0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// back - bot - left	0
	 0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// back - bot - right	1
	 0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// back - top - right	2
	-0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// back - top - left	3
	-0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// front - top - left	4
	 0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// front - top - right	5
	 0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// front - bot - right	6
	-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// front - bot - left	7
	-0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// left - top - right	8
	-0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// left - top - left	9
	-0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// left - bot - left	10
	-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// left - bot - right	11
	 0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// right - top - right	12
	 0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// right - top - left	13
	 0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// right - bot - left	14
	 0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// right - bot - right	15
	-0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// top - bot - left		16
	 0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// top - bot - right	17
	 0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// top - top - right	18
	-0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// top - top - left		19
	-0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// bot - top - left		20
	 0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// bot - top - right	21
	 0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// bot - bot - right	22
	-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// bot - bot - left		23
};

const IndexMatrix CubeIndicies{
	0,	1,	2,	// front tri 1
	2,	3,	0,	// front tri 2
	12, 13, 15,	// right tri 1
	15,14,  13,	// right tri 2
	8,	9,	10,	// left tri 1
	10,	11,	8,	// left tri 2
	20,	21,	22,	// bot tri 1
	22,	23,	20,	// bot tri 2
	16,	17,	18,	// top tri 1
	18,	19,	16,	// top tri 2
	4,	5,	6,	// back tri 1
	6,	7,	4	// back tri 2
};


class VertexArrayObject {
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	VertexArrayObject(vector<Vertex> Verticies, vector<GE0uint> Indicies);
	~VertexArrayObject();

	void Draw();
private:
	ShapeData Shape;
	//ID - VAO
	//VAB - Vertices
	//EAB - Indicies
	GE0uint ID, VAB, EAB;

	vector<Vertex> Verticies;
	vector<GE0uint> Indicies;
};