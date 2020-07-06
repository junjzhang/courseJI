library(quantmod)
library(forecast)
library(tseries)

#data process
##train data
getSymbols("TSLA",src="yahoo",from = "2016-11-18", to = '2019-11-25')
TSLA.df = data.frame(TSLA)
TSLA.df$Close.Date = as.Date(row.names(TSLA.df))
close.ts = ts(TSLA.df$TSLA.Close)
log_close.ts = ts(log(TSLA.df$TSLA.Close))
##test data
getSymbols("TSLA",src="yahoo",from = "2019-11-26", to = '2019-12-04')
TSLA.test.df = data.frame(TSLA)
test.data = TSLA.test.df$TSLA.Close

#model
model.sea = arima(close.ts,order = c(0,1,0),seasonal = list(order=c(2,1,1),period=100))
model.sea.fc = forecast(model.sea, h=7, level = c(99.5))
error.sea = abs(test.data-as.numeric(model.sea.fc$mean))/test_data
print(mean(error.sea))

#plot
x = as.Date(c("2019-11-19","2019-11-20","2019-11-21","2019-11-22","2019-11-25","2019-11-26", "2019-11-27"))
y_predict = model.sea.fc$mean
plot(x,test.data, type = "l", col = "lightblue3", xlab = "date", ylab = "stock price at close ($)", font.axis = 15, lwd = 3)
points(x,test.data,col = "lightblue3",pch = 16,  cex = 2)
lines(x,y_predict,col = 'lightcoral', lwd = 3)
points(x,y_predict,col = 'lightcoral',pch = 16, cex = 2)
legend(x=as.Date("2019-11-19"),y=335,legend=c("prediction value","actual value"),col=c('lightcoral',"lightblue3"),lty = 1, pch = 16,cex = 2,lwd=3)

#fit plot
plot(TSLA.df$Close.Date,fitted.values(model.sea),type = "l",col = 'blue')
lines(TSLA.df$Close.Date,close.ts, col = 'red')

#diagnoistic plot
attach(mtcars)
layout(matrix(c(1,1,2,3), 2, 2, byrow = TRUE))
plot(TSLA.df$Close.Date[100:length(TSLA.df$Close.Date)],model.sea.fc$residuals[100:length(TSLA.df$Close.Date)],xlab = "date", ylab = "residuals")
qqnorm(model.sea.fc$residuals)
qqline(model.sea.fc$residuals,col = 'red')
residual = model.sea.fc$residuals[-1]
residual_lag = model.sea.fc$residuals[-length(model.sea.fc$residuals)]
plot(residual_lag,residual,xlab = "previous", ylab = "residuals")
for(i in 1:6) {
  print(Box.test(model.sea.fc$residuals,type = "Ljung-Box",lag=i))
}
for(i in 1:6) {
  print(Box.test(model.sea.fc$residuals^2,type = "Ljung-Box",lag=i))
}
