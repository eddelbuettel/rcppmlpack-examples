
#include <RcppArmadillo.h>      		// it is important that this precedes the mlpack headers

#if !defined(MLPACK_COUT_STREAM) 		// also provided by mlpack.h in the R package
  #define MLPACK_COUT_STREAM Rcpp::Rcout
#endif
#if !defined(MLPACK_CERR_STREAM)
  #define MLPACK_CERR_STREAM Rcpp::Rcerr
#endif

