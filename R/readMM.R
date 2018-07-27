#' @export
readMM_nigel <- function(fname) {
  data = readMMcpp(fname)
  new("dgTMatrix", Dim = c(data$nr, data$nc), i = data$i, j = data$j, x = data$val)
}

readMM_nigel2 <- function(fname) {
  data = readMMcpp2(fname)
  new("dgTMatrix", Dim = c(data$nr, data$nc), i = data$i, j = data$j, x = data$val)
}


#' @export
write_mm_matrix <- function(nrow, ncol, sparsity, fname) {
  n = as.integer(nrow*ncol*sparsity)
  r = sort(sample(nrow, n, replace = TRUE))
  c = sort(sample(ncol, n, replace = TRUE))
  r
  c
  f = file(fname, open = "w")
  writeLines("%%MatrixMarket matrix coordinate real general", f)
  writeLines(paste(nrow, ncol, n), f)
  for(i in 1:n) {
    writeLines(paste(nrow, ncol, n), f)
  }
  close(f)
}