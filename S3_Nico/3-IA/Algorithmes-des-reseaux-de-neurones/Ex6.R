library(e1071)
library(nnet)
library(randomForest)
library(rpart)
library(rpart.plot)

#Get data
spamdata = read.table("spambase.data",header =F,sep=",")
#Transform data
spamdata$V58=as.factor(spamdata$V58)
levels(spamdata$V58)=c("non spam","spam")
#Check data transformed
prop.table(table(spamdata$V58))

#Make train and test dataset
n=nrow(spamdata)
ntrain=floor(2*n/3)
indextrain = sample(1:n,ntrain,replace=F)
train=spamdata[indextrain,]
test=spamdata[-indextrain,]

#Center variables, save the mean and standard deviation
meantrain = apply(train[,1:57],2,mean)
sdtrain = apply(train[,1:57],2,sd)
train[,1:57] = scale(train[,1:57])

#Some saved commands
    #modelsave = model
    #model = tune.nnet(V58~., data=train,size=2:5,decay=c(0,0.1,1),maxit=100)
    #model = nnet(V58~., data=train,size=5,decay=0.1,maxit=100)

#Model calculation
  #Neural network
model = tune.nnet(V58~., data=train,size=5,decay=0.1,maxit=100)
summary(model)

  #Random Forests
rf <- tune.randomForest(V58~.,data=train,ntree = 200, mtry = 2, importance = TRUE)
print(rf$best.model)
importance(rf$best.model)
varImpPlot(rf$best.model)

  #Tree
tree <- tune.rpart(V58~.,data=train)
prp(tree$best.model)


#Prediction error
  #Neural network
MatConfnn = table(train$V58,predict(modelsave$best.model,train,type="class"))
tbnn = 1-sum(diag(MatConfnn)/sum(MatConfnn))
print(paste("Prediction error neural network :",tbnn))
  #Random forests
MatConfrf = table(train$V58,predict(rf$best.model,train,type="class"))
tbrf = 1-sum(diag(MatConfrf)/sum(MatConft))
print(paste("Prediction error random forests :",tbrf))
  #Tree
MatConft = table(train$V58, predict(tree$best.model, train, type="class"))
tbt = 1-sum(diag(MatConft)/sum(MatConft))
print(paste("Prediction error tree :",tbt))
