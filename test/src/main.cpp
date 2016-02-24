#include <cnn_detection.h>

int main() {

	Mat img = imread("D:\\code\\vehicle_detection\\test\\model\\test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	resize(img, img, Size(640, 480));

	Net cnn;
	const char* modelPath = "D:\\code\\vehicle_detection\\test\\model\\cnn.bin";

	// init
	int ret_init = fullconv_cnn_init(&cnn, modelPath);

	// detect
	multimap<float, Rect>  bbox;
	int stride = 5;
	float thr = 0.5;
	int minSize = 64;
	int maxSize = min(img.cols, img.rows) / 3;
	float step = 1.3;

	int ret_detector = fullconv_multiscale_detect(img, bbox, &cnn, minSize, maxSize, step);


	for(auto box = begin(bbox); box !=end(bbox); ++box) {
		Rect rect = box->second;
		rectangle(img, rect, Scalar(0, 0, 255), 2);
	}
	imwrite("result.jpg", img);

	return 0;
}