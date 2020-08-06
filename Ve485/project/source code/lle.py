'''
* This file is to implement the algorithem of linear locally embedding.
** author: Junjie Zhang
'''
import numpy as np


class LLE():

    # * initial function
    # ** parameter:
    # *** kNeighbor: number of neighborhood
    # *** targetDim: target dimension after dimension deduction
    # *** X: matrix of samples , where each row is a sample, has dimension of (numSample, originDim)
    def __init__(self, X, targetDim, kNeighbor=5):
        self.kNeighbor = kNeighbor
        self.targetDim = targetDim
        self.X = X
        self.numSample, self.originDim = X.shape

    # * function to calculate the pairwise distance (Euclidean distance)
    def calPairwiseDist(self):
        squreSumMat = np.sum(np.square(self.X), axis=1)
        self.distMat = np.add(
            np.add(-2 * np.dot(self.X, self.X.T), squreSumMat).T, squreSumMat)
        self.distMat[self.distMat < 0] = 0
        self.distMat = self.distMat**0.5

    # * function to select the neigbors
    def selectNeighbor(self):
        # calculate the distance matrix
        self.calPairwiseDist()
        # the first one is itself, skip it
        self.neighborIndexMat = np.argsort(self.distMat, axis=1)[
            :, 1:self.kNeighbor+1]

    # * function to choose regulation parameter according to number of neighbors and the dimension of the data
    def chooseTol(self):
        if self.kNeighbor > self.originDim:
            self.tol = 1e-3
        else:
            self.tol = 0

    # function to reconstruct with linear weights
    def reconstruct(self):
        w = np.zeros((self.kNeighbor, self.numSample))
        I = np.ones((self.kNeighbor, 1))
        for ii in range(self.numSample):
            Xi = np.tile(self.X[ii], (self.kNeighbor, 1)).T
            Neigbori = self.X[self.neighborIndexMat[ii]].T
            Qi = np.dot((Xi-Neigbori).T, (Xi-Neigbori))
            # in case of kNeighbor > originDim
            Qi = Qi + np.eye(self.kNeighbor)*self.tol*np.trace(Qi)
            QiInv = np.linalg.pinv(Qi)
            wi = np.dot(QiInv, I)/(np.dot(np.dot(I.T, QiInv), I)[0, 0])
            w[:, ii] = wi[:, 0]

        # get W matrix based on w matrix
        self.W = np.zeros((self.numSample, self.numSample))
        for ii in range(self.numSample):
            for jj in range(self.kNeighbor):
                self.W[self.neighborIndexMat[ii][jj], ii] = w[jj, ii]

    # function to map the original data into embedding coordinates
    def embed(self):
        IW = np.eye(self.numSample)
        M = np.dot((IW-self.W), (IW-self.W).T)
        eigenVal, eigenVec = np.linalg.eig(M)
        vecIndex = np.argsort(eigenVal)[1: self.targetDim + 1]
        self.lowX = eigenVec[:, vecIndex]

    # * function to transform X to low-dimension
    def transform(self):
        # select neighbor
        self.selectNeighbor()

        # choose toleration
        self.chooseTol()

        # Reconstructing with linear weights
        self.reconstruct()

        # Mapping into embedding coordinates
        self.embed()
        return self.lowX
