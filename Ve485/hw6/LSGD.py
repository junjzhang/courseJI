import numpy.random as rand
import numpy as np


'''
 * Use L-2 Norm in this program
 * Use backtracking search to choose step
'''


# Generate data as requred
def dataGenerate(dim=1000, size=50, withNoise=False):
    # Generate x with mean 0 variation 1
    x = rand.standard_normal(dim)
    # Generate A with mean 0 variation 1
    A = np.array([rand.standard_normal(dim) for ii in range(size)])
    # Calculate b
    if withNoise:
        # Calculate b with noise N(0,0.001)
        b = A@x + rand.standard_normal(size)*0.1
    else:
        b = A@x
    # calulate optimal x with analycal solution
    xHat = A.transpose()@np.linalg.inv(A@A.transpose())@b
    return A, b, xHat


# Generate inital x
def xInitialize(low=-5, high=5, dim=1000):
    return rand.rand(dim)*rand.randint(low=low, high=high, size=dim)

# Calculate the value of ||Ax-b||


def fun(x, A, b):
    return np.linalg.norm(A@x-b)


# Calculate the gradient
def gradient(x, A, b):
    return 2*A.transpose()@(A@x-b)


# Use backtracking search to choose t
def chooseT(x, A, b, dir, alpha=0.001, beta=0.6):
    t = 1
    while (fun(x+t*dir, A, b) > (fun(x, A, b)-alpha*t*dir.transpose()@dir)):
        t = beta*t
    return t


def gradientDecent(x, xHat, A, b):
    dir = np.zeros(np.size(x))+1
    while (np.linalg.norm(dir, ord=2) >= 1e-11):
        # Calculate decent direction
        dir = - gradient(x, A, b)
        # choose t
        t = chooseT(x, A, b, dir)
        # Update x
        x = x+t*dir
    return x


def info(ii, xInit, xHatGD, xHat, funValueGD, funValueSV):
    print("***The algorithm start at #%d starting point***" % (ii+1))
    # print(xInit)
    print("The distance between xHatGD and xHat is %g" %
          np.linalg.norm(xHatGD-xHat, ord=2))
    print("f(xHatGD) = %g, and the difference between f(xHatGD) and f(xHat) is %g" % (
        funValueGD, abs(funValueGD-funValueSV)))
    return


if __name__ == "__main__":
    print("*******Without noise*******")
    A, b, xHat = dataGenerate()
    # start at for different starting points
    for ii in range(4):
        x = xInitialize()
        xHatGD = gradientDecent(x, xHat, A, b)
        info(ii, x, xHatGD, xHat, fun(xHatGD, A, b), fun(xHat, A, b))
    print("*******With noise*******")
    A, b, xHat = dataGenerate(withNoise=True)
    # start at for different starting points
    for ii in range(4):
        x = xInitialize()
        xHatGD = gradientDecent(x, xHat, A, b)
        info(ii, x, xHatGD, xHat, fun(xHatGD, A, b), fun(xHat, A, b))
