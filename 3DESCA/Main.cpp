#include "DES.hpp"
#include "Bit.hpp"
#include "Timer.hpp"
#include "FileUtilities.hpp"
#include "MpiRun.hpp"
#include <vector>
#include <iostream>


const TDESCA::chunk64 key(0x0123456789ABCDEF);

int main()
{
    std::string path = ExePath() + "\\..\\..\\..\\";
    std::pair<double, double> result = MPI::measure(key, key, key);
    std::cout << "Encode:" << result.first << std::endl << "Decode:" << result.second << std::endl;
    /*
    {
        std::vector<TDESCA::chunk64> dataIn = readFileIntoChunks(path + "lorem.txt");

        std::vector<uint64_t> dataOut;
        dataOut.reserve(dataIn.size());
        TDESCA::DES cipher;

        std::cout << "Encode execution: " << measureExecution([&](){
            for (const auto i : dataIn)
            {
                dataOut.push_back(cipher.Encode(key, i).val);
            }
        })/1000 << " ms" << std::endl;
        saveChunksIntoFile(path + "lorem2.txt", dataOut);
    }
    {
        std::vector<TDESCA::chunk64> dataIn = readFileIntoChunks(path + "lorem2.txt");

        std::vector<uint64_t> dataOut;
        dataOut.reserve(dataIn.size());
        TDESCA::DES cipher;

        std::cout << "Decode execution: " << measureExecution([&](){
            for (const auto i : dataIn)
            {
                dataOut.push_back(cipher.Decode(key, i).val);
            }
        })/1000 << " ms" << std::endl;

        saveChunksIntoFile(path + "lorem3.txt", dataOut);
    } */
    return 0;
}