tab=read.table("letter-recognition.data",header=F,sep=",")
tab$V1=as.factor(tab$V1)
# Bases apprentissage t test
n=nrow(tab)
ntrain=floor(2*n/3)
index=sample(1:n,ntrain,replace=FALSE)
train=tab[index,]
test=tab[-index,]

prop.table(table(tab$V1))
prop.table(table(train$V1))

# Random Forest
library(randomForest)
foret=randomForest(V1 ~.,data=train,importance=T,ntree=100)
print(foret)
plot(foret$err.rate[,1], type="l")

# Erreur ajustement
tb.aj=sum(diag(foret$confusion))/ntrain
print(tb.aj)

# Erreur de prévision
prev=predict(foret,test,type="class")
MatConf=table(test$V1,prev)
tb.test=sum(diag(MatConf))/nrow(test)

# Importance des variables
varImpPlot(foret)

# Comparaison arbre
library(rpart)
arbre=rpart(V1~.,train)
prp(arbre,extra=2)
prev=predict(arbre,test,type="class")
MatConf=table(test$V1,prev)
tb.test=sum(diag(MatConf))/nrow(test)