# !/bin/bash

set -e
set -u

##########################################
# Reduction
##########################################

#########
# add
#########

cd ../04_reduction/add/use
./reductionAdd_int_PI.sh
cd -

cd ../04_reduction/add/use
./reductionAdd_int_PII.sh
cd -

#########
# generic
#########

cd ../04_reduction/generic/use
./reduction_int_PI.sh
cd -

cd ../04_reduction/generic/use
./reduction_int_PII.sh
cd -

cd ../04_reduction/generic/use
./reduction_long_PII.sh
cd -

##########################################
# Slice
##########################################

cd ../05_slice/use
./sliceGM_Host.sh
cd -

cd ../05_slice/use
./sliceGM.sh
cd -

cd ../05_slice/use 
./sliceSM.sh
cd -

##########################################
# Montecarlo
##########################################

#########
# mono
#########

cd ../06_montecarlo/use
./montecarlo_int.sh
cd -

cd ../06_montecarlo/use
./montecarlo_long.sh
cd -

#########
# multi
#########

cd ../07_montecarloMulti/use
./montecarlo_multi_int.sh
cd -

cd ../07_montecarloMulti/use
./montecarlo_multi_long.sh   
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
