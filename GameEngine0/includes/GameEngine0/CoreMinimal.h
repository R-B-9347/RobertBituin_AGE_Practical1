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


class Texture;
typedef shared_ptr<Texture>TexturePtr;
typedef vector<TexturePtr>TexturePtrStack;

class Mesh;
typedef shared_ptr<Mesh> MeshPtr;
typedef vector<MeshPtr>MeshPtrStack;

class Model;
typedef shared_ptr<Model>ModelPtr;
typedef vector<ModelPtr>ModelPtrStack;

class Material;
typedef shared_ptr<Material>MaterialPtr;
typedef vector<MaterialPtr>MaterialPtrStack;

class Camera;
typedef shared_ptr<Camera>CameraPtr;

class Collision;
typedef shared_ptr<Collision>CollisionPtr;
typedef vector<CollisionPtr>CollisionPtrStack;

class BoxCollision;
typedef shared_ptr<BoxCollision>BoxCollisionPtr;

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
	Free,
	Cube
};

struct VFShaderParams {
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

enum class ShaderTypes {
	Vertex = 0,
	Fragment
};
