#ifndef GEOMETRYGENERATOR_H
#define GEOMETRYGENERATOR_H
#include "antmath.h"
#include "../demolish.h"
#include "../Mesh.h"
#include "../Vertex.h"
#include "../math.h"

typedef unsigned int UINT;

class GeometryGenerator
{
public:
	struct Vertex
	{

	    AV3FLOAT Position;
		AV3FLOAT Normal;
		AV3FLOAT TangentU;
		AV2FLOAT TexC;
		Vertex(){}
		Vertex(const AV3FLOAT& p, const AV3FLOAT& n, const AV3FLOAT& t, const AV2FLOAT& uv)
			: Position(p), Normal(n), TangentU(t), TexC(uv){}
		Vertex(
			float px, float py, float pz, 
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v)
			: Position(px,py,pz), Normal(nx,ny,nz),
			  TangentU(tx, ty, tz), TexC(u,v){}


	};

	struct MeshData
	{
		std::vector<Vertex> Vertices;
		std::vector<UINT> Indices;
	};


	void CreateBox(float width, float height, float depth, MeshData& meshData);


	void CreateSphere(float radius,
                      UINT sliceCount,
                      UINT stackCount,
                      MeshData& meshData,
                      std::array<iREAL,3> position);


	void CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshData);

    void CreateMeshFromMesh(demolish::Mesh* mesh,MeshData& meshData);
};

#endif 
