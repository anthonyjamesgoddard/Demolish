#ifndef DEMOLISH_IO_INPUT
#define DEMOLISH_IO_INPUT


#include <string>
#include <iostream>
#include <vector>

#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "math.h"

#include "../Mesh.h"

namespace demolish{
    namespace input{
        demolish::Mesh* readGeometry(char* fileName);
    }
}

#endif
