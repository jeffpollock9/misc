data {
    real alpha;
    real beta;
}

parameters {
    real mu;
}

transformed parameters {
    real nu = exp(mu);
}

model {
    nu ~ gamma(alpha, beta);
    target += mu;
}
