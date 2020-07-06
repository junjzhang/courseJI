#***********note that due to the bug in the package, 
#it may crash when step to the function predict, 
#you may try several times

#final model
if (!require("quantmod")) install.packages("quantmod")
library(quantmod)
if (!require("arfima")) install.packages("arfima")
library(arfima)

#data process
getSymbols("TSLA",src="yahoo",from = "2016-11-16")
TSLA.df = data.frame(TSLA)
date.final = as.Date(row.names(TSLA.df))[length(TSLA.df$TSLA.Close)]
close.ts = ts(TSLA.df$TSLA.Close)
if (date.final<as.Date("2019-12-06")){
  num_predict = as.numeric(as.Date("2019-12-06")-date.final)+5
} else if (date.final >= as.Date("2019-12-09")){
  num_predict = max(-as.numeric(date.final-as.Date("2019-12-09"))+4,0)
} else{
  num_predict = 5
}
#model
model = arfima::arfima(close.ts,order = c(0,1,0),seasonal = list(order = c(2,1,1),period = 100),cpus = 3)
#predict
result = predict(model,n.ahead = num_predict,predint = 0.5,cpus = 0)[[1]]$Forecast
if (num_predict < 5){
  result = c(TSLA.df$TSLA.Close[(length(TSLA.df$TSLA.Close)-(4-num_predict)):length(TSLA.df$TSLA.Close)],result)
} else if(num_predict > 5){
  result = result[(num_predict-4):num_predict]
} 
print(result)
#save model
write(result,file = "./group_3.txt",sep = "\n")