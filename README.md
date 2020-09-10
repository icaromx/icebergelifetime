# icebergelifetime
_Modified: Sep 9, 2020_

## Intended use

This code is to be used for the calculation of the electron lifetime at the ICEBERG test stand.

The code contains a LArSoft analyser module to be used to create a common ntuple(s) for the electron lifetime studies.

This code is a seperate package from dunetpc for the sake of ease of use, but it still depends on products from `dunetpc` (and consequently on `larsoft`).

## Installation
```
# in a fresh shell

mkdir testdev # use any name you desire
cd testdev/
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc v08_62_00 -q e19:prof # or whatever version of dunetpc we are on
mrb newDev
. localProducts_larsoft_*/setup
mrb g https://github.com/icaromx/icebergelifetime.git
mrbsetenv
mrb i
```

## Test/run

```
# in a fresh shell

cd testdev

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc v08_62_00 -q e19:prof #or whatever version of dunetpc you used
. localProducts_larsoft_*/setup
mrbslp

mkdir work
cd work

MYFILE=/dune/data/users/icaro/Testfiles/iceberg_r005040_sr01_20200310T102105_1_dl1_reco.root

lar -c icebergelifetime.fcl --no-output $MYFILE
```

### Note
The `dunetpc` version above may change in the future, check in the `ups/product_deps` file which version the code currently depends on.
