

ech1 = read.table("Ech1.txt",header=T,sep="")
ech2 = read.table("Ech2.txt",header=T,sep="")
ech3 = read.table("Ech3.txt",header=T,sep="")
ech4 = read.table("Ech4.txt",header=T,sep="")
ech5 = read.table("Ech5.txt",header=T,sep="")



mean(ech1)
sd(ech1)
boxplot(ech1)
hist(ech1)
t.test(ech1,mu=0.5,alternative="greater")

mean(ech2)
sd(ech2)
boxplot(ech2)
hist(ech2)
t.test(ech2,mu=0.5,alternative="greater")

mean(ech3)
sd(ech3)
boxplot(ech3)
hist(ech3)
t.test(ech3,mu=0.5,alternative="greater")

mean(ech4)
sd(ech4)
boxplot(ech4)
hist(ech4)
t.test(ech4,mu=0.5,alternative="greater")

mean(ech5)
sd(ech5)
boxplot(ech5)
hist(ech5)
t.test(ech5,mu=0.5,alternative="greater")