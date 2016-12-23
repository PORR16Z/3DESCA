#pragma warning (disable : 4267)
#pragma warning (disable : 4930)

#include "TDES.hpp"
#include "Timer.hpp"
#include "MpiRun.hpp"
#include "FileUtilities.hpp"

#include <vector>
#include <iostream>

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {
template<class Archive>
void serialize(Archive& ar, TDESCA::chunk64& chunk, const unsigned int version)
{
    ar & chunk.val;
}
} // namespace boost::serialization

namespace mpi {

template<> struct is_mpi_datatype<TDESCA::chunk64> : public mpl::true_ {};
} // namespace boost::mpi
} // namespace boost

namespace MPI {

boost::mpi::environment env;
boost::mpi::communicator world;


double measureEncode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath)
{
    TDESCA::TDES cipher;
    std::vector<TDESCA::chunk64> dataIn;
    Timer timer;

    // ENCODING
   // std::cout << "3";
    if (world.rank() == 0)
        dataIn = readFileIntoChunks(inPath);

    TDESCA::chunk64 inputChunk;
    //std::cout << "4";
    boost::mpi::scatter(world, dataIn, inputChunk, 0);
    //std::cout << "5";
    if (world.rank() == 0)
        timer.start();
    uint64_t outputChunk = cipher.Encode(key1, key2, key3, inputChunk).val;

    if (world.rank() == 0) {
        std::vector<uint64_t> dataOut;
        dataOut.reserve(dataIn.size());
        boost::mpi::gather(world, outputChunk, dataOut, 0);
        double resultNs = timer.stopNs() / 1000;
        saveChunksIntoFile(outPath, dataOut);
        return resultNs;
    }
    boost::mpi::gather(world, outputChunk, 0);
    return 0;
}

double measureDecode(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3, const std::string& inPath, const std::string& outPath)
{
    //boost::mpi::environment env();
    //boost::mpi::communicator world;
    TDESCA::TDES cipher;
    std::vector<TDESCA::chunk64> dataIn;
    Timer timer;

    // ENCODING
    if (world.rank() == 0)
        dataIn = readFileIntoChunks(inPath);

    TDESCA::chunk64 inputChunk;
    boost::mpi::scatter(world, dataIn, inputChunk, 0);

    if (world.rank() == 0)
        timer.start();
    uint64_t outputChunk = cipher.Decode(key1, key2, key3, inputChunk).val;

    if (world.rank() == 0) {
        std::vector<uint64_t> dataOut;
        dataOut.reserve(dataIn.size());
        boost::mpi::gather(world, outputChunk, dataOut, 0);
        double resultNs = timer.stopNs() / 1000;
        saveChunksIntoFile(outPath, dataOut);
        return resultNs;
    }
    boost::mpi::gather(world, outputChunk, 0);
    return 0;
}

std::pair<double, double> measure(TDESCA::chunk64 key1, TDESCA::chunk64 key2, TDESCA::chunk64 key3)
{
    std::string path = ExePath() + "\\..\\..\\..\\";
    std::string inPath = path + "lorem.txt";
    std::string encPath = path + "lorem2.txt";
    std::string decPath = path + "lorem3.txt";
    std::pair<double, double> resultNs, blank;

    resultNs.first = measureEncode(key1, key2, key3, inPath, encPath);
    resultNs.second = measureDecode(key1, key2, key3, encPath, decPath);

    if (world.rank() == 0)
        return resultNs;
    return blank;
}

} // namespace MPI