
#include "rcppmlpackexamples.h"

#include <mlpack.hpp>

//' Run a Random Forest Classifier
//'
//' This function performs a Random Forest classification on a subset of the
//' standard \sQuote{covertype} data set
//'
//' @title Run a Random Forest classificatio
//' @param dataset A matrix of explanatory variables, i.e. \dQuote{features}
//' @param labels A vector of the dependent variable as integer values, i.e. \dQuote{labels}
//' @param pct A numeric value for the percentage of data to be retained for the test set
//' @param nclasses An integer value for the number of a distinct values in \code{labels}
//' @param ntrees An integer value for the number of trees
//' @return A list object
//' @seealso covertype_small
//' @examples
//' data(covertype_small)                         # see help(covertype_small)
//' res <- randomForest(covertype_small[-55,],    # features (already transposed)
//'                     covertype_small[55,],     # labels now in [0, 6] range
//'                     0.3)                      # percentage used for testing
//' str(res)  # accuracy varies as method is randomized but not seed set here
// [[Rcpp::export]]
Rcpp::List randomForest(const arma::mat dataset, const arma::vec labels,
                        double pct = 0.3, int nclasses = 7, int ntrees = 10) {

    // mlpack needs this as a Row<size_t>
    arma::Row<size_t> labelsvec = arma::conv_to<arma::Row<size_t>>::from(labels);

    // variables for training and test data
    arma::mat trainSet, testSet;
    arma::Row<size_t> trainLabels, testLabels;

    // Split dataset randomly into training set and test set.\n",
    mlpack::data::Split(dataset, labelsvec,
                        trainSet, testSet,
                        trainLabels, testLabels,
                        pct /* Percentage of dataset to use for test set. */);

    mlpack::RandomForest<> rf(trainSet, trainLabels,
                              nclasses /* Number of classes in dataset */,
                              ntrees /* number of trees */);
    // Predict the labels of the test points.,
    arma::Row<size_t> output;
    rf.Classify(testSet, output);
    // Now compute the accuracy. The 'probabilities' output could also be used to\n",
    // generate an ROC curve.\n",
    const double pctcorrect = 100.0 * arma::accu(output == testLabels) / testLabels.n_elem;
    return Rcpp::List::create(Rcpp::Named("percent_correct") = pctcorrect,
                              Rcpp::Named("predicted") = output,
                              Rcpp::Named("testlabels") = testLabels);
}
