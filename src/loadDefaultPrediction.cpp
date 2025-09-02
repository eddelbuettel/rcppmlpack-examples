
// R package header provided by mlpack R package, followed by particular method used here
#include <mlpack.h>
#include <mlpack/methods/decision_tree/decision_tree.hpp>
// See https://github.com/mlpack/examples/blob/master/cpp/decision_tree/loan_default_prediction/

using namespace mlpack;
using namespace mlpack::data;

double ComputeAccuracy(const arma::Row<size_t>& yPreds, const arma::Row<size_t>& yTrue) {
    const size_t correct = arma::accu(yPreds == yTrue);
    return (double)correct / (double)yTrue.n_elem;
}

double ComputePrecision(const size_t truePos, const size_t falsePos) {
    return (double)truePos / (double)(truePos + falsePos);
}

double ComputeRecall(const size_t truePos, const size_t falseNeg) {
    return (double)truePos / (double)(truePos + falseNeg);
}

double ComputeF1Score(const size_t truePos, const size_t falsePos, const size_t falseNeg) {
    double prec = ComputePrecision(truePos, falsePos);
    double rec = ComputeRecall(truePos, falseNeg);
    return 2 * (prec * rec) / (prec + rec);
}

Rcpp::NumericMatrix makeReportMatrix(const arma::Row<size_t>& yPreds, const arma::Row<size_t>& yTrue) {
    arma::Row<size_t> uniqs = arma::unique(yTrue);
    int n = uniqs.n_elem;
    Rcpp::NumericMatrix R(n, 4);

    for (auto i=0; i<n; i++) {
        auto val = uniqs(i);
        size_t truePos = arma::accu(yTrue == val && yPreds == val && yPreds == yTrue);
        size_t falsePos = arma::accu(yPreds == val && yPreds != yTrue);
        //size_t trueNeg = arma::accu(yTrue != val && yPreds != val && yPreds == yTrue);
        size_t falseNeg = arma::accu(yPreds != val && yPreds != yTrue);

        R(i, 0) = ComputePrecision(truePos, falsePos);
        R(i, 1) = ComputeRecall(truePos, falseNeg);
        R(i, 2) = ComputeF1Score(truePos, falsePos, falseNeg);
        R(i, 3) = truePos;
    }
    Rcpp::rownames(R) = Rcpp::CharacterVector::create("zero", "one");
    Rcpp::colnames(R) = Rcpp::CharacterVector::create("precision", "recall", "f1-score", "support");
    return R;
}

//' Predict loan default using a decision tree model
//'
//' This functions performs a loan default prediction based on three variables
//' on employment, bank balance and annual salary to predict loan repayment or
//' default
//'
//' @title loanDefaultPrediction
//' @param loanDataFeatures A matrix of dimension 3 by N, i.e. transposed relative to
//' what R uses, with the three explanantory variables
//' @param loanDataTargets A vector of (integer-valued) binary variables loan repayment
//' or default
//' @param pct A numeric variable with the percentage of data to be used for testing,
//' defaults to 25\%
//' @return A list obkect with predictions, probabilities, accuracy and a report matrix
//' @examples
//' data(loanData)
//' res <- loanDefaultPrediction(t(as.matrix(loanData[,-4])),  # col 1 to 3, transposed
//'                              loanData[, 4],                # col 4 is the target
//'                              0.25)                         # retain 25% for testing
//' str(res)
//' res$report
// [[Rcpp::export]]
Rcpp::List loanDefaultPrediction(arma::mat& loanDataFeatures,
                                 arma::vec& loanDataTargets,
                                 double pct = 0.25) {

    // Split the data into features (X) and target (y) variables, targets are the last row.
    arma::Row<size_t> targets = arma::conv_to<arma::Row<size_t>>::from(loanDataTargets);//.row(loanData.n_rows - 1));

    // Train Test Split
    /**
     * The data set has to be split into a training set and a test set. Here the dataset has 10000
     * observations and the test Ratio is taken as 25% of the total observations. This indicates
     * the test set should have 25% * 10000 = 2500 observations and trainng test should have 7500
     * observations respectively. This can be done using the `data::Split()` api from mlpack.
     **/

    // Split the dataset into train and test sets using mlpack.
    arma::mat Xtrain, Xtest;
    arma::Row<size_t> Ytrain, Ytest;
    Split(loanDataFeatures, targets, Xtrain, Xtest, Ytrain, Ytest, pct);

    /**
     * Decision trees start with a basic question, From there you can ask a
     * series of questions to determine an answer. These questions make up
     * the decision nodes in the tree, acting as a means to split the data.
     * Each question helps an individual to arrive at a final decision, which
     * would be denoted by the leaf node. Observations that fit the criteria
     * will follow the “Yes” branch and those that don’t will follow the
     * alternate path. Decision trees seek to find the best split to subset
     * the data. To create the model we'll be using `DecisionTree<>` API from
     * mlpack.
     */
    // Create and train Decision Tree model using mlpack.
    DecisionTree dt(Xtrain, Ytrain, 2);
    // Classify the test set using trained model & get the probabilities.
    arma::Row<size_t> output;
    arma::mat probs;
    dt.Classify(Xtest, output, probs);

    return Rcpp::List::create(Rcpp::Named("predictions") = output.t(),
                              Rcpp::Named("probabilities") = probs.t(),
                              Rcpp::Named("accurracy") = ComputeAccuracy(output, Ytest),
                              Rcpp::Named("report") = makeReportMatrix(output, Ytest));
}
