#!/bin/bash
make
rm *.o

# ------------------------------------------------------------------------------
#  Parameters
# ------------------------------------------------------------------------------
dname=sift100K
n=100000
qn=1000
d=128
B=4096
dPath=/home/xikafe/dataset/${dname}/txt/${dname}


# ------------------------------------------------------------------------------
#  Running Scripts
# ------------------------------------------------------------------------------
L_list=(8) 
M_list=(70)
length=`expr ${#L_list[*]} - 1`

for j in $(seq 0 ${length})
do 
  l=${L_list[j]}
  m=${M_list[j]}
  oFolder=./results2.0/${dname}/drusilla/${l}-${m}/

  ./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}D.txt \
   		-of ${oFolder}

  ./drusilla -alg 2 -n ${n} -qn ${qn} -d ${d} -ds ${dPath}D.txt -qs ${dPath}Q.txt -ts ${dPath}.fn2.0 \
    	-of ${oFolder}
done
