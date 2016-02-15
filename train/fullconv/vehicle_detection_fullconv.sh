#!/usr/bin/env sh
TOOLS=/home/xiang.wu/caffe/build/tools
mkdir log
export PATH=/usr/local/cuda-7.5/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-7.5/lib64:$LD_LIBRARY_PATH

export PATH=/usr/bin:$PATH
export LD_LIBRARY_PATH=/usr/lib:$LD_LIBRARY_PATH

GLOG_logtostderr=0 GLOG_alsologtostderr=1 $TOOLS/caffe train --solver=./vehicle_detection_solver_fullconv.prototxt --gpu=3 #--snapshot=DeepFace_set003_net_iter_520000.solverstate
