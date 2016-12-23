#pragma once

#include "Bit.hpp"

namespace MPI {

double measureEncode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath);
double measureDecode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath);

std::pair<double, double> measure(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3);
} // namespace MPI