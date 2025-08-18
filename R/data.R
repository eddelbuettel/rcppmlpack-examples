
#' Covertype data subset used for classification
#'
#' A subset of the UCI machine learning data set \sQuote{covertype} describing cloud coverage
#' in seven different states of coverage. This smaller subset contains with 100,000 observations
#' and 55 variables. The first 54 variables are explanatory (i.e. \dQuote{features}),
#' with the last providing the dependent variable (\dQuote{labels}. The data is in the
#' \sQuote{wide} 55 x 100,000 format used by \pkg{mlpack}. The dependent variable has been
#' transformed to the range zero to six by subtracting one from the values found in the data file.
#'
#' The original source of the data is the US Forest Service, and the complete file is part of the
#' UC Irvince machine learning data repository.
#'
#' @name covertype_small
#' @docType data
#' @source \url{https://www.mlpack.org/datasets/covertype-small.csv.gz}
#' @reference \url{https://archive.ics.uci.edu/dataset/31/covertype}
#' @keywords data
NULL
