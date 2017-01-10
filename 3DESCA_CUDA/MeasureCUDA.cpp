#pragma warning (disable : 4267)
#pragma warning (disable : 4930)

#include "TDES.hpp"
#include "Timer.hpp"
#include "MeasureCUDA.hpp"
#include "FileUtilities.hpp"
#include "Kernel.cuh"

#include <vector>
#include <iostream>


namespace CUDA {

double measureEncode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath)
{
    std::vector<TDESCA::chunk64> inputChunks;
    std::vector<int> dataInSizes;

    // ENCODING
    inputChunks = readFileIntoChunks(inPath);

    // input data must be a multiple of thread count per block
    // which we assume to be 256
    size_t originalSize = inputChunks.size();
    if (originalSize % 256 != 0)
    {
        size_t missingSize = 256 - originalSize % 256;
        inputChunks.resize(originalSize + missingSize);
    }

    std::vector<TDESCA::chunk64> outputChunks;
    outputChunks.resize(inputChunks.size());

    double resultNs;
    CudaEncode(key1, key2, key3, inputChunks.data(), inputChunks.size(), outputChunks.data(), &resultNs);

    // revert output to original size
    outputChunks.resize(originalSize);
    saveChunksIntoFile(outPath, outputChunks);
    return resultNs;
}

double measureDecode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath)
{
    std::vector<TDESCA::chunk64> inputChunks;

    // DECODING
    inputChunks = readFileIntoChunks(inPath);

    // input data must be a multiple of thread count per block
    // which we assume to be 256
    size_t originalSize = inputChunks.size();
    if (originalSize % 256 != 0)
    {
        size_t missingSize = 256 - originalSize % 256;
        inputChunks.resize(originalSize + missingSize);
    }

    std::vector<TDESCA::chunk64> outputChunks;
    outputChunks.resize(inputChunks.size());

    double resultNs;
    CudaDecode(key1, key2, key3, inputChunks.data(), inputChunks.size(), outputChunks.data(), &resultNs);

    outputChunks.resize(originalSize);
    saveChunksIntoFile(outPath, outputChunks);
    return resultNs;
}

std::pair<double, double> measure(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, std::string inPath, unsigned int repeatTimes)
{
    std::string encPath = inPath + ".enc";
    std::string decPath = encPath + ".dec";
    std::pair<double, double> resultNs{0.0, 0.0}, blank;
    double temp1, temp2;

    for (unsigned int i = 0; i < repeatTimes; i++)
    {
        temp1 = measureEncode(key1, key2, key3, inPath, encPath);
        temp2 = measureDecode(key1, key2, key3, encPath, decPath);

        resultNs.first += temp1;
        resultNs.second += temp2;
    }

    return resultNs;
}

} // namespace MPI