
// R package header provided by mlpack R package, followed by particular method used here
#include <mlpack.h>
#include <mlpack/methods/hoeffding_trees/hoeffding_trees.hpp>

//' Run a Hoeffding Trees (Batch) Classifier
//'
//' This function performs a Hoeffding Trees classification.
//'
//' @title Run a Random Forest classificatio
//' @param dataset A matrix of explanatory variables, i.e. \dQuote{features}
//' @param labels A vector of the dependent variable as integer values, i.e. \dQuote{labels}
//' @param pct A numeric value for the percentage of data to be retained for the test set
//' @param nclasses An integer value for the number of a distinct values in \code{labels}
//' @return A list object
//' @seealso covertype_small
//' @examples
//' data(covertype_small)                           # see help(covertype_small)
//' res <- hoeffdingTrees(covertype_small[-55,],    # features (already transposed)
//'                       covertype_small[55,],     # labels now in [0, 6] range
//'                       0.3)                      # percentage used for testing
//' str(res)  # accuracy varies as method is randomized but no seed set here
// [[Rcpp::export]]
Rcpp::List hoeffdingTrees(const arma::mat dataset, const arma::vec labels,
                          double pct = 0.3, int nclasses = 7) {

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

    mlpack::HoeffdingTree ht(trainSet, trainLabels, nclasses);

    // Predict the labels of the test points.,
    arma::Row<size_t> output;
    ht.Classify(testSet, output);
    // Now compute the accuracy. The 'probabilities' output could also be used to\n",
    // generate an ROC curve.\n",
    const double pctcorrect = 100.0 * arma::accu(output == testLabels) / testLabels.n_elem;
    return Rcpp::List::create(Rcpp::Named("percent_correct") = pctcorrect,
                              Rcpp::Named("predicted") = output,
                              Rcpp::Named("testlabels") = testLabels);
}
