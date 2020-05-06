#ifndef MATERIAL
#define MATERIAL

#include "crashr.h"

#include <map>

namespace crashr {
namespace material {
enum class MaterialType : int { GOLD = 1, GRAPHITE = 2, WOOD = 3 };

enum class MaterialInteraction : char {
    WOODWOOD,
    GOLDGOLD,
    GRAPHITEGRAPHITE,
    WOODGOLD,
    GRAPHITEWOOD,
    GRAPHITEGOLD
};

static std::map<crashr::material::MaterialType, double> materialToDensitymap(
    {{crashr::material::MaterialType::WOOD, 20000},
     {crashr::material::MaterialType::GRAPHITE, 1000},
     {crashr::material::MaterialType::GOLD, 1000}});

int getInterfaceType(int materialA, int materialB);

extern void materialInit();
int getCollisionInterface();
}  // namespace material
}  // namespace crashr

#endif
