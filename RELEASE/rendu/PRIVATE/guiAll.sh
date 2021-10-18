# !/bin/bash

set -e
set -u

##########################################
# Rippling
##########################################

cd ../01_rippling
./rippling.sh &
cd -

##########################################
# Mandelbrot
##########################################

cd ../02_mandelbrot
./mandelbrot_float.sh &
cd -

cd ../02_mandelbrot
./mandelbrot_double.sh &
cd -

cd ../02_mandelbrot
./mandelbrot_half.sh &
cd -

##########################################
# Raytracing
##########################################


cd ../03_raytracing
./raytracingGM.sh &
cd -

cd ../03_raytracing
./raytracingGM2SM.sh &
cd -

cd ../03_raytracing
./raytracingCM.sh &
cd -

cd ../03_raytracing
./raytracingCM2SM.sh &
cd -

##########################################
# DemoCube3D
##########################################

cd ../09_demoCube3D
./demoCube3D.sh &
cd -

##########################################
# Mandelbrot
##########################################

cd ../08_mandelbrot3D
./mandelbrot3D.sh &
cd -

##########################################
# end
##########################################

echo ""
echo "Finsihed!"
echo ""
