#include <cnn_detection.h>

int main() {

	Mat img = imread("D:\\code\\vehicle_detection\\test\\model\\test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	resize(img, img, Size(640, 480));

	Net cnn;
	const char* modelPath = "D:\\code\\vehicle_detection\\test\\model\\cnn.bin";

	// init
	int ret_init = fullconv_cnn_init(&cnn, modelPath);

	// detect
	int ret_detector = fullconv_cnn_detect(img, &cnn);

	return 0;
}