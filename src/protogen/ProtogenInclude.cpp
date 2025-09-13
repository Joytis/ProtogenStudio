
#define RAPIDJSON_HAS_STDSTRING 1

// std lib
#include <filesystem>
#include <fstream>
#include <algorithm>

// rapidjson
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/error.h" 
#include "rapidjson/error/en.h"

// lodepng 
#include "lodepng.h"
#include "lodepng.cpp"

// Tracy
#include "tracy/Tracy.hpp"
#include "TracyClient.cpp"

// Include some tracy math
#include "tracy_math/Maths.h"
#include "tracy_math/MathSimd.h"
#include "tracy_math/Maths.cpp"

// Aaaaand the rest of everything. 
#include "Common.h"
#include "ProtogenMath.h"
#include "Enums.cpp"

#include "Utils.h"
#include "Utils.cpp"

#include "Grid.h"

#include "Protogen.h"

#include "Protogen.cpp"
