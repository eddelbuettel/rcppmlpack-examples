
// R package header provided by mlpack R package, followed by particular method used here
#include <mlpack.h>
#include <mlpack/methods/adaboost/adaboost.hpp>

//' Run decisionTree classifier
//'
//' @title Run a decisionTree classification
//' @param dataset A matrix of explanatory variables, i.e. \dQuote{features}
//' @param labels A vector of the dependent variable as integer values, i.e. \dQuote{labels}
//' @param pct A numeric value for the percentage of data to be retained for the test set
//' @param min_leaf_size An integer value with the minimum number of elements per leaf
//' @param minimum_gain_split A double with the gain needed to further split the tree
//' @param maximum_depth An integer with the maximum tree depth, default zero means unlimited
//' @return A list object
//' @examples
//' data(iris)
//' X <- t(as.matrix(iris[,1:4]))
//' y <- as.integer(iris[,5]) - 1   # mlpack prefers {0, 1, 2}
//' decisionTree(X, y)
// [[Rcpp::export]]
Rcpp::List decisionTree(const arma::mat dataset,
                        const arma::ivec labels,
                        double pct = 0.3,
                        int min_leaf_size=10,
                        double minimum_gain_split=1e-7,
                        int maximum_depth=0) {

    const size_t numClasses = arma::max(labels) + 1;
    arma::Row<size_t> labelsvec = arma::conv_to<arma::Row<size_t>>::from(labels);

    // variables for training and test data
    arma::mat trainSet, testSet;
    arma::Row<size_t> trainLabels, testLabels;

    // Split dataset randomly into training set and test set.\n",
    mlpack::data::Split(dataset, labelsvec,
                        trainSet, testSet,
                        trainLabels, testLabels,
                        pct);

    mlpack::DecisionTree tree(trainSet, trainLabels, numClasses,
                              min_leaf_size, minimum_gain_split, maximum_depth);

    arma::Row<size_t> predictions;
    arma::mat probabilities;
    tree.Classify(testSet, predictions, probabilities);

    const double pctcorrect = 100.0 * arma::accu(predictions == testLabels) / testLabels.n_elem;

    return Rcpp::List::create(Rcpp::Named("percent_correct") = pctcorrect,
                              Rcpp::Named("predicted") = predictions,
                              Rcpp::Named("probabilities") = probabilities,
                              Rcpp::Named("testlabels") = testLabels);

}
