library(nnet)
library(rgl)
library(NeuralNetTools)

x1 = runif(2000,-0.5,0.5)
x2 = runif(2000,0,1)

Y = 0.1*x2 > x1^2
Y = Y+1
plot(x1,x2,col=Y)

data = data.frame(x1,x2,Y)
data$Y = as.factor(data$Y)

#centrer réduire
#data[,1:2] = scale(data[,1:2])


# NN
NN = nnet(Y~.,data=data,size=2,maxit=1000)
#NNsave = NN
#current NNsave : final value 1.588191

poidsZ1=NN$wts[1:3] # poids du 1er neuronne
poidsZ2=NN$wts[4:6] # poids du 2eme neuronne

abline(-poidsZ1[1]/poidsZ1[3],-poidsZ1[2]/poidsZ1[3],col="blue",lwd=5)
abline(-poidsZ2[1]/poidsZ2[3],-poidsZ2[2]/poidsZ2[3],col="purple",lwd=5)

sigma1 = poidsZ1[1] + poidsZ1[2]*x1 + poidsZ1[3]*x2
sigma2 = poidsZ2[1] + poidsZ2[2]*x1 + poidsZ2[3]*x2

Z1 = 1/(1+exp(-sigma1))
Z2 = 1/(1+exp(-sigma2))

poidsY = NN$wts[7:9]

plot(Z1,Z2,col=Y)

abline(-poidsY[1]/poidsY[3],-poidsY[2]/poidsY[3],col="cyan",lwd=5)


#Redo with size=3

NN = nnet(Y~.,data=data,size=3,maxit=1000)
NN$wts
plotnet(NN)

plot(x1,x2,col=Y)
abline(-poidsH1[1]/poidsH1[3],-poidsH1[2]/poidsH1[3],col="blue",lwd=5)
abline(-poidsH2[1]/poidsH2[3],-poidsH2[2]/poidsH2[3],col="purple",lwd=5)
abline(-poidsH3[1]/poidsH3[3],-poidsH3[2]/poidsH3[3],col="cyan",lwd=5)

plot3d(x1,x2,col=Y)

poidsH1 = NN$wts[1:3]
poidsH2 = NN$wts[4:6]
poidsH3 = NN$wts[7:9]

sig1 = poidsH1[1] + poidsH1[2]*x1 + poidsH1[3]*x2
sig2 = poidsH2[1] + poidsH2[2]*x1 + poidsH2[3]*x2
sig3 = poidsH3[1] + poidsH3[2]*x1 + poidsH3[3]*x2

H1 = 1/(1+exp(-sig1))
H2 = 1/(1+exp(-sig2))
H3 = 1/(1+exp(-sig3))

plot3d(H1,H2,H3,col=Y)
