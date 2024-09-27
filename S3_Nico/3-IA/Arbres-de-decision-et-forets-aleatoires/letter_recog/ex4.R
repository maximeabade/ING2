require(randomForest)
data(iris)

summary(iris)


iris.rf <- randomForest(Species~.,data=iris)
print(iris.rf)


#oob : out of bag
print(iris.rf$oob.times[1:10])

sous_echant=c(25,75,135)
sous_echant
iris$Species[sous_echant]
iris.rf$oob.times[sous_echant]
iris.rf$votes[sous_echant,]


m=margin(iris.rf)
print(m[sous_echant]) 


print(iris.rf$predicted[1:10])
table(iris$Species, iris.rf$predicted)
iris.rf$confusion


#calcul du taux d'erreur
error_rate=1-sum(diag(iris.rf$confusion))/sum(iris.rf$confusion)
print(error_rate)


file=read.table("Species_to_predict.csv",header=TRUE,sep=";")

predicted=predict(iris.rf,file)
print(predicted[1:5])
iris.rf$importance
varImpPlot(iris.rf)
iris.rf=randomForest(iris[,1:4], iris$Species, ntree=5000) 
plot(iris.rf$err.rate[,1], type="l")
iris.rf2=randomForest(iris[,1:4], iris$Species, sampsize=140) 
iris.rf3=randomForest(iris[,1:4], iris$Species, maxnodes=5) 