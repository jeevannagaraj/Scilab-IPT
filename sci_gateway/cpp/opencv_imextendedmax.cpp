/********************************************************
Author: Vinay Bhat
********************************************************
Usage: return_image = imextendedmax(input_image, h)
Example:
  im = imextendedmax(image, 80)
********************************************************/

#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
extern "C"
{
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include "sciprint.h"
  #include "../common.h"

  void imextendedmax_imreconstruct(Mat, Mat, Mat&);

  int opencv_imextendedmax(char *fname, unsigned long fname_len)
  {

    SciErr sciErr;
    int intErr = 0;
    int *piAddr = NULL;
    double h;

    //checking input argument
    CheckInputArgument(pvApiCtx, 2, 2);
    CheckOutputArgument(pvApiCtx, 1, 1) ;

    // Get the input image from the Scilab environment
    Mat image;
    retrieveImage(image, 1);

    // Get the address of 2nd argument, the H-Maxima transform scalar
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    // Get the H-Maxima transform scalar
    intErr = getScalarDouble(pvApiCtx, piAddr, &h);
    if(intErr)
    {
        return intErr;
    }   

    if (h < 0)
    {
        sciprint("Please enter a nonnegative scalar for H-maxima transform.\n");
        return 0;
    }
    
    Mat gray_image, dst, fin_image, m, m2;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    max((gray_image-h), 0, m);
    imextendedmax_imreconstruct(gray_image, m, dst);
    subtract(dst, 1, m2);
    imextendedmax_imreconstruct(dst, m2, m);
    subtract(dst, m, m2);
    fin_image = m2 * 255;

    string tempstring = type2str(fin_image.type());
    char *checker;
    checker = (char *)malloc(tempstring.size() + 1);
    memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
    returnImage(checker, fin_image, 1);
    free(checker);

    //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx);
    return 0;

  }
  void imextendedmax_imreconstruct(Mat g, Mat f, Mat& dest)
  {
    Mat m0, m1, m;
    m1 = f;
    do {
      m0 = m1.clone();
      dilate(m0, m, Mat());
      min(g, m, m1);
    } while(countNonZero(m1 != m0) != 0);
    dest = m1.clone();
  }
/* ==================================================================== */
}
