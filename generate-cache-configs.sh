#!/bin/sh

PROJECT_FILE="/home/maltanar/sandbox/spmvaccsim/spmvaccsim.pro"
#CACHE_SIZES="1024 2048 4096 8192 16384 32768 65536 131072"
CACHE_SIZES="1024 2048"
WORK_DIR="/home/maltanar/sandbox/build/spmvaccsim-work"
TARGET_DIR="/home/maltanar/sandbox/build/spmvaccsim"

mkdir -p $WORK_DIR
mkdir -p $TARGET_DIR

for depth in $CACHE_SIZES; do
  currentWorkDir="$WORK_DIR/$depth"
  # create dir for this cache depth
  mkdir -p $currentWorkDir
  cd $currentWorkDir
  echo "Now building configuration $depth in $currentWorkDir"
  # generate the makefile
  qmake $PROJECT_FILE "CACHE_DEPTH=$depth"
  # build
  make -j8
  # move resulting executable
  cp spmvaccsim $TARGET_DIR/spmvaccsim-$depth 
  # cleanup
  cd $WORK_DIR
  rm -rf $currentWorkDir
done

rm -rf $WORK_DIR
