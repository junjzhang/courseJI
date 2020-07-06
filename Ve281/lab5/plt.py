# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
import matplotlib.pyplot as plt

def plot(x,y):
    plt.figure(figsize=(10,12))
    plt.plot(x,y)
    plt.xlabel("width",fontsize = 100)
    plt.ylabel(r"time costed (ms)",fontsize = 35)
    plt.show()
    return
font1 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size'   : 23,
}
x = 2**np.array([range(3,11)])
y_b = np.array([2324.4,4165.97,11976,29883.1,92916.5,364875,1.43269e+06,5.54236e+06])
y_u = np.array([2392.06,4332.82,10698.6,34356.4,131198,716602,4.18925e+06,3.15113e+07])
y_f = np.array([2516.76,4927.1,13428,37502,129138,543947,2.08741e+06,8.65231e+06])
plt.figure(figsize=(12,8))
#plt.plot(x[0,m:n],(y_bubble[m:n]),color = "darkseagreen", label = "bubble sort")
plt.plot(x[0,],y_b,color = "indianred",label = "Binary")
plt.scatter(x[0,],y_b,color = "indianred",label = "Binary")
plt.plot(x[0,],y_u,color = "lightslategrey",label = "Unsorted")
plt.scatter(x[0,],y_u,color = "lightslategrey",label = "Unsorted")
plt.plot(x[0,],y_f,color = "gold",label = "Fibonacci")
plt.scatter(x[0,],y_f,color = "gold",label = "Fibonacci")
#plt.plot(x[0,m:n],(y_rs[m:n]),color = "olivedrab",label = "random selection")
#plt.plot(x[0,m:n],(y_ds[m:n]),color = "sienna",label = "deterministic selection")
plt.xlabel("width",fontsize = 14)
plt.ylabel("time costed (ms)",fontsize = 14)

plt.legend(fontsize = 12)
plt.show()