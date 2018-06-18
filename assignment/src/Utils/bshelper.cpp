#include "utils.h"
#include "bshelper.h"
#include <cmath>
#include <boost/math/distributions/normal.hpp>

using boost::math::normal;

const double d1(double asset_price, double strike, double rate, double volatility, double time_to_maturity) {
    double unadjusted_d1 = log(asset_price / strike) + (rate + pow(volatility, 2) / 2) * time_to_maturity;
    double result = unadjusted_d1 / (volatility * sqrt(time_to_maturity));
    return result;
}

const double d2(double asset_price, double strike, double rate, double volatility, double time_to_maturity) {
    double unadjusted_d2 = log(asset_price / strike) + (rate - pow(volatility, 2) / 2) * time_to_maturity;
    double result = unadjusted_d2 / (volatility * sqrt(time_to_maturity));
    return result;
}

const double weightAsset(double asset_price, double option_d1) {
    normal s;
    double d1_probability = cdf(s, option_d1);
    return asset_price * d1_probability;
}

const double weightStrike(double option_strike, double option_d2, double rate, double time_to_maturity) {
    normal s;
    double d2_probability = cdf(s, option_d2);
    double discount_factor = continuous_discount_factor(rate, time_to_maturity);
    return option_strike * discount_factor * d2_probability;
}