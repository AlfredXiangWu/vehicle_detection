#include <cnn_detection.h>

int main() {

	Mat img = imread("D:\\code\\vehicle_detection\\test\\model\\test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	resize(img, img, Size(640, 480));

	Net cnn;
	const char* modelPath = "D:\\code\\vehicle_detection\\test\\model\\cnn.bin";

	// init
	int ret_init = fullconv_cnn_init(&cnn, modelPath);

	// detect
	ValStructVec<float, Rect> bbox;
	bbox.reserve(10000);
	int stride = 10;
	float thr = 0.5;
	int minSize = 64;
	int maxSize = min(img.cols, img.rows) / 2;
	float step = 1.2;

	int ret_detector = fullconv_multiscale_detect(img, bbox, &cnn, minSize, maxSize, step);

	return 0;
}