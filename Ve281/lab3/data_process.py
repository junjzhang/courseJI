#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct  4 21:15:44 2019

@author: zhangjunjie
"""
import numpy as np
import matplotlib.pyplot as plt

m = 0
n = 22

def plot(x,y):
    plt.figure(figsize=(10,12))
    plt.plot(x,y)
    plt.xlabel("array size",fontsize = 100)
    plt.ylabel(r"$log_{10}$ time costed (ms)",fontsize = 35)
    plt.show()
    return
font1 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size'   : 23,
}
x = 2**np.array([range(2,24)])
y_bubble = np.array([0.199,0.457,1.541,5.02,17.495,63.659,248.47,872.767,3845.89,14453.4,42178.1,179090,743468,2.97419e06,1.21348e7])
y_insertion = np.array([0.249,0.397,0.776,2.107,6.59,25.07,91.45,361.06,1395.78,5474.95,13477.7,45569.3,187240,749774,4.81304e06])
y_selection = np.array([0.209,0.477,1.56,5.388,17.863,62.775,241.479,931.501,3706.85,10863.7,37403.7,165678,689636,2.78981e6,1.12232e7])
y_merge = np.array([0.835,1.292,2.525,5.288,11.183,24.046,53.529,138.35,246.322,527.695,1139.14,2437.99,5191.91,8942.42,12124.5,27485.6,47509.8,83073.7,169137,343070,692609,1.4064e+06])
y_quick = np.array([0.467,0.945,1.928,3.708,7.684,16.699,36.223,77.654,175.209,372.079,812.568,1746.75,3696.23,8014.14,8753.38,11267.1,22216,39892.6,71628.2,144812,313752,645546])
y_rs = np.array([0.368,0.686,1.481,2.078,1.699,5.527,12.157,19.046,23.887,64.463,190.657,284.604,454.337,700.888,2795.27])
y_ds = np.array([0.686,1.233,2.405,4.682,8.688,17.903,30.855,64.315,150.25,237.528,423.743,846.572,1799.33,3576.33,5308.32])
plt.figure(figsize=(12,8))
#plt.plot(x[0,m:n],(y_bubble[m:n]),color = "darkseagreen", label = "bubble sort")
#plt.plot(x[0,m:n],(y_insertion[m:n]),color = "indianred",label = "insertion sort")
#plt.plot(x[0,m:n],(y_selection[m:n]),color = "cornflowerblue", label = "selsection sort")
plt.plot(x[0,m:n],(y_merge[m:n]),color = "lightslategrey",label = "merge sort",linestyle ="--")
plt.plot(x[0,m:n],(y_quick[m:n]),color = "gold",label = "quick sort",linestyle = "--")
#plt.plot(x[0,m:n],(y_rs[m:n]),color = "olivedrab",label = "random selection")
#plt.plot(x[0,m:n],(y_ds[m:n]),color = "sienna",label = "deterministic selection")
plt.xlabel("array size",fontsize = 14)
plt.ylabel("time costed (ms)",fontsize = 14)

plt.legend(fontsize = 12)
plt.show()