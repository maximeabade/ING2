library(rpart)
library(rpart.plot)

myData = read.table("Test_Classif_dpt.txt",header=T)

plot(myData$X1,myData$X2,col=myData$Y)
myData$Y =as.factor(myData$Y)

tree <- rpart(Y~.,data=myData,control=rpart.control(minsplit=5,cp=0))
prp(tree,extra=2)


myData = read.table("Test_Classif_Correl.txt",header=T)

plot(myData$X1,myData$X2,col=myData$Y)
myData$Y =as.factor(myData$Y)

tree <- rpart(Y~.,data=myData,control=rpart.control(minsplit=5,cp=0))
prp(tree,extra=2)
