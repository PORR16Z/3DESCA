#pragma warning (disable : 4267)
#pragma warning (disable : 4930)

#include "TDES.hpp"
#include "Timer.hpp"
#include "MeasureCUDA.hpp"
#include "FileUtilities.hpp"

#include <vector>
#include <iostream>


namespace CUDA {

double measureEncode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath)
{
    std::vector<TDESCA::chunk64> inputChunks;
    std::vector<int> dataInSizes;
    TDESCA::TDES cipher;
    std::vector<TDESCA::chunk64> dataIn;
    Timer timer;

    // ENCODING
    dataIn = readFileIntoChunks(inPath);
    inputChunks.resize(dataIn.size());

    std::vector<uint64_t> outputChunks;
    outputChunks.reserve(inputChunks.size());

    timer.start();

    for (const auto& i : inputChunks)
        outputChunks.push_back(cipher.Encode(key1, key2, key3, i).val);

    std::vector<uint64_t> dataOut;
    dataOut.resize(dataIn.size());
    double resultNs = timer.stopNs();
    saveChunksIntoFile(outPath, dataOut);
    return resultNs;
}

double measureDecode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath)
{
    std::vector<TDESCA::chunk64> inputChunks;
    TDESCA::TDES cipher;
    std::vector<TDESCA::chunk64> dataIn;
    Timer timer;

    // DECODING
    dataIn = readFileIntoChunks(inPath);
    inputChunks.resize(dataIn.size());

    std::vector<uint64_t> outputChunks;
    outputChunks.reserve(inputChunks.size());

    timer.start();

    for (const auto& i : inputChunks)
        outputChunks.push_back(cipher.Decode(key1, key2, key3, i).val);

    std::vector<uint64_t> dataOut;
    dataOut.resize(dataIn.size());

    double resultNs = timer.stopNs();
    saveChunksIntoFile(outPath, dataOut);
    return resultNs;

    return 0;
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