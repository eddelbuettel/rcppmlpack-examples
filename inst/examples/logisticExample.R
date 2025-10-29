
# Set a seed for reproducibility
set.seed(123)

# Define the number of observations
n <- 1000

# Generate predictor variables
x1 <- rnorm(n, mean = 0, sd = 1) # Continuous predictor
x2 <- sample(c(0, 1), n, replace = TRUE, prob = c(0.4, 0.6)) # Binary predictor

# Define the linear predictor (z) based on desired coefficients
# For example, let's assume true coefficients are intercept = -1, x1 = 0.5, x2 = 1.2
z <- -1 + 0.5 * x1 + 1.2 * x2

# Transform the linear predictor into probabilities using the logistic function
probabilities <- 1 / (1 + exp(-z))

# Generate the binary outcome variable (y) based on these probabilities
y <- rbinom(n, size = 1, prob = probabilities)

# Create a data frame
synthetic_data <- data.frame(x1, x2, y)

# Display the first few rows of the synthetic data
print("First few rows of the synthetic data:")
print(head(synthetic_data))

# Fit a logistic regression model
logistic_model <- glm(y ~ x1 + x2, data = synthetic_data, family = "binomial")

# Summarize the model
print("Summary of the logistic regression model:")
print(summary(logistic_model))

# Create dataset: both a csv and an RData for package

logisticRegressionData <- data.frame(cbind(x1, x2, y))
data.table::fwrite(logisticRegressionData, "logistic_data.csv")
save(logisticRegressionData, file="logisticRegression.RData")
