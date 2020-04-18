#include "Math.hpp"
#include "Service/SysCfgService.hpp"
#include "Service/MemoryService.hpp"
#include "TestUtility.hpp"
#include "Application/Application.hpp"

using namespace std;
using namespace LaughCrab;

int main(int argc, char **argv)
{
    //TestUtility::TestMain();
//    TestUtility::testMemoryService();
    //TestUtility::TestMD5();
    Application().Run(argv);
    return 0;
}
