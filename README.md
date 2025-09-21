
## rcppmlpackexamples: Example of using [mlpack][mlpack] via its C++ API from R

[![CI](https://github.com/eddelbuettel/rcppmlpack-examples/workflows/ci/badge.svg)](https://github.com/eddelbuettel/rcppmlpack-examples/actions?query=workflow%3Aci)
[![License](https://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](https://www.gnu.org/licenses/gpl-2.0.html)
[![CRAN](https://www.r-pkg.org/badges/version/rcppmlpackexamples)](https://cran.r-project.org/package=rcppmlpackexamples)
[![r-universe](https://eddelbuettel.r-universe.dev/badges/rcppmlpackexamples)](https://eddelbuettel.r-universe.dev/rcppmlpackexamples)
[![Downloads](https://cranlogs.r-pkg.org/badges/rcppmlpackexamples?color=brightgreen)](https://www.r-pkg.org/pkg/rcppmlpackexamples)

### About

[mlpack][mlpack] has supported header-only compilation since the 4.0.0 release. It also contains [an
R package][rpackage] that has been part of [CRAN][cran] for years. Its focus is on access from R at
the R prompt: underlying [mlpack][mlpack] functions are properly wrapped.

Sometimes, however, we would like to access the C++ API of [mlpack][mlpack] from the C++ side of an
R package. This package provides a working demonstration of how to do this.

### Scope

Currently, the package contains two examples covering

- linear regression (with optional regularization)
- random forest classification of a multinomial response
- loan default prediction using a decision tree

### Installation

The package is on CRAN and can be installed via the usual

```r
> install.packages("rcppmlpackexamples")
```

The [r-univere page](https://eddelbuettel.r-universe.dev/rcppmlpackexamples) has source and binary
builds from the repository version which may differ from the CRAN version and shows how to install
them. Lastly, one can always rely on `remotes::install_github()`:

```r
> remotes::install_github("eddelbuettel/rcppmlpack-examples")
```

### Miscellaneous

We use the `rcpp` prefix to not conflate this repo with the existing
[mlpack examples][mlpack-examples] repo.


### Author

Dirk Eddelbuettel for this R package

The mlpack authors for all of mlpack

### License

GPL (>= 2) for this package

MIT for mlpack


[mlpack]: https://mlpack.org/
[rpackage]: https://cran.r-project.org/package=mlpack
[cran]: https://cran.r-project.org
[mlpack-examples]: https://github.com/mlpack/examples
