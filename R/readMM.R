#' @export
readMM_nigel <- function(fname) {
  data = readMMcpp(fname)
  new("dgTMatrix", Dim = c(data$nr, data$nc), i = data$i, j = data$j, x = data$val)
}

readMM_nigel2 <- function(fname) {
  data = readMMcpp2(fname)
  new("dgTMatrix", Dim = c(data$nr, data$nc), i = data$i, j = data$j, x = data$val)
}

readMM_nigel3 <- function(fname) {
  data = readMMcpp3(fname)
  new("dgTMatrix", Dim = c(data$nr, data$nc), i = data$i, j = data$j, x = data$val)
}


#' @export
write_mm_matrix <- function(nrow, ncol, sparsity, fname) {
  options(scipen = 99999)
  n = as.integer(nrow*ncol*sparsity)
  avg_per_row = as.integer(n / nrow)
  n = avg_per_row * nrow
  if(avg_per_row < 1) {
    stop("Need at least one per row")
  }
  f = file(fname, open = "w")
  writeLines("%%MatrixMarket matrix coordinate real general", f)
  writeLines(paste(nrow, ncol, n), f)
  r = sort(sample(nrow, n, replace = TRUE))
  
  for(i in 1:nrow) {
    samps = sort(sample(ncol, avg_per_row))
    for(j in samps)
      writeLines(paste(i, j, 5.435), f)
  }
  close(f)
}