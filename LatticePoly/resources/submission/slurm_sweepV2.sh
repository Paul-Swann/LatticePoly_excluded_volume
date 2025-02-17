#!/bin/bash

##
##  slurm.sh
##  LatticePoly
##
##  Created by mtortora on 20/06/2022
##  Copyright © 2022 ENS Lyon. All rights reserved.
##

#SBATCH -o %A_%a.out
#SBATCH -e %A_%a.err

# Relative path to code root directory
ROOTDIR=${SCRIPTDIR}/../..

# Set working directory to root
cd ${ROOTDIR}

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTDIR/lib
PYTHONPATH=$PYTHONPATH:$ROOTDIR/resources

export LD_LIBRARY_PATH
export PYTHONPATH

# Executable path
EXEC=bin/lat

#QVARS="OUTPUTDIR=$1,PARAM=$2,MIN_VAL=$3,MAX_VAL=$4,SCRATCHDIR=${SCRATCHDIR},SCRIPTDIR=${SCRIPTDIR}"
#QVARS2="PARAM2=$5,MIN_VAL2=$6,MAX_VAL2=$7,STEP=$s,ITER=$i"  {printf("%.4f\n", $1+($2-$1)/($4/4-$3)*($5+($6-1)*4)}

TASK_ID_RESCALLED=$(((SLURM_ARRAY_TASK_ID-1)/12))

VAL=$(echo ${MIN_VAL} ${MAX_VAL} ${SLURM_ARRAY_TASK_MIN} ${SLURM_ARRAY_TASK_MAX} ${SLURM_ARRAY_TASK_ID} | awk '{printf("%.4f\n", $1+($2-$1)/($4/4-$3)*(($5-$3)%12))}')
VAL2=$(echo ${MIN_VAL2} ${MAX_VAL2} ${SLURM_ARRAY_TASK_MIN} ${SLURM_ARRAY_TASK_MAX} ${TASK_ID_RESCALLED} ${STEP} | awk '{printf("%.4f\n", $1+($2-$1)/($4/4-$3)*($5+($6-1)*4))}')

# Data directory on local disk
DATDIR=${PARAM}
[ ! -z "${PARAM2}" ] && DATDIR=${PARAM2}/${VAL2}/${DATDIR}

DATDIR=data/${OUTPUTDIR}/${DATDIR}

# Ouput directory on scratch
TMPDIR=${PARAM}_${VAL}_${ITERATION}
[ ! -z "${PARAM2}" ] && TMPDIR=${PARAM2}_${VAL2}_${TMPDIR}

TMPDIR=${SCRATCHDIR}/${LOGNAME}/Painter_Clone2/LatticeData/${TMPDIR}

# Create output directory if necessary
[ ! -d "${TMPDIR}" ] && mkdir -p ${TMPDIR}

# Substitution strings
DIRSUB="s|\(outputDir[[:space:]]*=[[:space:]]*\)\(.*;\)|\1${TMPDIR} ;|;"
VALSUB="s|\(${PARAM}[[:space:]]*=[[:space:]]*\)\(.*;\)|\1${VAL} ;|;"

[ ! -z "${PARAM2}" ] && VAL2SUB="s|\(${PARAM2}[[:space:]]*=[[:space:]]*\)\(.*;\)|\1${VAL2} ;|;"

# Copy input configuration file to output directory, substituting paths and parameter values
sed -e "${DIRSUB}""${VALSUB}""${VAL2SUB}" < data/input.cfg > ${TMPDIR}/input.cfg

# Run
./${EXEC} ${TMPDIR}/input.cfg > ${TMPDIR}/log.out

# Perform post-processing analyses
python3 resources/DistanceMap.py ${TMPDIR} -1 10 >> ${TMPDIR}/process.out
python3 resources/LiqCluster.py ${TMPDIR} -1 >> ${TMPDIR}/process.out
python3 resources/LiqDensity.py ${TMPDIR} -1 >> ${TMPDIR}/process.out
python3 resources/LiqMSD.py ${TMPDIR} -1 >> ${TMPDIR}/process.out
python3 resources/LiqPolyContact.py ${TMPDIR} -1 >> ${TMPDIR}/process.out
python3 resources/PolyGyration.py ${TMPDIR} -1 >> ${TMPDIR}/process.out
python3 resources/PolyMSD.py ${TMPDIR} -1 >> ${TMPDIR}/process.out

# Move SLURM output files to data directory
mv ${SLURM_SUBMIT_DIR}/${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.out ${TMPDIR}
mv ${SLURM_SUBMIT_DIR}/${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.err ${TMPDIR}

# Create data directory on local disk
[ ! -d "${DATDIR}/${VAL}" ] && mkdir -p ${DATDIR}/${VAL}

# Archive output files to home directory
tar --transform "s|^|${VAL}/|" -czvf ${DATDIR}/${VAL}/${ITERATION}.tar.gz -C ${TMPDIR} .

# Clean scratch
rm -rf ${TMPDIR}
