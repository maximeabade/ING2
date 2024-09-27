source("prepDataTitanic.r")

#Building the Rformula

ind <- sample(2, nrow(train), replace=T, prob=c(0.7, 0.3)) 
dataset.train <- train[ind==1, ] 
dataset.test <- train[ind==2, ]

formula <- Survived~Pclass+Sex+Title+AgeGroup+Family+FareGroup+Cabin2

library(randomForest)


rf <- randomForest(formula, data = dataset.train)

pred <- predict(rf,newdata=dataset.test)

confTest <- table(pred,dataset.test$Survived)
confOOB <- rf$confusion

accTest <- (confTest[1,1]+confTest[2,2])/(confTest[1,1]+confTest[1,2]+confTest[2,1]+confTest[2,2])
accOOB <- (confOOB[1,1]+confOOB[2,2])/(confOOB[1,1]+confOOB[1,2]+confOOB[2,1]+confOOB[2,2])
cat("ntree = ",rf$ntree," mtry = ",rf$mtry,", Accuracy = ",accOOB,",",accTest,"\n")


#Extract a tree

getTree(rf,2, labelVar=T)

#Functions we need

#This function checks if the right part contains some variable

containsThisVariable <- function(v, myRule)
{
  if (length(grep(v,myRule))>0)
    return(TRUE)
  else
    return(FALSE)
}

containsTheseVariables <- function(lv, myRule)
{
   for (num in 1:length(lv))
   {
     if (containsThisVariable(lv[num], myRule)==FALSE)
	   return(FALSE)
   }
   return(TRUE)
 }


#Extracting rules from the forest

library(inTrees)


#Trnasform the RF into a list

treeList <- RF2List(rf)
X <- dataset.train[,c(3,5,13,14,15,16,17)]
ruleExec <- extractRules(treeList,X,ntree=rf$ntree)
ruleExec <- unique(ruleExec)
ruleMetric <- getRuleMetric(ruleExec,X,dataset.train$Survived)
varnames <- c("Pclass","Sex","Title","AgeGroup","Family","FareGroup","Cabin2")
readableRules <- presentRules(ruleMetric, varnames)
nbRules <- dim(readableRules)[1]
cat(nbRules," rules extracted.","\n")


minFreq <- 0.1
maxErr <- 0.2
#Put in this table the variables you want to have in the rules
wantedVariables=c("Sex")

nr<- 0
for(numRule in 1:nbRules)
{
  if ((as.numeric(readableRules[numRule,2])>=minFreq)&(as.numeric(readableRules[numRule,3])<maxErr)
            &(containsTheseVariables(wantedVariables,readableRules[numRule,4])==TRUE))
  {
    nr<- nr+1
    cat(nr,":",readableRules[numRule,4]," --> ",readableRules[numRule,5],"\n")
  }
}

