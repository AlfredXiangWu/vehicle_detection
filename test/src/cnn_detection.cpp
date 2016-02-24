#include "cnn_detection.h"
#define NET_SIZE 64
#define PROB 21


int fullconv_cnn_init(Net *cnn, const char* modelPath) {

	if(cnn->LoadFromFile(modelPath)) {
		cout << "Load model error!" << endl;
		return -1;
	}

	return 0;
}

int fullconv_multiscale_detect(const Mat img, multimap<float, Rect> &bbox, Net *cnn, const int minSize, const int maxSize, const float scaleStep){
	
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
	const int stride = 10;
	const float thr = 0.5;
	
	// Multi-scale detect
	Mat imgResize;
	multimap<float, Rect> rectMap;
	for(float scale  = minScale; scale <= maxScale; scale = scale*scaleStep) {
		resize(imgGray, imgResize, Size(imgGray.rows*scale, imgGray.cols*scale));
		fullconv_cnn_detect(imgResize, cnn, stride, thr, scale, rectMap);
	}

	int ret_nms = bbox_nms(rectMap, bbox, 1e-3);

	return 0;
}

int fullconv_cnn_detect(const Mat img,  Net *cnn, const int stride, const float thr, const float scale, multimap<float, Rect> &bbox) {

	// convert pixel from [0, 255] to [0, 1]
	const int width = img.rows;
	const int height = img.cols;
	const int channel = img.channels();
	float* data = (float*)malloc(width*height*sizeof(float));
	for(int i = 0; i < width*height; ++i) {
		data[i] =  static_cast<float>(img.data[i]) / 255.0;
	}

	float* patch = (float*)malloc(NET_SIZE*NET_SIZE*sizeof(float));
	Rect rect;

	// window scanning (No multi-scale scanning)
	for (int w = 0; w < width - NET_SIZE; w = w + stride) {
		for (int h = 0; h < height - NET_SIZE; h = h + stride) {

			// patch init
			for (int k = 0; k < NET_SIZE; ++k) {
				int idx = (h + k)*width;
				memcpy(patch + k*NET_SIZE, data + w + idx, sizeof(float)*NET_SIZE);
			}

			cnn->TakeInput(patch, NET_SIZE, NET_SIZE, 1);
			cnn->Forward();
			float score = *(cnn->get_blob(PROB)->data + 1);
			if (score > thr){
				rect.x = w / scale;
				rect.y = h / scale;
				rect.width = NET_SIZE / scale;
				rect.height = NET_SIZE / scale;
				bbox.insert(pair<float, Rect>(score, rect));
			}
		}
	}

	free(patch);
	free(data);
	return 0;
}

int bbox_nms(multimap<float, Rect> src, multimap<float, Rect> &dst, const float thr) {

	if (0 == src.size())
		return -1;

	while(src.size() > 0) {
		auto last = --end(src);
		const float prob = last->first;
		const Rect rect1 = last->second;

		dst.insert(pair<float, Rect>(prob, rect1));

		src.erase(last);

		for(auto pos = begin(src); pos !=end(src);) {
			const Rect &rect2 = pos->second;
			float interArea = (rect1 & rect2).area();
			float unionArea = rect1.area() + rect2.area() - interArea;
			float overlap = interArea / unionArea;

			if(overlap > thr) 
				pos = src.erase(pos);
			else
				++pos;
		}
	}



	return 0;
}

