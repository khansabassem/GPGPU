# !/bin/bash

set -e
set -u

##########################################
# Rippling
##########################################

cd ../01_rippling
./rippling_benchmark_best.sh 
cd -

##########################################
# Mandelbrot
##########################################

cd ../02_mandelbrot
./mandelbrot_float_benchmark_best.sh 
cd -

cd ../02_mandelbrot
./mandelbrot_double_benchmark_best.sh 
cd -

##########################################
# Raytracing
##########################################

cd ../03_raytracing
./raytracing_benchmark_best.sh 
cd -

##########################################
# sleep
##########################################

sleep 59m

##########################################
# end
##########################################

echo ""
echo "Finsihed!"
echo ""
