
// R package header provided by mlpack R package, followed by particular method used here
#include <mlpack.h>
#include <mlpack/methods/adaboost/adaboost.hpp>


//' Run AdaBoost using a simple Perceptron model as the weak learner
//'
//' @title An AdaBoost classification
//' @param dataset A matrix of explanatory variables, i.e. \dQuote{features}
//' @param labels A vector of the dependent variable as integer values, i.e. \dQuote{labels}
//' @param iterations An integer value for the number of iterations
//' @param tolerance A double with the desired tolerance
//' @param perceptronIter An integer value for the number of a iterations for the weak learner
//' @return A list object
//' @examples
//' data(iris)
//' X <- t(as.matrix(iris[,1:4]))
//' y <- as.integer(iris[,5]) - 1   # mlpack prefers {0, 1, 2}
//' adaBoost(X, y)
// [[Rcpp::export]]
Rcpp::List adaBoost(const arma::mat dataset, const arma::vec labels,
                    int iterations = 100,
                    double tolerance = 2e-10,
                    int perceptronIter = 400) {

    // mlpack needs this as a Row<size_t>
    arma::Row<size_t> labelsvec = arma::conv_to<arma::Row<size_t>>::from(labels);

    using PerceptronType = mlpack::Perceptron<mlpack::SimpleWeightUpdate, mlpack::ZeroInitialization, arma::mat>;
    mlpack::AdaBoost<PerceptronType, arma::mat> a;
    int numClasses = arma::max(labelsvec) + 1;
    //Rcpp::Rcout << "Num classes: " << numClasses << std::endl;
    //dataset.print("dataset");
    //labelsvec.print("labelsvec");
    double ztProduct = a.Train(dataset, labelsvec, numClasses, iterations, tolerance, perceptronIter);

    arma::Row<size_t> predictedLabels;
    a.Classify(dataset, predictedLabels);
    //predictedLabels.print("predicted");
    size_t countError = arma::accu(labelsvec != predictedLabels);
    double hammingLoss = (double) countError / labels.n_cols;

    return Rcpp::List::create(Rcpp::Named("countError") = countError,
                              Rcpp::Named("hammingLoss") = hammingLoss,
                              Rcpp::Named("ztProduct") = ztProduct,
                              Rcpp::Named("predicted") = predictedLabels);

}
