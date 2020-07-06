# Task 1 part (a) ---------------------------------------------------------
#? is to search command in help document.
#?? is to search keyword in all installed packages and help document.
# Task 1 part (b) ---------------------------------------------------------
rm(list = ls())
x = 1/7
print(x,digits=15)
# Task 1 part (c) ---------------------------------------------------------
#When we need to specify plot the relation ship of two variable under some condition, we should use coplot().
# Task 1 part (d) ---------------------------------------------------------
# All number in R is stored in double precision, while compared them by "==" directly, there'll be problems.
# Task 1 part (e) ---------------------------------------------------------
y.vec = rep(seq(1,100),each=2)^c(1,0)-c(0,2)
# Task 2 part (a) ---------------------------------------------------------
rm(list = ls())
z = sample(c(sample(-100:100, 27), rep(NA, 3)))
tmp = runif(1, min = 3, max = 4)
m.mat = matrix(c(1:4, tmp, 6L:9L), nrow = 3)
colnames(m.mat) = c("A", "B", "A")
m.df = data.frame(A = 1:3, B = c(4, tmp, 6L), A = 7L:9L)
#i. 
print(z[1])
#ii. 
print(z[2:5])
#iii. 
print(z[1:(length(z)-2)])
#iv. 
print(z[seq(1:(length(z)/2))*2])
#v. 
print(z[z>0])
#vi. 
print(z[!is.na(z)])
#vii.
print(z[seq(from=2,by=3,to=length(z))])
# Task 2 part (b) ---------------------------------------------------------
#It first assigns names to the objects in z.
#Then it pick up object with name "Michigan"
# Task 2 part (c) ---------------------------------------------------------
#i. 
print(m.mat[1:2,])
#ii. 
print(m.mat[m.mat>log(10,base=2)&col(m.mat)==2])
# Task 2 part (d) ---------------------------------------------------------
# It means extracting objects in m.mat from left to right by row.
# Task 2 part (e) ---------------------------------------------------------
#i.
print(m.df[1:2,])
#ii. 
print(m.df$B[m.df$B>log(10,base=2)])
# Task 2 part (f) ---------------------------------------------------------
#The first line's output means whether the objects, which locates at the first row and first column of m.mat and m.df, are the same.
#The second line's output means whether the column with name "B" of m.mat and m.df are the same.
#The third line's output shows the column of m.mat with name "B."
#The fouth line's output shows the column of m.df with name "B."
#The sixth line's output shows the name of columns of m.mat and m.df.
#The eighth line's output shows whether the third columns of m.mat and m.df are the same.
#The ninth line'soutput shows whether the objects in the third columns of m.mat is stored in interger.
#The tenth line'soutput shows whether the objects in the third columns of m.df is stored in interger.
# Task 3 part (a) ---------------------------------------------------------
rm(list = ls())
s = "Satisfactory"
p = "Poor"
e = "Excellent"
g = "Good"
i = "Inadequate"
a = "A"
b = "B"
c = "C"
d = "D"
f = "F"
gindex = c(3,3,4,1,1,rep(2,4),1:3,1,2,5,1,2,1,4,rep(1,3),3,3,1,3,2,2,1:3,2,1,1:3,3,2,3,2)
grade = c(c,c,d,a,a,rep(b,4),a,b,c,a,b,f,a,b,a,d,rep(a,3),c,c,a,c,b,b,a,b,c,b,a,a,b,c,c,b,c,b)
desc = c(s,s,p,e,e,rep(g,4),e,g,s,e,g,i,e,g,e,p,rep(e,3),s,s,e,s,g,g,e,g,s,g,e,e,g,s,s,g,s,g)
fail = c(rep(FALSE,14),TRUE,rep(FALSE,25))
gender = c(rep("Female",20),rep("Male",20))
proj = c(rep(18,6),rep(17,4),rep(16,3),rep(15,7),rep(18,5),rep(17,4),rep(16,5),rep(15,6))
gradebook.df = data.frame(gindex = gindex,grade = grade, desc = desc, fail = fail, gender = gender, proj = proj)
# Task 3 part (b) ---------------------------------------------------------
print(data.frame(A = sum(gradebook.df$grade == a), B = sum(gradebook.df$grade == b), C = sum(gradebook.df$grade == c), D = sum(gradebook.df$grade == d), F = sum(gradebook.df$grade == f)))
# Task 3 part (c) ---------------------------------------------------------
print(data.frame(A = mean(gradebook.df$proj[gradebook.df$grade == a]), B = mean(gradebook.df$proj[gradebook.df$grade == b]), C = mean(gradebook.df$proj[gradebook.df$grade == c]), D = mean(gradebook.df$proj[gradebook.df$grade == d]), F = mean(gradebook.df$proj[gradebook.df$grade == f])))
# Task 3 part (d) ---------------------------------------------------------
index = 1:40
print(gradebook.df[sample(index,10),])
# Task 4 part (a) ---------------------------------------------------------
rm(list = ls())
random = rnorm(100,4,2)
hist(random,freq = TRUE)
# Task 4 part (b) ---------------------------------------------------------
x = seq(from = -6, to = 10, by = 0.1)
y = dnorm(x,4,2)
hist(random,freq = FALSE)
lines(x,y,col="blue", lwd=2)
# Task 4 part (c) ---------------------------------------------------------
random2 = rnorm(700,4,2)
print(random2)
random3 = (sample(random2,300)-4)/2
print(random3)
# Task 5 part (a) ---------------------------------------------------------
rm(list = ls())
chisqdens.plot = function(nu){
  x = seq(from = 0, to = qchisq(0.999,nu), by = 0.05)
  y = dchisq(x,nu)
  plot(x,y,"l")
}
chisqdens.plot(2)
# Task 5 part (b) ---------------------------------------------------------
chisqdens.plot = function(nu){
  x = seq(from = 0, to = qchisq(0.999,nu[length(nu)]), by = 0.05)
  y = dchisq(x,nu[1])
  plot(x,y,"l",col = 1)
  for (i in 2:length(nu)){
    y = dchisq(x,nu[i])
    lines(x,y,col = i)
  }
  legend(9,0.5,nu,text.col=1:length(nu),col = 1:length(nu),lty = 1)
}
chisqdens.plot(c(2,4,8,16))
# Task 5 part (c) ---------------------------------------------------------
chisqdens.plot = function(nu){
  col = hsv(1/nu,0.75,0.75,1)
  colb = hsv(1/nu,0.75,0.75,0.25)
  x = seq(from = 0, to = qchisq(0.999,nu[length(nu)]), by = 0.05)
  x2 = c(0,x,qchisq(0.999,nu[1])+0.02)
  y = dchisq(x,nu[1])
  y2 = c(0,y,0)
  plot(x,y,"l",col = col[1])
  polygon(x2,y2, col = colb[1], border = col[1])
  for (i in 2:length(nu)){
    x2 = c(0,x,qchisq(0.999,nu[1])+0.02)
    y2 =c(0,dchisq(x,nu[i]),0)
    polygon(x2, y2, col = colb[i], border = col[i])
  }
  legend(9,0.5,nu,text.col=col,col = col,lty = 1)
}
# Task 6 part (a) ---------------------------------------------------------
#eruptions contains the duration of eruptions
#waiting contains the time gap between two neighbouring eruptions.
# Task 6 part (b) ---------------------------------------------------------
data ("faithful")
hist(faithful$waiting,freq=TRUE)
hist(faithful$waiting,freq=TRUE,breaks = 20)
# Task 6 part (c) ---------------------------------------------------------
qqnorm(faithful$waiting)
qqline(faithful$waiting,lwd=2,col=2)
#It shows that the waitting variable doesn't follow a norm distribution.
# Task 6 part (d) ---------------------------------------------------------
plot(faithful$waiting,faithful$eruptions)
lowessdf = lowess(faithful$waiting,faithful$eruptions)
lines(lowessdf$x,lowessdf$y,col=2)
# Task 7 ---------------------------------------------------------
library(lattice)
plt = xyplot(NOx ~ E|C,ethanol)
show(plt)
#From the graph, it may be concluded that the NOx may has few relationship with C. But NOx is normally distributed with E.

