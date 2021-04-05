# icebergelifetime
_Modified: Apr 5, 2021_

## Intended use

This code is to be used for the calculation of the electron lifetime at the ICEBERG test stand. There are two components to this code, one to create the ntuples to be used for doing the analysis. This involves using decoded iceberg files that include the calorimetry and track reconstruction data products.

The second component is the actual analysis where the lifetime is calculated

The code contains a LArSoft analyser module to be used to create a common ntuple(s) for the electron lifetime studies.

This code is a seperate package from dunetpc for the sake of ease of use, but it still depends on products from `dunetpc` (and consequently on `larsoft`).

## Installation
```
# in a fresh shell

mkdir testdev # use any name you desire
cd testdev/
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc v09_17_01 -q e19:prof # or whatever version of dunetpc we are on
mrb newDev
. localProducts_larsoft_*/setup
mrb g https://github.com/icaromx/icebergelifetime
mrbsetenv
mrb i
```

## Creating the Ntuples

```
# in a fresh shell

cd testdev

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc v09_17_01 -q e19:prof #or whatever version of dunetpc you used
. localProducts_larsoft_*/setup
mrbslp

mkdir work
cd work

MYFILE=/dune/data/users/icaro/Testfiles/iceberg_r005040_sr01_20200310T102105_1_dl1_reco.root

lar -c icebergelifetime.fcl --no-output $MYFILE
```

## Doing an Analysis

```
# copy and source setup.sh in the desired directory where the analysis will be done

```

### Note
The `dunetpc` version above may change in the future, check in the `ups/product_deps` file which version the code currently depends on.
