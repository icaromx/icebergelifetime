#source setup_icebergelifetime.sh

export ANALYSIS_DIR=`pwd`
echo $ANALYSIS_DIR
mkdir $ANALYSIS_DIR/Plots

RUN='5'

export FILENAME=$ANALYSIS_DIR/icebergelifetime

cd $MRB_SOURCE/icebergelifetime/analysis/

if [[ $1 != "JP" ]]; then
	root -l -b -q 'ana_elifetime.C("'$FILENAME'")'
	mv fout_ana_elifetime.root $ANALYSIS_DIR/Plots
fi

root -l -b -q 'plot.C("'$ANALYSIS_DIR/Plots/fout_ana_elifetime'","'$RUN'")'
cp -r Plots/* $ANALYSIS_DIR/Plots
rm -rf Plots/

cd $ANALYSIS_DIR



