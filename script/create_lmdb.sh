echo "Creating lmdb..."
export PATH=/usr/local/cuda-7.5/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-7.5/lib64:$LD_LIBRARY_PATH

TOOL_PATH="/home/xiang.wu/caffe/build/tools"
DATA_PATH="/home/xiang.wu/data/vehicle/train_set200/"
SAVE_PATH="/home/xiang.wu/data/lmdb"


GLOG_logtostderr=1 $TOOL_PATH/convert_imageset --resize_width=64 --resize_height=64 --backend=lmdb --gray=true $DATA_PATH/ $DATA_PATH/train_set200_list_rng7610.txt $SAVE_PATH/vehicle_train_set200_list_rng7610_lmdb