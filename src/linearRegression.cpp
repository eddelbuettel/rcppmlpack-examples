
#include <RcppArmadillo.h>      		// it is important that this precedes the mlpack headers

#if !defined(MLPACK_COUT_STREAM) 		// also provided by mlpack.h in the R package
  #define MLPACK_COUT_STREAM Rcpp::Rcout
#endif
#if !defined(MLPACK_CERR_STREAM)
  #define MLPACK_CERR_STREAM Rcpp::Rcerr
#endif

#include <mlpack.hpp>
#include <mlpack/methods/linear_regression/linear_regression.hpp> // particular algorithm used here

//' Run a linear regression (with optional ridge regression)
//'
//' This function performs a linear regression, and serves as a simple
//' test case for accessing an MLPACK function.
//'
//' @title Run a linear regression with optional ridge regression
//' @param matX A matrix of explanatory variables ('predictors') in standard
//' R format (i.e. \sQuote{tall and skinny'} to be transposed internally to MLPACK
//' format (i.e. `\sQuote{short and wide}).
//' @param vecY A vector of dependent variables ('responses')
//' @param lambda An optional ridge parameter, defaults to zero
//' @param intercept An optional boolean switch about an intercept, default is true.
//' @return A vector with fitted values
//' @examples
//' suppressMessages(library(utils))
//' data("trees", package="datasets")
//' X <- with(trees, cbind(log(Girth), log(Height)))
//' y <- with(trees, log(Volume))
//' lmfit <- lm(y ~ X)
//' # summary(fitted(lmfit))
//' mlfit <- linearRegression(X, y)
//' # summary(mlfit)
//' all.equal(unname(fitted(lmfit)),  as.vector(mlfit))
// [[Rcpp::export]]
arma::vec linearRegression(const arma::mat& matX,
                           const arma::rowvec& vecY,
                           const double lambda = 0.0,
                           const bool intercept = true) {

    arma::mat X = matX.t();     // account for arma/mlpack transposed view
    mlpack::regression::LinearRegression<> lr(X, vecY, lambda, intercept);
    arma::rowvec fittedValues(vecY.n_elem);
    lr.Predict(X,  fittedValues);
    return fittedValues.t();
}
