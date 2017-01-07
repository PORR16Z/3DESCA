#include "DES.hpp"
#include "Bit.hpp"
#include "Timer.hpp"
#include "FileUtilities.hpp"
#include "MeasureOMP.hpp"
#include <vector>
#include <iostream>

const TDESCA::chunk64 key(0x0123456789ABCDEF);

int main(int argc, char** argv)
{
	std::string path = ExePath() + "\\..\\..\\..\\lorem.txt";
	unsigned int threadsNumber = 1;
	unsigned int repeatTimes = 1000;
	if (argc > 1) threadsNumber = strtol(argv[1], NULL, 10);
	if (argc > 2) path = std::string(argv[2]);
	if (argc > 3) repeatTimes = strtol(argv[3], NULL, 10);

	std::pair<double, double> result;

	result = OMP::measure(key, key, key, path, threadsNumber, repeatTimes);
	std::cout << "REPEATED " << repeatTimes << " TIMES" << std::endl;
	std::cout << "Encode: [Total]" << result.first / 1000000 << "ms | [Single]" << result.first / 1000000 / repeatTimes << "ms" << std::endl;
	std::cout << "Decode: [Total]" << result.second / 1000000 << "ms | [Single]" << result.second / 1000000 / repeatTimes << "ms" << std::endl;

	return 0;
}