# Drusilla_RAM: RAM based (internal) version of Drusilla_Select by xikafe
04 Jun 2019





# Drusilla_Ext: External Version (Thanks HuangQiang) of Drusilla_Select

Version: 1.0.1

Release date:  03-01-2018

Last Modified: 04-05-2018


Introduction
--------

This package is written in the C++ programming language. Drusilla_Ext is 
an external version of Drusilla_Select, which is used for c-Approximate 
Furthest Neighbor (or simply c-AFN) search under Euclidean distance. 

The original Drusilla_Select is an internal algorithm which was proposed 
by Dr. Ryan Curtin and Dr. Andrew Gardner in their SISAP 2015 paper. We 
adapt the original one into an external algorithm used for our comparison 
with RQALSH and RQALSH* in our ICDE 2017 and TKDE 2017 papers. 


How to use this Package?
--------

We provide a Makefile and a script (i.e., run_mnist.sh) as a running example 
for comipling and running this package. Before start running this package, 
please ensure the input format of the dataset and query set is correct. We 
provide a sample dataset and query set (i.e., Mnist) for your reference.

We also provide the scripts (i.e., run_sift.sh, run_gist.sh, run_trevi.sh,
and run_p53.sh) for the users who would like to reproduce our results 
presented in our ICDE 2017 and TKDE 2017 papers. The datasets Sift, Gist, 
Trevi, and P53 we used can be downloaded from the following links:

* Sift: https://drive.google.com/open?id=1tgcUU9X61TehVa_Klj5skVdYRoYZ7CgX

* Gist: https://drive.google.com/open?id=1fvUTGUbYgg8oaGNbZbAMLnfmxoU8UDhh

* Trevi: https://drive.google.com/open?id=1XSiiQ6D1zoxGXULl3sHxsjPO8JCM-md1

* P53: https://drive.google.com/open?id=1hjGvcq29WsgHpGoz0vCdCYAUR453aY29


Authors
--------

* **Qiang Huang**

  Smart Systems Institute, National University of Singapore (NUS),
  
  Singapore, 119613 
  
  huangq2011@gmail.com, huangq25@mail2.sysu.edu.cn
  
  https://sites.google.com/site/qianghuang2017/


Relevant Paper
--------

The paper for Drusilla_Select has been published in SISAP 2016, which is displayed 
as follows:

* **Ryan R. Curtin and Andrew B. Gardner. Fast approximate furthest neighbors with 
data-dependent candidate selection. International Conference on Similarity Search 
and Applications (SISAP), 221 - 235, 2016.**

* **Ryan R. Curtin, Javier Echauz, and Andrew B. Gardner. Exploiting the structure 
of furthest neighbor search for fast approximate results. Information Systems, 2018.**

If you use the package for publications, please cite their papers above.
