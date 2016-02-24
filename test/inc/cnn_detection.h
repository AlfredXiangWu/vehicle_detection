#ifndef _CNN_DETECTION_H
#define _CNN_DETECTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <opencv2\opencv.hpp>

#include "cnn.h"

using namespace std;
using namespace cv;


int fullconv_cnn_init(Net *cnn, const char* modelPath); 

int fullconv_multiscale_detect(const Mat img, multimap<float, Rect>  &bbox, Net *cnn, const int minSize, const int maxSize, const float scaleStep);

int fullconv_cnn_detect(const Mat img,  Net *cnn, const int stride, const float thr, const float sclae, multimap<float, Rect>  &bbox) ;

int bbox_nms(multimap<float, Rect> src, multimap<float, Rect> &dst, const float thr);

#endif