# !/bin/bash

set -e
set -u

##########################################
# Reduction
##########################################

#########
# add
#########

cd ../04_reduction/add/test
./testReductionAdd_int_PI.sh
cd -

cd ../04_reduction/add/test
./testReductionAdd_int_PII.sh
cd -

#########
# generic
#########

cd ../04_reduction/generic/test
./testReduction_int_PI.sh
cd -

cd ../04_reduction/generic/test
./testReduction_int_PII.sh
cd -

cd ../04_reduction/generic/test
./testReduction_long_PII.sh
cd -

##########################################
# Slice
##########################################


cd ../05_slice/test
./testSliceGM_Host.sh
cd -

cd ../05_slice/test
./testSliceGM.sh
cd -

cd ../05_slice/test
./testSliceSM.sh
cd -

##########################################
# Montecarlo
##########################################

#########
# mono
#########

cd ../06_montecarlo/test
./testMontecarlo_int.sh
cd -

cd ../06_montecarlo/test
./testMontecarlo_long.sh
cd -

#########
# multi
#########

cd ../07_montecarloMulti/test
./testMontecarlo_multi_int.sh
cd -

cd ../07_montecarloMulti/test
./testMontecarlo_multi_long.sh
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
