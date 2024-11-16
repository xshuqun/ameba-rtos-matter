#!/bin/bash

set -e

if [ -z "$1" ]; then
  echo "Error: No base directory provided."
  echo "Usage: $0 <base_directory>"
  exit 1
fi

basedir=$1
chipdir=${basedir}/connectedhomeip
amebadir=${basedir}/ameba-rtos-z2

cd ${chipdir}
source ${chipdir}/scripts/bootstrap.sh
source ${chipdir}/scripts/activate.sh

echo "Changing directory to build location ${amebadir}"

cd ${amebadir}

chmod u+x matter_setup.sh
./matter_setup.sh amebaz2

cd ${amebadir}/project/realtek_amebaz2_v0_example/GCC-RELEASE/

echo "Building all_clusters"
make all_clusters

echo "Building firmware image"
make is_matter

echo "Build all-clusters-app completed"
make clean_matter_libs
make clean_matter

echo "Building lighting"
make light

echo "Building firmware image"
make is_matter

echo "Build lighting completed"
make clean_matter_libs
make clean_matter

cd ${amebadir}/
chmod u+x matter_setup.sh
./matter_setup amebaz2plus

cd ${amebadir}/project/realtek_amebaz2plus_v0_example/GCC-RELEASE/

echo "Building all_clusters"
make all_clusters

echo "Building firmware image"
make is_matter

echo "Build all-clusters-app completed"
make clean_matter_libs
make clean_matter

echo "Building lighting"
make light

echo "Building firmware image"
make is_matter

echo "Build lighting completed"
make clean_matter_libs
make clean_matter
