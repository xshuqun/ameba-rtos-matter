#!/bin/bash

set -e

if [ -z "$1" ]; then
  echo "Error: No base directory provided."
  echo "Usage: $0 <base_directory>"
  exit 1
fi

basedir=$1
chipdir=${basedir}/connectedhomeip
amebadir=${basedir}/ameba-rtos-d

cd ${chipdir}
source ${chipdir}/scripts/bootstrap.sh
source ${chipdir}/scripts/activate.sh

cd ${amebadir}

chmod u+x matter_setup.sh
.//matter_setup.sh amebad

cp ${amebadir}/component/common/application/matter/tools/docker/amebad/platform_autoconf.h ${amebadir}/project/realtek_amebaD_va0_example/inc/inc_hp

echo "Build project_lp"
cd ${amebadir}/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp
make all

echo "Build project_hp"
cd ${amebadir}/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp

echo "Building all_clusters"
make -C asdk all_clusters

echo "Building firmware image"
make all

echo "Build all-clusters-app completed"
make clean

echo "Building lighting"
make -C asdk light

echo "Building firmware image"
make all

echo "Build lighting completed"
make clean
