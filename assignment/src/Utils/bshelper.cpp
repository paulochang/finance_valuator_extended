#include "utils.h"
#include "bshelper.h"
#include <cmath>
#include <boost/math/distributions/normal.hpp>

using boost::math::normal;

const double getD1(double asset_price, double strike, double rate, double volatility, double time_to_maturity) {
    double unadjusted_d1 = log(asset_price / strike) + (rate + pow(volatility, 2) / 2) * time_to_maturity;
    double result = unadjusted_d1 / (volatility * sqrt(time_to_maturity));
    return result;
}

const double getD2(double asset_price, double strike, double rate, double volatility, double time_to_maturity) {
    double unadjusted_d2 = log(asset_price / strike) + (rate - pow(volatility, 2) / 2) * time_to_maturity;
    double result = unadjusted_d2 / (volatility * sqrt(time_to_maturity));
    return result;
}

const double weightAsset(double asset_price, double option_d1) {
    normal normalDistInstance;
    double d1_probability = cdf(normalDistInstance, option_d1);
    return asset_price * d1_probability;
}

const double weightStrike(double option_strike, double option_d2, double rate, double time_to_maturity) {
    normal normalDistInstance;
    double d2_probability = cdf(normalDistInstance, option_d2);
    double discount_factor = continuous_discount_factor(rate, time_to_maturity);
    return option_strike * discount_factor * d2_probability;
}


const double
evaluateCall(double option_strike, double time_to_maturity, double rate, double volatility, double asset_price) {
    double d1_value = getD1(asset_price, option_strike, rate, volatility, time_to_maturity);
    double d2_value = getD2(asset_price, option_strike, rate, volatility, time_to_maturity);

    double weighted_asset = weightAsset(asset_price, d1_value);
    double weighted_strike = weightStrike(option_strike, d2_value, rate, time_to_maturity);

    return weighted_asset - weighted_strike;
}

const double
evaluatePut(double option_strike, double time_to_maturity, double rate, double volatility, double asset_price) {
    double d1_value = getD1(asset_price, option_strike, rate, volatility, time_to_maturity);
    double d2_value = getD2(asset_price, option_strike, rate, volatility, time_to_maturity);

    double weighted_asset = weightAsset(asset_price, -d1_value);
    double weighted_strike = weightStrike(option_strike, -d2_value, rate, time_to_maturity);

    return weighted_strike - weighted_asset;
}

const double
blackScholes(enum OptionType option_type, double option_strike, double time_to_maturity, double rate, double volatility,
             double asset_price) {
    switch (option_type) {
        case call:
            return evaluateCall(option_strike, time_to_maturity, rate, volatility, asset_price);
        case put:
            return evaluatePut(option_strike, time_to_maturity, rate, volatility, asset_price);
    }
    return 0;
}