#ifndef MATERIAL
#define MATERIAL

#include "demolish.h"

#include <map>

namespace demolish {
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

static std::map<demolish::material::MaterialType, iREAL> materialToDensitymap(
    {{demolish::material::MaterialType::WOOD, 20000},
     {demolish::material::MaterialType::GRAPHITE, 1000},
     {demolish::material::MaterialType::GOLD, 1000}});

int getInterfaceType(int materialA, int materialB);

extern void materialInit();
int getCollisionInterface();
}  // namespace material
}  // namespace demolish

#endif
