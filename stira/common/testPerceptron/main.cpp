#include <iostream>
#include "../common/Perceptron.h"
#include "../common/TextFileUtils.h"
using namespace std;
using namespace stira::common;

int main()
{
    std::vector<ClassSample> samples = TextFileUtils::ReadDataSamplesFromTextFile( std::string("../../testdata/IrisDataset.txt"), 0, 1 );

    cout << "Hello World!" << endl;
    return 0;
}

