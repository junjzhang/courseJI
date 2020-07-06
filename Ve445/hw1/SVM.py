# This is the template of VE445 JI 2019 Fall Assignment 1
# Name: Junjie ZHANG
#   ID:517021911128
# Date: Oct 15th, 2019

import numpy as np

class SVM(object):
    # This class is the hard margin SVM and it is the parent
    # class of KernelSVM and SoftMarginSVM.
    def __init__(self, sample, label):
        self.sample = sample
        self.label = label
        
    def training(self):
    # Start training
        self.train()
        return
    
    def train(self, max_passes = 1, tol = 0):
        #define some useful parameters
        self.n = self.sample.shape[0]
        self.m = self.sample.shape[1]
        self.label = self.label.reshape(self.n,1)
        self.tol = tol
        
        #calculate alpha
        self.SMO(max_passes)
        
        #calculate paramter
        #only valid for non-kernel one
        self.w = np.sum((self.alpha*self.label*self.sample),axis = 0).reshape(self.m,1)
        return
    
    def testing(self, test_sample, test_label):
    # This function should return the accuracy 
    # of the input test_sample in float64
        
        prediction = self.predict(test_sample)
        accuracy = np.sum((prediction == test_label.reshape(test_sample.shape[0],1)).astype(float))/test_sample.shape[0]
        return accuracy
    
    def parameter_w(self):
    # This function is used to return the parameter w of the SVM.
        return self.w 
    
    def parameter_b(self):
    # This function is used to return the parameter b of the SVM.
        return self.b  

    def E(self,i):
    #calculate the error of X_i
        result = 0
        for jj in range(self.n):
            result += self.alpha[jj,0]*self.label[jj,0]*self.K(self.sample[jj,].reshape(self.m,1),self.sample[i,].reshape(self.m,1))
        result += self.b - self.label[i,0]
        return result
        
    def K(self,a,b):
    #Kerneal
        a = a.reshape(self.m,1)
        b = b.reshape(self.m,1)
        return a.T@b
        
    def predict(self,x):
    #Predict the y based on x
        result = np.zeros((x.shape[0],1))
        for ii in range(x.shape[0]):
            predict_value = 0
            for jj in range(self.n):
                predict_value += self.alpha[jj,0]*self.label[jj,0]*self.K(self.sample[jj,],x[ii,])
            result[ii,0] = (1 if predict_value+self.b>0 else -1)
        return result

    def choose_boundary(self,ii,jj):
        if (self.label[ii]==self.label[jj]):
            L = 0
            H = self.alpha[ii,0]+self.alpha[jj,0]
        else:
            L = max(self.alpha[jj,0]-self.alpha[ii,0],0)
            H = float("inf")
        return L,H
    
    def judge(self,ii,Eii):
        return self.label[ii]*Eii<self.tol
    
    def update_b(self,ii,jj,b1,b2):
        if (self.alpha[jj,0]>0):
            self.b = b2
        elif (self.alpha[ii,0]>0):
            self.b = b1
        else:
            self.b = (b1+b2)/2
    
    def SMO(self,max_passes):
        passes = 0
        self.alpha = np.zeros((self.n,1))
        self.b = 0
        while (passes<max_passes):
            alphas_changed = 0
            for ii in range(self.n):
                Eii = self.E(ii)
                if (self.judge(ii,Eii)):
                    jj = np.random.choice(self.n,1,replace = False)
                    while(jj == ii):
                        jj = np.random.choice(self.n,1,replace = False)
                    Ejj = self.E(jj)
                    alpha_old_ii = self.alpha[ii,0]
                    alpha_old_jj = self.alpha[jj,0]
                    L,H = self.choose_boundary(ii,jj)
                    if (L==H):
                        continue
                    Kiijj = self.K(self.sample[ii,],self.sample[jj,])
                    Kii = self.K(self.sample[ii,],self.sample[ii,])
                    Kjj = self.K(self.sample[jj,],self.sample[jj,])
                    eta = 2*Kiijj-Kii-Kjj
                    if (eta >= 0):
                        continue
                    alpha_new_jj = alpha_old_jj-self.label[jj,0]*(Eii-Ejj)/eta
                    if (alpha_new_jj > H):
                        self.alpha[jj,0] = H
                    elif (alpha_new_jj < L):
                        self.alpha[jj,0] = L
                    else:
                        self.alpha[jj,0] = alpha_new_jj
                    if(abs(alpha_old_jj-alpha_new_jj)<1e-5):
                        continue
                    
                    self.alpha[ii,0] += self.label[ii,0]*self.label[jj,0]*(alpha_old_jj-self.alpha[jj,0])
                    
                    b1 = self.b - Eii - self.label[ii,0]*(self.alpha[ii,0]-alpha_old_ii)*Kii-self.label[jj,0]*(self.alpha[jj,0]-alpha_old_jj)*Kiijj
                    b2 = self.b - Ejj - self.label[ii,0]*(self.alpha[ii,0]-alpha_old_ii)*Kiijj-self.label[jj,0]*(self.alpha[jj,0]-alpha_old_jj)*Kjj
                    self.update_b(ii,jj,b1,b2)
                    alphas_changed += 1
            if(alphas_changed == 0):
                passes += 1
            else:
                passes = 0


class KernelSVM(SVM):
    # This class is the kernel SVM.
    
    def training(self, kernel = 'Linear', parameter = 1):
    # Specifics:
    #   For the parameter of 'kernel':
    #   1. The default kernel function is 'Linear'.
    #      The parameter is 1 by default.
    #   2. Gaussian kernel function is 'Gaussian'.
    #      The parameter is the Gaussian bandwidth.
    #   3. Laplace kernel funciton is 'Laplace'.
    #   4. Polynomial kernel functino is 'Polynomial'.
    #      The parameter is the exponential of polynomial.
    # Add your code after the initialization.
        self.kernel = kernel
        self.parameter = parameter
    # Start training
        self.train()
        return
    
    def K(self,a,b):
        a = a.reshape(self.m,1)
        b = b.reshape(self.m,1)
        
        if (self.kernel == "Linear"):
            return a.T@b
        if (self.kernel == "Gaussian"):
            return np.exp(-((a-b).T@(a-b))/(2*(self.parameter)**2))
        if (self.kernel == "Laplace"):
            return np.exp(-(np.sum(np.abs(a-b)))/(2*(self.parameter)**2))
        if (self.kernel == "Polynomial"):
            return (a.T@b)**self.parameter


class SoftMarginSVM(KernelSVM):
    # This class is the soft margin SVM and inherits
    # the kernel SVM to expand to both linear Non-seperable and
    # soft margin problem.
    
   def training(self, kernel = 'Linear', parameter = 1):
    # Specifics:
    #   For the parameter of 'kernel':
    #   1. The default kernel function is 'Linear'.
    #      The parameter is 1 by default.
    #   2. Gaussian kernel function is 'Gaussian'.
    #      The parameter is the Gaussian bandwidth.
    #   3. Laplace kernel funciton is 'Laplace'.
    #   4. Polynomial kernel functino is 'Polynomial'.
    #      The parameter is the exponential of polynomial.
    # Add your code after the initialization.
        self.C = 1
        self.kernel = kernel
        self.parameter = parameter
        tol = 0.3
    # Start training
        self.train(tol=tol)
        return 
    
   def choose_boundary(self,ii,jj):
        if (self.label[ii]!=self.label[jj]):
            L = max(self.alpha[jj,0]-self.alpha[ii,0],0)
            H = min(self.alpha[jj,0]-self.alpha[ii,0]+self.C,self.C)
        else:
            L = max(self.alpha[ii,0]+self.alpha[jj,0]-self.C,0)
            H = min(self.alpha[ii,0]+self.alpha[ii,0],self.C)
        return L,H
    
   def judge(self,ii,Eii):
        return (self.label[ii,0]*Eii < -self.tol)
    
   def update_b(self,ii,jj,b1,b2):
        if (self.alpha[jj,0]>0 and self.alpha[jj,0]<self.C):
            self.b = b2
        elif (self.alpha[ii,0]>0 and self.alpha[ii,0]<self.C):
            self.b = b1
        else:
            self.b = (b1+b2)/2
            
    