#include "DES.hpp"
#include "Bit.hpp"
#include "Timer.hpp"
#include "FileUtilities.hpp"
#include "MeasureMPI.hpp"
#include "MeasureLocal.hpp"
#include <vector>
#include <iostream>


const TDESCA::chunk64 key(0x0123456789ABCDEF);
const unsigned int repeatTimes = 5;

int main()
{
    std::string path = ExePath() + "\\..\\..\\..\\";
    std::pair<double, double> result;
    /*
    // MPI
    result = MPI::measure(key, key, key, repeatTimes);
    if (result.first > 0)
    {
        std::cout << "REPEATED " << repeatTimes << " TIMES" << std::endl;
        std::cout << "Encode: [Total]" << result.first / 1000000 << "ms | [Single]" << result.first / 1000000 / repeatTimes << "ms" << std::endl;
        std::cout << "Decode: [Total]" << result.second / 1000000 << "ms | [Single]" << result.second / 1000000 / repeatTimes << "ms" << std::endl;
    }
    */
    
    // LOCAL
    result = Local::measure(key, key, key, repeatTimes);
    std::cout << "REPEATED " << repeatTimes << " TIMES" << std::endl;
    std::cout << "Encode: [Total]" << result.first / 1000000 << "ms | [Single]" << result.first / 1000000 / repeatTimes << "ms" << std::endl;
    std::cout << "Decode: [Total]" << result.second / 1000000 << "ms | [Single]" << result.second / 1000000 / repeatTimes << "ms" << std::endl;
    
    return 0;
}