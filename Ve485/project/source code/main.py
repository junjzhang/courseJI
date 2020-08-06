'''
* This file is the main file to start the program
** author: Junjie Zhang
'''
import numpy as np
import matplotlib.pyplot as plt
import sys
import getopt
from sklearn.manifold import LocallyLinearEmbedding
from sklearn.decomposition import PCA
from mpl_toolkits.mplot3d import Axes3D
from data import *
from lle import *


def printHelp():
    print('Usage: python main.py -n <num of the sample> -s <shape of the manifold> -k <num of neighbors to be used>')
    print('<shape of the mainfold>: sr for swiss roll, s for S shape, b for bowl shape')
    return


def main(argv):
    # handle argument
    numSample = 500
    shape = 'sr'
    kNeibors = 30
    try:
        opts, args = getopt.getopt(
            argv, "hn:s:k:", ['help', 'numSample=', 'shape=', 'numNeighbo='])
    except getopt.GetoptError:
        printHelp()
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            printHelp()
            sys.exit()
        elif opt in ('-n', '--numSample'):
            numSample = int(arg)
        elif opt in ('-s', '--shape'):
            if arg in ('sr', 's', 'b'):
                shape = arg
            else:
                print(
                    '<shape of the mainfold>: sr for swiss roll, s for S shape, b for bowl shape')
                sys.exit(2)
        elif opt == 'k':
            kNeibors = int(arg)

    # genereate data
    if (shape == 'sr'):
        X, color = swissRoll(0, 1.5, numSample, noise=0.1)
    elif (shape == 's'):
        X, color = sShape(0, 1, numSample, noise=0.1)
    elif (shape == 'b'):
        X, color = ball(0.3, 1, numSample, noise=0.01)

    # set up solver
    lleSolver = LLE(X, 2, kNeibors)
    lowX1 = lleSolver.transform()

    # solve my sklern
    lowX2 = LocallyLinearEmbedding(
        n_components=2, n_neighbors=kNeibors).fit_transform(X)

    # solve by PCA
    pca = PCA(n_components=2)
    pca.fit(X)
    lowX3 = pca.fit_transform(X)

    X = X.T
    # plot of original data
    fig1 = plt.figure(1)
    ax3D = Axes3D(fig1)
    ax3D.scatter(X[0], X[1], X[2], c=color)

    plt.figure(2, figsize=(8, 5))
    # plot of my solver
    plt.subplot(131)
    plt.title("Result of my LLE")
    plt.scatter(lowX1[:, 0], lowX1[:, 1], c=color)

    # plot of sklearn solver
    plt.subplot(132)
    plt.title("Result of sklearn's LLE")
    plt.scatter(lowX2[:, 0], lowX2[:, 1], c=color)

    # plot of sklearn PCA solver
    plt.subplot(133)
    plt.title("Result of sklearn's PCA")
    plt.scatter(lowX3[:, 0], lowX3[:, 1], c=color)

    plt.show()


if __name__ == '__main__':
    main(sys.argv[1:])
