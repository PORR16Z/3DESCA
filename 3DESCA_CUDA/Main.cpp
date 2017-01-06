#include "DES.hpp"
#include "Bit.hpp"
#include "Timer.hpp"
#include "FileUtilities.hpp"
#include "MeasureCUDA.hpp"
#include <vector>
#include <iostream>


const TDESCA::chunk64 key(0x0123456789ABCDEF);

int main(int argc, char** argv)
{
    std::string path = ExePath() + "\\..\\..\\..\\lorem.txt";
    unsigned int repeatTimes = 1000;
    if (argc > 1) path = std::string(argv[1]);
    if (argc > 2) repeatTimes = strtol(argv[2], NULL, 10);

    std::pair<double, double> result;

    result = CUDA::measure(key, key, key, path, repeatTimes);
    if (result.first > 0)
    {
        std::cout << "REPEATED " << repeatTimes << " TIMES" << std::endl;
        std::cout << "Encode: [Total]" << result.first / 1000000 << "ms | [Single]" << result.first / 1000000 / repeatTimes << "ms" << std::endl;
        std::cout << "Decode: [Total]" << result.second / 1000000 << "ms | [Single]" << result.second / 1000000 / repeatTimes << "ms" << std::endl;
    }

    return 0;
}