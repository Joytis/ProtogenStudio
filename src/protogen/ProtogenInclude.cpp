
#define RAPIDJSON_HAS_STDSTRING 1

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

// std lib
#include <filesystem>
#include <fstream>
#include <algorithm>

// Aaaaand the rest of everything. 
#include "Common.h"

#include "Grid.h"

#include "Protogen.h"
#include "Protogen.cpp"

#include "Utils.h"
#include "Utils.cpp"

#include "Vector4.h"