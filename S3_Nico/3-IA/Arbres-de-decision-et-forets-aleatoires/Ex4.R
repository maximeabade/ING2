library(randomForest)
library(rpart)
library(rpart.plot)

data(iris)
lapply(iris,class)

rf <- randomForest(Species~.,iris,ntree = 500, mtry = 2, importance = TRUE)

print(rf)
importance(rf)
varImpPlot(rf)

print(rf$oob.times[1:10])


sous_echant=c(25,75,135,115,4)
iris$Species[sous_echant]

rf$oob.times[sous_echant]

rf$votes[sous_echant,]

m=margin(rf)
print(m[sous_echant])
