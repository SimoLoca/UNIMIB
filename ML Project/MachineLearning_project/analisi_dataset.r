### Caricamento pacchetti/librerie
library(mlbench)
#install.packages("corrplot")
library(corrplot)
library(caret)
library(ggplot2)
setwd("~/R/MachineLearning_project")
dataset = read.csv("winequality-red.csv")

### Trasformazione variabile target per task di classificazione binario
dataset$quality = ifelse(dataset$quality >= 6, 1, 0)

### Normalizzazione dataset
for (i in 1:11){
  dataset[,i]<- (dataset[,i]-min(dataset[,i]))/(max(dataset[,i])-min(dataset[,i]))
}
x = dataset[, 1:11]   # Input Space
y = dataset[, 12]     # Output Space

### Analisi distribuzioni covariate rispetto alla variabile target
featurePlot(x, as.factor(y), plot="density", scales=list(x=list(relation="free"),
                                                         y=list(relation="free")),
            auto.key=list(columns=3))
### Plot per analizzare covariate rispetto al target
plot(x=dataset$fixed.acidity, y=dataset$volatile.acidity, col=as.factor(y))

### Matrice di correlazione
# per avere risultati ripetibili
set.seed(7)
# calcolo matrice di correlazione
correlationMatrix = cor(x)
### PLOT
corrplot(correlationMatrix, type = "upper", order = "original", 
         tl.col = "black", tl.srt = 45)

#analisi covariate a rischio eliminazione
pH.true <- dataset$pH[y == 1]
pH.false <- dataset$pH[y == 0]
chlorides.true <- dataset$chlorides[y == 1]
chlorides.false <- dataset$chlorides[y == 0]
residual.sugar.true <- dataset$residual.sugar[y == 1]
residual.sugar.false <- dataset$residual.sugar[y == 0]
free.sulfur.dioxide.true <- dataset$free.sulfur.dioxide[y == 1]
free.sulfur.dioxide.false <- dataset$free.sulfur.dioxide[y == 0]
matrix <- matrix(c(mean(pH.true), mean(pH.false), 
                   mean(chlorides.true), mean(chlorides.false),
                   mean(residual.sugar.true), mean(residual.sugar.false), 
                   mean(free.sulfur.dioxide.true), mean(free.sulfur.dioxide.false),
                   var(pH.true), var(pH.false),
                   var(chlorides.true), var(chlorides.false),
                   var(residual.sugar.true), var(residual.sugar.false),
                   var(free.sulfur.dioxide.true), var(free.sulfur.dioxide.false),
                   IQR(pH.true), IQR(pH.false),
                   IQR(chlorides.true), IQR(chlorides.false),
                   IQR(residual.sugar.true), IQR(residual.sugar.false),
                   IQR(free.sulfur.dioxide.true), IQR(free.sulfur.dioxide.false)),nrow=8, ncol=3)
rownames(matrix) <- c("pH 1", "pH 0",
                      "chlorides 1", "chlorides 0",
                      "residual sugar 1", "residual sugar 0",
                      "free sulfur dioxide 1", "free sulfur dioxide 0")
colnames(matrix) <- c("mean", "variance", "Inter quantil difference")

write.csv(matrix, file = "~/R/MachineLearning_project/values.csv")

#analisi tramite boxplot delle covariate correlate

x1 <- dataset[, c(1,3)]
boxplot(x1)
x2 <- dataset[, c(3,8)]
boxplot(x2)
x3 <- dataset[, c(6,7)]
boxplot(x3)
