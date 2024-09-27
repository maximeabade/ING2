library(rpart)
library(rpart.plot)
data(ptitanic)

lapply(ptitanic,class)

ptitanicTree <- rpart(survived~.,data=ptitanic)
ptitanicTree <- rpart(survived~.,data=ptitanic,control=rpart.control(minsplit=5,cp=0))

ptitanicSimple <- prune(ptitanicTree,cp=0.0047)
ptitanicOptimal <- prune(ptitanicTree,cp=ptitanicTree$cptable[which.min(ptitanicTree$cptable[,4]),1])

plotcp(ptitanicOptimal)


prp(ptitanicOptimal,extra=2)
prp(ptitanicTree,extra=2)

table(ptitanic$survived, predict(ptitanicOptimal, ptitanic, type="class"))

help(rpart)


tree2 = prune(ptitanicTree,cp=0.0047)
prp(tree2)

predict(tree2,ptitanic[1:5,],type="class")

MatConf = table(ptitanic$survived, predict(tree2, ptitanic, type="class"))

tb = sum(diag(MatConf))/nrow(ptitanic)
tb
te = 1-tb
te
diag(MatConf)/apply(MatConf,1,sum)
####################################################################################################################

data(iris)
lapply(iris,class)

n = nrow(iris)
ntrain = floor(2*n/3)
ntest = n - ntrain

indextrain = sample(1:n,ntrain,replace=FALSE)

train = iris[indextrain,]
test = iris[-indextrain,]

irisTree <- rpart(Species~.,data=train)

prp(irisTree, extra = 2)
plotcp(irisTree)

prev = predict(irisTree, train,type="class")
MatConf=table(train$Species,prev)
print(MatConf)
tb.classes = diag(MatConf)/apply(MatConf,1,sum)
print(tb.classes)
tb = sum(diag(MatConf))/ntrain
print(tb)


prev = predict(irisTree, test,type="class")
MatConfTest=table(test$Species,prev)
print(MatConfTest)
tbTest.classes = diag(MatConfTest)/apply(MatConfTest,1,sum)
print(tbTest.classes)
tbTest = sum(diag(MatConfTest))/ntest
print(tbTest)





















