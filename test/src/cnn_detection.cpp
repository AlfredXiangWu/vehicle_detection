#include "cnn_detection.h"


int fullconv_cnn_init(Net *cnn, const char* modelPath) {

	if(cnn->LoadFromFile(modelPath)) {
		cout << "Load model error!" << endl;
		return -1;
	}

	return 0;
}

/*int fullconv_multiscale_detect(const Mat img, vector<Rect> &bbox, Net *cnn, const int minSize, const int maxSize, const float scaleStep){
	
	// Convert RGB image to gray-scale
	Mat imgGray;

	if(imgGray.channels() != 1)
		cvtColor(img, imgGray, CV_BGR2GRAY); 
	else
		imgGray = img;


	// detection parameters
	const float windowSize = 64;
	float minScale = windowSize / maxSize;
	float maxScale = windowSize / minSize;
	
	// Multi-scale detect
	Mat imgResize;
	for(float scale  = minScale; scale <= maxScale; scale = scale*scaleStep) {
		resize(imgGray, imgResize, Size(imgGray.rows*scale, imgGray.cols*scale));
	}

	return 0;
}*/

int fullconv_cnn_detect(const Mat img,  Net *cnn) {

	// convert pixel from [0, 255] to [0, 1]
	int width = img.rows;
	int height = img.cols;
	int channel = img.channels();
	if(width != 640 && height != 480 && channel != 1)
		return -1;
	float* data = (float*)malloc(width*height*sizeof(float));
	for(int i = 0; i < width*height; ++i) {
		data[i] =  static_cast<float>(img.data[i]) / 255.0;
	}

	// cnn prediction
	cnn->TakeInput(data, height, width, channel);
	cnn->Forward();
	Blob* detectorMap = cnn->get_blob(21);

	int widthBlob = detectorMap->width;
	int heightBlob = detectorMap->height;
	int channelBlob = detectorMap->channels;

	cout << widthBlob << " " << heightBlob << " " << channelBlob << endl;
	// upsample feature map 


	// nms


	return 0;
}

int upsample_feature_map();

int bbox_nms();

