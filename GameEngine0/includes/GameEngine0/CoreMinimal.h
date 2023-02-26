#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int GE0uint;

class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GEptr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO>VAOptr;
typedef vector<VAOptr>VAOStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram>Shaderptr;

typedef vector<float> PositionMatrix;
typedef vector<GE0uint>IndexMatrix;

struct ShapeData {
	vector<float>PositionMatrix;
	vector<GE0uint>IndexMatrix;
};
enum class GeometricShapes {
	Triangle = 0,
	Polygon,
	Circle,
	Free
};

struct VFShaderParams {
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

enum class ShaderTypes {
	Vertex = 0,
	Fragment
};
