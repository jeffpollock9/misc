data {
    real alpha;
    real beta;
}

parameters {
    real<lower = 0.0> nu;
}

model {
    nu ~ gamma(alpha, beta);
}
