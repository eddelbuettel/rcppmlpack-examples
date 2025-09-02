
library(rcppmlpackexamples)
library(tinytest)

## quick basic tests from examples


## linear regression without regularisation
suppressMessages(library(utils))
data("trees", package="datasets")
X <- with(trees, cbind(log(Girth), log(Height)))
y <- with(trees, log(Volume))
lmfit <- lm(y ~ X)
mlfit <- linearRegression(X, y)
expect_equal(unname(fitted(lmfit)),  as.vector(mlfit))
