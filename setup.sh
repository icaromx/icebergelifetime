VERSION=v09_17_01
QUAL=e19
AREA=dev_icebergelifetime
WORKSPACE=/dune/app/users/$USER/dev_areas/$AREA/dev
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc $VERSION -q ${QUAL}:prof
cd $WORKSPACE
source localProducts_larsoft_${VERSION}_${QUAL}_prof/setup
#setup ninja v1_8_2
mrbsetenv
#only for the first time, build/install with ninja
#mrb i --generator ninja
#in the future, you need build with ninja if you modified the source files
# setup local products: slp
mrbslp
cd -
#echo 'working at: ' $WORKSPACE
#whenever you want to compile do the following
#cd $MRB_BUILDDIR
#ninja install
#x509 and grid proxy
#setup_fnal_security

export ANALYSIS_SCRIPTS=$MRB_SOURCE/icebergelifetime/analysis/

alias do_analysis='. $ANALYSIS_SCRIPTS/do_analysis.sh' 
