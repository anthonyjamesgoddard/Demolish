#include "../demolish.h"
#include "../Mesh.h"
#include "../Vertex.h"

namespace demolish{
    void CreateBox(iREAL dim1, iREAL dim2, iREAL dim3,
                    std::vector<demolish::Vertex>&  meshVertices,
                    std::vector<std::array<int, 3>>& meshTriangles);
}


