TenFoldCV_NN <- function(data, labels, folds){
  # seleziono gli attributi nel dataset per creare la formula f
  n = names(data)
  hiddenLayer = ifelse(length(n)==11, 4, 3)
  f = as.formula(paste("good + bad ~", paste(n[!n %in% "quality"], collapse = " + ")))

  # train di una nn con una 10-fold cross validation
  pbar <- create_progress_bar('text')
  pbar$init(10)
  # Viene trainato un modello per ogni fold creata
  cv = lapply(folds, function(x) {
    training_fold = data[-x, ]
    test_fold = data[x, ]
    label_fold = labels[-x]
    testLabel_fold = labels[x]

    # fit the model
    training_fold = as.data.frame(training_fold)
    training_fold$good = label_fold==1
    training_fold$bad = label_fold==0
    # nn fit
    start = Sys.time()
    nn = neuralnet(f, training_fold, hidden = hiddenLayer, linear.output = T)
    end = Sys.time()
    print(end-start)
    # nn pred
    y_pred = predict(nn, test_fold)
    y_pred.prediction = c("good", "bad")[apply(y_pred, 1,which.max)]
    # estrapola le singole conf mat
    cm = table(testLabel_fold, y_pred.prediction)
    # roc
    roc = roc(testLabel_fold, as.numeric(as.factor(y_pred.prediction)))
    
    pbar$step()
    return(list(cm, roc, nn))
  })
  
  # select the best nn
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
  #NNs
  NNs = lapply(cv, function(x){return(x[[3]])})
  #plot(NNs[[xx]])
  #print(NNs[[xx]])
  # analisi Generalized weight
  #for (i in 1:length(n))
  #  gwplot(NNs[[xx]], selected.covariate = n[i])
  
  #ROC(k)s
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
  
  return(list(TotalConfusionMatrix, VectorofMeasure, roc , NNs[[xx]]))
}