Mydata=read.table("./Letters/letter-recognition.data", header = F, sep=",")
Mydata$V1=as.factor(Mydata$V1)
#REPRESENTATION ET VERIFICATION DES CLASSES EQUILIBREES
pie(table(Mydata$V1))
# BASE TRAIN ET VALIDATION
n=nrow(Mydata)
ntrain=(floor(2*n/3))
index=sample(1:n, ntrain,replace=F)
train=Mydata[index,]
validation=Mydata[-index,]

library(rpart)
library(rpart.plot)
# ARBRE GENERE PAR RSTUDIO
arbreR=rpart(V1~.,train)
prp(arbreR)


#ARBRE GENERE NOUS MEMES
arbreH=rpart(V1~.,train,control=rpart.control(cp=0,minbucket = 30))
plotcp(arbreH)
arbreH=prune(arbreH,cp=0.0082)
plotcp(arbreH)
arbreH=prune(arbreH,cp=0.018)
prp(arbreR)
prp(arbreH)

#Comparaison des deux arbres

prevR=predict(arbreR,validation,type="class")
MatconfR=table(prevR,validation$V1)
tbR=sum(diag(MatconfR)) / sum(MatconfR)











