
// R package header provided by mlpack R package
#include <mlpack.h>

//' Simple example of loading categorical data via 'mlpack'
//'
//' @return Nothing is returned, the function is invoked for its side effect.
// [[Rcpp::export]]
void datasetExample() {
    // cf https://mlpack.org/doc/user/load_save.html#mixed-categorical-data

    // Load a categorical dataset.
    arma::mat dataset;

    // Define a TextOptions to load categorical data.
    mlpack::TextOptions opts;
    opts.Fatal() = true;
    opts.Categorical() = true;

    // See https://datasets.mlpack.org/covertype.train.arff.
    mlpack::Load("covertype.train.arff", dataset, opts);

    // Print information about the data.
    Rcpp::Rcout << "The data in 'covertype.train.arff' has: " << std::endl;
    Rcpp::Rcout << " - " << dataset.n_cols << " points." << std::endl;
    Rcpp::Rcout << " - " << opts.DatasetInfo().Dimensionality() << " dimensions."
                << std::endl;

    arma::Row<size_t> labels;
    // We need to have a second options, since we are loading two different
    // data types and extension.
    mlpack::TextOptions labelOpts;
    labelOpts.Fatal() = true;
    // See https://datasets.mlpack.org/covertype.train.labels.csv.
    mlpack::Load("covertype.train.labels.csv", labels, labelOpts);


    // Print information about each dimension.
    for (size_t d = 0; d < opts.DatasetInfo().Dimensionality(); ++d) {
        if (opts.DatasetInfo().Type(d) == mlpack::Datatype::categorical) {
            Rcpp::Rcout << " - Dimension " << d << " is categorical with "
                        << opts.DatasetInfo().NumMappings(d) << " categories." << std::endl;
        } else {
            Rcpp::Rcout << " - Dimension " << d << " is numeric." << std::endl;
        }
    }

    // Modify the 5th point.  Increment any numeric values, and set any categorical
    // values to the string "hooray!".
    for (size_t d = 0; d < opts.DatasetInfo().Dimensionality(); ++d) {
        if (opts.DatasetInfo().Type(d) == mlpack::Datatype::categorical) {
            // This will create a new mapping if the string "hooray!" does not already
            // exist as a category for dimension d..
            dataset(d, 4) = opts.DatasetInfo().MapString<double>("hooray!", d);
        } else {
            dataset(d, 4) += 1.0;
        }
    }
}
