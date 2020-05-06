#include "../demolish.h"
#include "../Mesh.h"
#include "../Vertex.h"

namespace demolish{
    void CreateBox(iREAL dim1, iREAL dim2, iREAL dim3,
                    std::vector<demolish::Vertex>&  meshVertices,
                    std::vector<std::array<int, 3>>& meshTriangles);

    void CreateTrunCone(iREAL topRadius, iREAL bottomRadius, iREAL height, int resolution,
                        std::vector<demolish::Vertex> &meshVertices,
                        std::vector<std::array<int, 3>>& meshTriangles);

    void CreateHopper(iREAL topRadius,
                                iREAL bottomRadius,
                                iREAL height,
                                std::vector<demolish::Vertex>    &meshVertices,
                                std::vector<std::array<int, 3>>  &meshTriangles);
}


