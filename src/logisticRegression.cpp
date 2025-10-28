
// R package header provided by mlpack R package, followed by particular method used here
#include <mlpack.h>
#include <mlpack/methods/logistic_regression.hpp>

//' Run a logistic regression returning classification
//'
//' This function performs a logistic regression on the given data set.
//'
//' @title Run logistic regression
//' @param data A matrix of data values
//' @param labels A vector of class labels
//' @param lambda An optional L2 regularization parameter, defaults to zero
//' @return A list with predictions, probabilities and parmeters
//' @examples
//' data(logisticRegression)
//' X <- as.matrix(logisticsData[, 1:2])
//' y <- as.matrix(logisticsData[, 3])
//' res <- logisticRegression(X, y)
//' res$parameters
// [[Rcpp::export]]
Rcpp::List logisticRegression(const arma::mat& data,
                              const arma::rowvec& labels,
                              const double lambda = 0.0) {

    arma::mat X = data.t();     				// account for arma/mlpack transposed view
    arma::Row<size_t> y = arma::conv_to<arma::Row<size_t>>::from(labels);   // mlpack needs Row<size_t>
    mlpack::LogisticRegression<> lr(X, y, lambda);
    arma::Row<size_t> predictions;
    arma::mat probabilities;
    lr.Classify(X, predictions, probabilities);
    auto parameters = lr.Parameters();
    return Rcpp::List::create(Rcpp::Named("predictions") = predictions,
                              Rcpp::Named("probabilities") = probabilities,
                              Rcpp::Named("parameters") = parameters);
}
