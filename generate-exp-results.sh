#!/bin/sh

SIMULATOR_FOLDER="/home/maltanar/sandbox/build/spmvaccsim"
MATRICES="Williams-webbase-1M Williams-mc2depi Hamm-scircuit Williams-mac_econ_fwd500 Williams-cop20k_A DNVS-shipsec1 Boeing-pwtk Williams-consph"
CACHE_SIZES="1024 2048 4096 8192 16384 32768 65536 131072"
RESULT_FOLDER="/home/maltanar/sandbox/results/spmvaccsim"

mkdir -p $RESULT_FOLDER

for depth in $CACHE_SIZES; do
  for matrix in $MATRICES; do
    #echo "Now processing matrix $matrix with cache depth $depth"
    $SIMULATOR_FOLDER/spmvaccsim-$depth -m $matrix -c 1
    #> $RESULT_FOLDER/$depth-$matrix-coldskip.txt
    $SIMULATOR_FOLDER/spmvaccsim-$depth -m $matrix -c 0
    #> $RESULT_FOLDER/$depth-$matrix-nocoldskip.txt
  done
done

