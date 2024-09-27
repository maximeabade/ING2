library(randomForest)

letters = read.table("letter-recognition.data",sep=",",col.names = c("lettr","x-box","y-box","width","high" ,"onpix"	,"x-bar"	,"y-bar"	,"x2bar","y2bar"	,"xybar","x2ybr"	,"xy2br","x-ege"	,"xegvy","y-ege"	,"yegvx"))
lapply(letters,class)

n = nrow(letters)
ntrain = floor(2*n/3)
ntest = n - ntrain

indextrain = sample(1:n,ntrain,replace=FALSE)

train = letters[indextrain,]
test = letters[-indextrain,]

rf <- randomForest(lettr~.,train,ntree = 500, mtry = 4, importance = TRUE) #mtry environ égal à racine(nombres de colonnes)

plot(rf$err.rate[,1],type="l")
varImpPlot(rf)
print(rf)
importance(rf)


prev = predict(rf, train,type="class")
MatConf=table(train$lettr,prev)
print(MatConf)
tb.classes = diag(MatConf)/apply(MatConf,1,sum)
print(tb.classes)
tb = sum(diag(MatConf))/ntrain
print(tb)

prev = predict(rf, test,type="class")
MatConf=table(test$lettr,prev)
print(MatConf)
tb.classes = diag(MatConf)/apply(MatConf,1,sum)
print(tb.classes)
tb = sum(diag(MatConf))/(n - ntrain)
print(tb)

