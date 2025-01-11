#include "test.h"
#include "io.h"

int main()
{
    std::string outputPath = std::string(OUTPUT_PATH);

    // test 1
    std::vector<Surface> surfaces = fourSideHole();
    std::string filename1 = outputPath + "/foursideHole_3.obj";
    IO::writeObj(filename1, surfaces, 2, 2);

    return 0;
}