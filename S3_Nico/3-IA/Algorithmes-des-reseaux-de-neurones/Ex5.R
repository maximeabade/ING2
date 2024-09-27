data("iris")

help(nnet)

#scale <- pour centrer réduire

apply(iris[,1:4],2,mean)
apply(iris[,1:4],2,var)

iris[,1:4] = scale(iris[,1:4])
apply(iris[,1:4],2,mean)
apply(iris[,1:4],2,var)

#question 1.b

model1 = nnet(Species~., data=iris, size=5)
#43 poids à ajuster : (4+1)*5 + (5+1)*3 = 43

#question 2

model2 = nnet(Species~., data=iris, size=2, maxit = 1000)
plotnet(model2)

summary(model2)

#question 4

model3bis = tune.nnet(Species~., data=iris,size=2:10,decay=c(0,0.1,1,2,3),maxit=100)
summary(model3bis)
plotnet(model3$best.model)
