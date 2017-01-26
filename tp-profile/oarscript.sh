#!/bin/bash
#OAR --project formation-ced-2016
#OAR -t devel
#OAR -l /nodes=1/cpu=1/core=1,walltime=00:02:00
#OAR -n tp1

set -x
# Choisir l'executable (chemin absolu!)
EXE=/home/$USER/TPPROFIL/a.out
# Choisir le compilateur
GNU=1
#GNU=0

# Liste des noeuds
export NODES=`awk -v ORS=, '{print}' $OAR_FILE_NODES|sed 's/,$//'`
set +x

# Chargement des modules necessaires
source /applis/site/env.bash
set -x
# Number of cores
nbcores=`cat $OAR_NODE_FILE|wc -l`
# Number of nodes
nbnodes=`cat $OAR_NODE_FILE|sort|uniq|wc -l`
#Name of the first node
firstnode=`head -1 $OAR_NODE_FILE`
#Number of cores allocated on the first node (it is the same on all the nodes)
pernode=`grep "$firstnode\$" $OAR_NODE_FILE|wc -l`

set +x

if (( $GNU == 1 )) ; then

####################
# GNU
###################

module load gnu-devel/4.4.6
$EXE

# -x LD_LIBRARY_PATH : envoie une var d'env a chaque processus
# --machinefile $OAR_NODE_FILE : Provide a hostfile to use 
# --mca <<key>> <<value>> : btl_sm_use_knem ?
# -np $nbcores : run X copies of <program> 

else

#####################
## INTEL
#####################

module load intel-devel/14
$EXE
fi
