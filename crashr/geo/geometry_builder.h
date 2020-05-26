#include "geo/mesh.h"
#include "geo/vertex.h"

namespace crashr {
void CreateBox(double dim1, double dim2, double dim3,
               std::vector<crashr::Vertex>& meshVertices,
               std::vector<std::array<int, 3>>& meshTriangles);

void CreateTrunCone(double topRadius, double bottomRadius, double height,
                    int resolution, std::vector<crashr::Vertex>& meshVertices,
                    std::vector<std::array<int, 3>>& meshTriangles);

void CreateHopper(double topRadius, double bottomRadius, double height,
                  std::vector<crashr::Vertex>& meshVertices,
                  std::vector<std::array<int, 3>>& meshTriangles);
}  // namespace crashr

