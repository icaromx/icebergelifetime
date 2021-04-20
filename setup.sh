VERSION=v09_20_00
QUAL=e19
AREA=`pwd`
DEV_AREA=$AREA/dev
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc $VERSION -q ${QUAL}:prof
cd $DEV_AREA
source localProducts_larsoft_${VERSION}_${QUAL}_prof/setup
#setup ninja v1_8_2
mrbsetenv
#only for the first time, build/install with ninja
#mrb i --generator ninja
#in the future, you need build with ninja if you modified the source files
# setup local products: slp
mrbslp
cd ..
echo 'working at: ' $AREA

export ANALYSIS_SCRIPTS=$MRB_SOURCE/icebergelifetime/analysis/

alias do_analysis='. $ANALYSIS_SCRIPTS/do_analysis.sh' 
