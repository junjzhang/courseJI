library(quantmod)
library(forecast)
if (!require("fracdiff")) install.packages("fracdiff")
library(fracdiff)
library(tseries)
if (!require("fracdiff")) install.packages("fracdiff")
library(arfima)

#*****Data process
#train data
getSymbols("TSLA",src="yahoo",from = "2016-11-18", to = '2019-12-08')
TSLA.df = data.frame(TSLA)
TSLA.df$Close.Date = as.Date(row.names(TSLA.df))
close.ts = ts(TSLA.df$TSLA.Close)
##test data
getSymbols("TSLA",src="yahoo",from = "2019-12-09")
TSLA.test.df = data.frame(TSLA)
test.data = TSLA.test.df$TSLA.Close

#********fraction Integration
close.fd = fracdiff(close.ts,nar = 0,nma = 0)
close.res.fd = diffseries(close.ts,d = close.fd$d)
ggtsdisplay(close.res.fd, main = "Stock price trend (upper), ACF (bottom left), PACF (bottom right)")
#test
adf.test(close.res.fd)
for(i in 1:6) {
  print(Box.test(close.res.fd,type = "Ljung-Box",lag=i))
}
for(i in 1:6) {
  print(Box.test(close.res.fd^2,type = "Ljung-Box",lag=i))
}

#********model
models = arfima::arfima(close.ts,order = c(0,1,0), seasonal = list(order = c(2,1,1),period = 100),cpus = 3)
#8个model 开始，选出最好的那个
model = bestModes(models,1)
coef(model)
y_predict = predict(model,5)[[1]]$Forecast
res = residuals(model)
res = res$Mode1
error = mean(abs(test.data-y_predict)/test.data)


#plot
x = as.Date(c("2019-11-26","2019-11-27","2019-11-29","2019-12-02","2019-12-03"))
plot(x,test.data, type = "l", col = "lightblue3", xlab = "date", ylab = "stock price at close ($)", font.axis = 15, lwd = 3,ylim = c(330,365))
points(x,test.data,col = "lightblue3",pch = 16,  cex = 2)
lines(x,y_predict,col = 'lightcoral', lwd = 3)
points(x,y_predict,col = 'lightcoral',pch = 16, cex = 2)
legend(x=as.Date("2019-11-26"),y=336,legend=c("prediction value","actual value"),col=c('lightcoral',"lightblue3"), pch = 16)

#diagnoistic plot
attach(mtcars)
layout(matrix(c(1,1,2,3), 2, 2, byrow = TRUE))
plot(TSLA.df$Close.Date[1:length(res)],res,xlab = "date", ylab = "residuals")
qqnorm(res)
qqline(res,col = 'red')
residual = res[-1]
residual_lag = res[-length(res)]
plot(residual_lag,residual,xlab = "previous", ylab = "residuals")
for(i in 1:6) {
  print(Box.test(res,type = "Ljung-Box",lag=i))
}
for(i in 1:6) {
  print(Box.test(res^2,type = "Ljung-Box",lag=i))
}