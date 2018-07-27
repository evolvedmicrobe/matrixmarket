library(matrixmarket)
library(Matrix)
fname = "/Users/nigel.delaney/tmp.mm"
write_mm_matrix(10000, 10000, .04, fname)
system.time({res <- readMM(fname)})
rm(res)
# C++
system.time({res2 <- readMM_nigel(fname)})
rm(res2)
# C fscan
system.time({res3 <- readMM_nigel2(fname)})
rm(res3)
# C++ atoi
system.time({res4 <- readMM_nigel3(fname)})
rm(res4)
# C++ get/atoi
system.time({res5 <- readMM_nigel4(fname)})
rm(res5)

# C++ buffer
system.time({res6 <- readMM_nigel5(fname)})
rm(res6)

library(lineprof)
lineprof({res <- readMM(fname)})
g = lineprof({res3 <- readMM_nigel4(fname)})
g
shine(g)
for(i in 1:1000) {
  res3 <- readMM_nigel4(fname)
}
