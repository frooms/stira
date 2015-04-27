#include <iostream>
#include <time.h>
#include "../bregman/FlashROF.h"
#include "Example.h"
#include "../../image/datastructures/Image.h"
#include "../../image/tools/ImageIO.h"

using namespace std;
using namespace stira;
using namespace stira::image;

int main(int argc, char** argv)
{
   string fileNamePGM;
   if (argc != 2)
   {
      fileNamePGM = string("../../testdata/lena256-GaussianNoise.pgm");
      //fileNamePGM = string("../../testdata/bricks_zigzag_texture_6190218.PGM");
   }
   else
   {
      fileNamePGM = string(argv[1]);
   }
   
   cout << "Proceeding with tests with " << fileNamePGM << " as input image." << endl << flush;
   
   Image* pImage = 0;
   
   pImage = ImageIO::Read( fileNamePGM );
  
   FlashROF frof;
   Image* pResult = frof.Run( pImage );
   
   ImageIO::Write( pResult, std::string("BregmanDenoised.pgm") );
   
   delete pImage;
   delete pResult;
   
   return 0;
}
