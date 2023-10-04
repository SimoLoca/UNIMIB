TenFoldCV_SVM <- function(data, labels, folds){
  # train di una svm con una 10-fold cross validation
  pbar <- create_progress_bar('text')
  pbar$init(10)
  # Viene trainato un modello per ogni fold creata
  cv = lapply(folds, function(x) {
    training_fold = data[-x, ]
    test_fold = data[x, ]
    label_fold = labels[-x]
    testLabel_fold = labels[x]
    start = Sys.time()
    svm = svm(training_fold, label_fold,
                     type = 'C-classification',
                     kernel = 'radial')
    end = Sys.time()
    print(end-start)
    y_pred = predict(svm, newdata = test_fold)
    # estrapola le singole conf mat
    cm = table(testLabel_fold, y_pred)
    # roc
    roc = roc(testLabel_fold, as.numeric(y_pred))
   
    pbar$step()
    return(list(cm, roc, svm))
  })
  
  # select the best svm
  bestAcc = 0
  xx = 0
  for (i in 1:10) {
    c = cv[[i]][[1]]
    Accuracy = (c[2,2] + c[1,1]) / (c[2,2] + c[1,1] + c[1,2] + c[2,1])
    if (Accuracy > bestAcc) {
      bestAcc = Accuracy
      xx = i
    }
  }
  #SVMs
  SVMs = lapply(cv, function(x){return(x[[3]])})
  
  # ROC(k)s
  ROCKS = lapply(cv, function(x){return(x[[2]])})
  
  # calcolo confusion matrix totale
  TotalConfusionMatrix= cv[[1]][[1]]
  for (i in 2:10)
    TotalConfusionMatrix = TotalConfusionMatrix + cv[[i]][[1]]
  TP = TotalConfusionMatrix[2,2] #TP true positive
  FP = TotalConfusionMatrix[1,2] #FP false positives 
  TN = TotalConfusionMatrix[1,1] #TN true negatives 
  FN = TotalConfusionMatrix[2,1] #FN false negatives
  # calcolo accuracy (TP + TN) / (TP + TN + FP + FN)
  Accuracy = (TP + TN) / (TP + TN + FP + FN)
  # calcolo precision 
  Precision = TP / (TP+FP)
  # calcolo recall
  Recall = TP / (TP+FN)
  # calcolo f-measure
  FMeasure = (2 * Precision * Recall) / (Precision + Recall)
  
  VectorofMeasure = c(Accuracy, Precision, Recall, FMeasure)
  names(VectorofMeasure) = c("Accuracy", "Precision", "Recall", "F-measure")
  
  sensitivity = lapply(ROCKS, function(x){return (x[[2]])})
  specificities = lapply(ROCKS, function(x){return (x[[3]])})
  auc = lapply(ROCKS, function(x){return (x[[9]])})
  sensitivity <- colMeans(matrix(unlist(sensitivity), ncol = 3, byrow = TRUE))
  specificities <- colMeans(matrix(unlist(specificities), ncol = 3, byrow = TRUE))
  auc <- colMeans(matrix(unlist(auc), ncol = 1, byrow = TRUE))
  df <- data.frame(sensitivity, specificities)
  roc =  list(df, auc)
  
  return(list(TotalConfusionMatrix, VectorofMeasure, roc, SVMs[[xx]]))
}
