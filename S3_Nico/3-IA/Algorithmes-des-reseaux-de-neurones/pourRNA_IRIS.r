library(nnet)

#Scale Iris Data

normalize <- function(x)
{
  return((x-min(x))/(max(x)-min(x)))
}

iris2 <- as.data.frame(lapply(iris[,c(1,2,3,4)], normalize))

iris2$Species = NULL
for (i in 1:nrow(iris2))
  iris2[i, 'Species']=iris[i, 'Species']
#Build

set.seed(123) 
ind <- sample(2, nrow(iris), replace=T, prob=c(0.7, 0.3)) 
iris.train <- iris2[ind==1, ] 
iris.test <- iris2[ind==2, ]


