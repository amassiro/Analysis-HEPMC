########################################
# SET ENVIRONMENT VARs FOR ROOT
export ROOTSYS=/home/amassiro/root-v5-34/
export PATH=$PATH:$ROOTSYS/bin
export PATH=$PATH:$ROOTSYS/include
# export LD_LIBRARY_PATH=$ROOTSYS/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib
########################################

##################################################
# new SET ENVIRONMENT VARs FOR ROOT ---> ROOT 5.25
. $ROOTSYS/bin/thisroot.sh
##################################################

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.


##### ENVIRONMENT VARIABLES FOR THE MAKEFILE
export CC_ENV=/usr/bin/g++-4.4
export BOOSTFLAGS_ENV="-I$/usr/include/boost"
export BOOSTLIBS_ENV="-lboost_program_options"


ln -s ../Delphes-3.0.10/external/fastjet   .
ln -s ../Delphes-3.0.10/external/ExRootAnalysis   .
ln -s -d ../Delphes-3.0.10/classes .
ln -s ../Delphes-3.0.10/libDelphes.so .
