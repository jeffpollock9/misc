library(rstan)
library(ggplot2)
library(dplyr)
library(tidyr)

n <- 1e5L

alpha <- 1.666
beta <- 2.42

nu_samples <- function(stan_file) {

    model <- rstan::stan_model(stan_file)

    samples <- rstan::sampling(model,
                               iter = n,
                               seed = 666,
                               data = list(alpha = alpha, beta = beta))

    rstan::extract(samples, "nu")[["nu"]]
}

manual_nu <- nu_samples("transformations_manual.stan")
automatic_nu <- nu_samples("transformations_automatic.stan")
wrong_nu <- nu_samples("transformations_wrong.stan")

plot_data <- data.frame(manual = manual_nu,
                        automatic = automatic_nu,
                        wrong = wrong_nu) %>%
    gather("method", "nu")

ggplot(plot_data) +
    geom_density(aes(nu, col = method, fill = method)) +
    facet_wrap(~ method) +
    stat_function(linetype = 3,
                  size = 1.2,
                  fun = dgamma,
                  args = list(shape = alpha, rate = beta))
