#ifndef DEMOLISH_IO_INPUT
#define DEMOLISH_IO_INPUT

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "math.h"

#include "../Mesh.h"

namespace demolish {
namespace input {
demolish::Mesh* readGeometry(char* fileName);
}
}  // namespace demolish

#endif
