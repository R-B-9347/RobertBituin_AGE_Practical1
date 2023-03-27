#include "GameEngine0/Graphics/VertexArrayObject.h"
#include "GL/glew.h"

VertexArrayObject::VertexArrayObject(GeometricShapes ChosenShape)
{
	ID = EAB = VAB = 0;

	PositionMatrix ChosenPosition = PositionMatrix();
	IndexMatrix ChosenIndex = IndexMatrix();

	switch (ChosenShape) {
	case GeometricShapes::Triangle :
		ChosenPosition = TrianglePositions;
		ChosenIndex = TriangleIndex;
		break;
	case GeometricShapes::Polygon:
		ChosenPosition = PolyPositions;
		ChosenIndex = PolyIndex;
		break;
	case GeometricShapes::Circle:
		ChosenPosition = CiclePositions;
		ChosenIndex = CircleIndex;
		break;
	case GeometricShapes::Free:
		ChosenPosition = FreePositions;
		ChosenIndex = FreeIndex;
		break;
	case GeometricShapes::Cube:
		ChosenPosition = CubePositions;
		ChosenIndex = CubeIndicies;
		break;

	default:
		break;
	}

	Shape.PositionMatrix = ChosenPosition;
	Shape.IndexMatrix = ChosenIndex;

	//Positions
	glGenVertexArrays(1, &ID);

	glBindVertexArray(ID);

	glGenBuffers(1, &VAB);
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	glBufferData(GL_ARRAY_BUFFER, Shape.PositionMatrix.size() * sizeof(float),&Shape.PositionMatrix[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Shape.IndexMatrix.size() * sizeof(GE0uint), &Shape.IndexMatrix[0], GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,    //first data set
		3,    //how many number in matrix to make triangle
		GL_FLOAT,GL_FALSE,
		sizeof(float) * 8,
		(void*)0
	);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(3 * sizeof(float))
	);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(6 * sizeof(float))
	);

	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &ID);

	Shape.PositionMatrix.clear();
	Shape.IndexMatrix.clear();

	cout << "Deleted VAO." << endl;
}

void VertexArrayObject::Draw()
{
	glBindVertexArray(ID);

	glDrawElements(GL_TRIANGLES, Shape.IndexMatrix.size(),GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);

}
