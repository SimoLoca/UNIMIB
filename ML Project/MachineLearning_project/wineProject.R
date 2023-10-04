library("rstudioapi")
library("e1071")
library("caret")
library("pROC")
library(plyr) 
library(neuralnet)
setwd(dirname(getActiveDocumentContext()$path))
source('TenFoldCV_SVM.R')
source('TenFoldCV_NN.R')

# import del dataset 
wine <- read.csv("winequality-red.csv")
dataset <- wine[, 1:11]
dataset$residual.sugar <- NULL
dataset$pH <- NULL
dataset$fixed.acidity <- NULL
dataset$free.sulfur.dioxide <- NULL

# trasformazione del problema multiclasse in binario
quality = ifelse(wine$quality >= 6, 1, 0)

# PCA
#res <-prcomp(data.matrix(dataset, rownames.force = NA), scale.=TRUE, center = TRUE)
#eigvectors <- res$rotation[, 1:5]
#dataset.pca <- data.matrix(dataset, rownames.force = NA)%*%eigvectors

# min-max scaling dei dataset
#for (i in 1:ncol(dataset.pca))
#  dataset.pca[,i]<- (dataset.pca[,i]-min(dataset.pca[,i]))/(max(dataset.pca[,i])-min(dataset.pca[,i]))
for (i in 1:ncol(dataset))
  dataset[,i]<- (dataset[,i]-min(dataset[,i]))/(max(dataset[,i])-min(dataset[,i]))

# 10fold CV su SVM e NN
set.seed(694)  # per ottenere risultati ripetibili e confrontabili
folds = createFolds(quality, k = 10)
cv.SVM = TenFoldCV_SVM(dataset, as.factor(quality), folds)
cv.NN = TenFoldCV_NN(dataset, quality, folds)

# Analisi risultati
ROCKS.SVM = cv.SVM[[3]]
df.svm <- ROCKS.SVM[[1]]
auc.svm <- unlist(ROCKS.SVM[[2]])

ROCKS.NN = cv.NN[[3]]
df.nn <- ROCKS.NN[[1]]
auc.nn <- unlist(ROCKS.NN[[2]])

ggplot(df.svm ,aes(x = 1-specificities, y = sensitivity ))+geom_line(size = 2, alpha = 0.7)+
  labs(x = "1-Specificity", y = "Sensitivity")+
  ggtitle(paste0('ROC Curve SVM', '(AUC = ', auc.svm, ')'))

ggplot(df.nn ,aes(x = 1-specificities, y = sensitivity ))+geom_line(size = 2, alpha = 0.7)+
  labs(x = "1-Specificity", y = "Sensitivity")+
  ggtitle(paste0('ROC Curve NN', '(AUC = ', auc.nn, ')'))

boxplot(df.nn$sensitivity, df.svm$sensitivity, names = c("NN", "SVM"), main = "Sensitivity")
boxplot(df.nn$specificities, df.svm$specificities, names = c("NN", "SVM"), main = "Specificities")





