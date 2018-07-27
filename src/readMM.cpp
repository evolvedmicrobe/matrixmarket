// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-



#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream>
#include <istream>
extern "C" {
  #include "mm_io.h"
}
// we only include RcppArmadillo.h which pulls Rcpp.h in for us
#include "RcppArmadillo.h"

using namespace Rcpp;
using namespace arma;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
List readMMcpp(std::string fname) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int M, N, nz;   
  int i;
  
  if ((f = fopen(fname.c_str(), "r")) == NULL) 
    Rcpp::stop("Could not open file.");

  if (mm_read_banner(f, &matcode) != 0)
    Rcpp::stop("Could not process Matrix Market banner.\n");

  if (mm_is_complex(matcode))
    Rcpp::stop("Unsupported Market Market type: [%s]\n", mm_typecode_to_str(matcode));

  /* find out size of sparse matrix .... */
  
  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
    stop("Failed to read matrix size.");
  
  /* reseve memory for matrices */
  IntegerVector I(nz);
  IntegerVector J(nz);
  NumericVector val(nz);

  fclose(f);
  std::ifstream fs(fname);
  std::string line;
  fs.ignore(1000, '\n');
  fs.ignore(1000, '\n');

  for (i=0; i<nz; i++)
  {
    fs >> I[i];
    fs >> J[i];
    fs >> val[i];
    I[i]--;  /* adjust from 1-based to 0-based */
    J[i]--;
  }
  fs.close();
  return List::create(Named("nr") = M,
                      Named("nc") = N,
                      Named("i") = I,
                      Named("j") = J,
                      Named("val") = val);
}


// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
List readMMcpp2(std::string fname) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int M, N, nz;   
  int i;
  
  if ((f = fopen(fname.c_str(), "r")) == NULL) 
    Rcpp::stop("Could not open file.");
  
  if (mm_read_banner(f, &matcode) != 0)
    Rcpp::stop("Could not process Matrix Market banner.\n");
  
  if (mm_is_complex(matcode))
    Rcpp::stop("Unsupported Market Market type: [%s]\n", mm_typecode_to_str(matcode));
  
  /* find out size of sparse matrix .... */
  
  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
    stop("Failed to read matrix size.");
  
  /* reseve memory for matrices */
  IntegerVector I(nz);
  IntegerVector J(nz);
  NumericVector val(nz);
  
  /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
  /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
  /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */
  
  for (i=0; i<nz; i++)
  {
    if(fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]) != 3) {
      stop("Failed in parsing file.");
    }
    I[i]--;  /* adjust from 1-based to 0-based */
    J[i]--;
  }
  
  if (f !=stdin) fclose(f);
  return List::create(Named("nr") = M,
                      Named("nc") = N,
                      Named("i") = I,
                      Named("j") = J,
                      Named("val") = val);
  
  return 0;
}




// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
List readMMcpp3(std::string fname) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int M, N, nz;   
  int i;
  
  if ((f = fopen(fname.c_str(), "r")) == NULL) 
    Rcpp::stop("Could not open file.");
  
  if (mm_read_banner(f, &matcode) != 0)
    Rcpp::stop("Could not process Matrix Market banner.\n");
  
  if (mm_is_complex(matcode))
    Rcpp::stop("Unsupported Market Market type: [%s]\n", mm_typecode_to_str(matcode));
  
  /* find out size of sparse matrix .... */
  
  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
    stop("Failed to read matrix size.");
  
  /* reseve memory for matrices */
  IntegerVector I(nz);
  IntegerVector J(nz);
  NumericVector val(nz);
  
  fclose(f);
  std::ifstream fs(fname);
  std::string line;
  fs.ignore(1000, '\n');
  fs.ignore(1000, '\n');
  
  int cmax = 100;
  char vals[cmax];
  for (i=0; i<nz; i++)
  {

    fs.get(vals, cmax, ' ');
    fs.ignore(1);
    I[i] = atoi(vals);
    fs.get(vals, cmax, ' ');
    fs.ignore(1);
    J[i] = atoi(vals);
    fs.get(vals, cmax, '\n');
    fs.ignore(1);
    val[i] = atof(vals);
    I[i]--;  /* adjust from 1-based to 0-based */
  J[i]--;
  }
  fs.close();
  return List::create(Named("nr") = M,
                      Named("nc") = N,
                      Named("i") = I,
                      Named("j") = J,
                      Named("val") = val);
}


void filll(char* val, std::ifstream& f, char delim) {
  int i=0;
  while(true) {
    val[i] = f.get();
    if(val[i] == delim) {
      val[i] = '\0';
      break;
    }
    i++;
  }
}

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
List readMMcpp4(std::string fname) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int M, N, nz;   
  int i;
  
  if ((f = fopen(fname.c_str(), "r")) == NULL) 
    Rcpp::stop("Could not open file.");
  
  if (mm_read_banner(f, &matcode) != 0)
    Rcpp::stop("Could not process Matrix Market banner.\n");
  
  if (mm_is_complex(matcode))
    Rcpp::stop("Unsupported Market Market type: [%s]\n", mm_typecode_to_str(matcode));
  
  /* find out size of sparse matrix .... */
  
  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
    stop("Failed to read matrix size.");
  
  /* reseve memory for matrices */
  IntegerVector I(nz);
  IntegerVector J(nz);
  NumericVector val(nz);
  
  fclose(f);
  std::ifstream fs(fname);
  std::string line;
  fs.ignore(1000, '\n');
  fs.ignore(1000, '\n');
  
  int cmax = 100;
  char vals[cmax];
  
  for (i=0; i<nz; i++)
  {
    filll(vals, fs, ' ');
    I[i] = atoi(vals);
    filll(vals, fs, ' ');
    J[i] = atoi(vals);
    filll(vals, fs, '\n');
    val[i] = atof(vals);
    I[i]--;  /* adjust from 1-based to 0-based */
  J[i]--;
  }
  fs.close();
  return List::create(Named("nr") = M,
                      Named("nc") = N,
                      Named("i") = I,
                      Named("j") = J,
                      Named("val") = val);
}

#define BUFSIZE 32768
class Reader {
public:
  char buf[BUFSIZE];
  int pos;
  std::ifstream fs;
  Reader(std::string fname) : pos(0), fs(fname){
    fs.ignore(1000, '\n');
    fs.ignore(1000, '\n');
    fs.read(buf, BUFSIZE);
  }
  ~Reader() {
    fs.close();
  }
  void filfrombuf(char* val,  char delim) {
    int i=0;
    while(true) {
      if (pos >= BUFSIZE) {
        fs.read(buf, BUFSIZE);
        pos =0;
      }
      val[i] = buf[pos];
      pos++;
      if(val[i] == delim) {
        val[i] = '\0';
        return;
      }
      i++;
    }
  }
};




// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
List readMMcpp5(std::string fname) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int M, N, nz;   
  int i;
  
  if ((f = fopen(fname.c_str(), "r")) == NULL) 
    Rcpp::stop("Could not open file.");
  
  if (mm_read_banner(f, &matcode) != 0)
    Rcpp::stop("Could not process Matrix Market banner.\n");
  
  if (mm_is_complex(matcode))
    Rcpp::stop("Unsupported Market Market type: [%s]\n", mm_typecode_to_str(matcode));
  
  /* find out size of sparse matrix .... */
  
  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
    stop("Failed to read matrix size.");
  
  /* reseve memory for matrices */
  IntegerVector I(nz);
  IntegerVector J(nz);
  NumericVector val(nz);
  
  fclose(f);
  Reader r(fname);
  int cmax = 100;
  char vals[cmax];
  
  for (i=0; i<nz; i++)
  {
    r.filfrombuf(vals, ' ');
    I[i] = atoi(vals);
    r.filfrombuf(vals, ' ');
    J[i] = atoi(vals);
    r.filfrombuf(vals, '\n');
    val[i] = atof(vals);
    I[i]--;  /* adjust from 1-based to 0-based */
    J[i]--;
  }
  
  return List::create(Named("nr") = M,
                      Named("nc") = N,
                      Named("i") = I,
                      Named("j") = J,
                      Named("val") = val);
}

