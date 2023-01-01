#include"include/Primitive.h"

namespace EssentialMath {
	void TriangleMesh::ComputeVertexNormals()
	{
		// Clear the triangle mesh vertices normal
		for (Vertex& vertex : mVertices) {
			vertex.Normal = Vector3::Zero;
		}

		for (Triangle& triangle : mTriangles) {
			for (uint8_t idx = 0; idx < 3; idx++) {
				mVertices[triangle.GetVertexIndex(idx)].Normal += triangle.GetNormal();
			}
		}
		
		// Average vertex normal
		for (Vertex& vertex : mVertices) {
			vertex.Normal = vertex.Normal.Normalize();
		}
	}
}
