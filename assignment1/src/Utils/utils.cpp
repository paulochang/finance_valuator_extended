#include "utils.h"
#include <cmath>

double annual_discount_factor(double annual_rate, double years) {
    double cap_per_year = 1 + annual_rate;
    return pow(cap_per_year, -years);
}

double period_discount_factor(double annual_rate, int periods_per_year, double years) {
    double cap_per_period = (1 + annual_rate / periods_per_year);
    double total_periods = periods_per_year * years;
    return pow(cap_per_period, -total_periods);
}

double continuous_discount_factor(double continuous_rate, double years) {
    return exp(-1 * continuous_rate * years);
}

double discount_annually(double amount, double annual_rate, double years) {
    double discount_rate = annual_discount_factor(annual_rate, years);
    double result = amount * discount_rate;
    return result;
}

double discount_by_periods(double amount, double annual_rate, int periods_per_year, double years) {
    double discount_rate = period_discount_factor(annual_rate, periods_per_year, years);
    double result = amount * discount_rate;
    return result;
}

double discount_continuously(double amount, double continuous_rate, double years) {
    double discount_rate = continuous_discount_factor(continuous_rate, years);
    double result = amount * discount_rate;
    return result;
}

double annual_capitalization(double amount, double annual_rate, double years) {
    double capitalization_rate = 1.0 / annual_discount_factor(annual_rate, years);
    double result = amount * capitalization_rate;
    return result;
}

double period_capitalization(double amount, double annual_rate, int periods_per_year, double years) {
    double capitalization_rate = 1.0 / period_discount_factor(annual_rate, periods_per_year, years);
    double result = amount * capitalization_rate;
    return result;
}

double continuous_capitalization(double amount, double continuous_rate, double years) {
    double capitalization_rate = 1.0 / continuous_discount_factor(continuous_rate, years);
    double result = amount * capitalization_rate;
    return result;
}

double forward_rate(double zero_coupon_rate, double daycount_fraction, double previous_zcrate, double previous_dcf) {
    double diff_performance = zero_coupon_rate * daycount_fraction - previous_zcrate * previous_dcf;
    double diff_periods = daycount_fraction - previous_dcf;
    return diff_performance / diff_periods;
}

double annual_to_continuous_rate(int periods_per_year, double annual_rate) {
    return periods_per_year * log(1 + annual_rate / periods_per_year);
}

double continuous_to_annual_rate(int periods_per_year, double continuous_rate) {
    return periods_per_year * (exp(continuous_rate / periods_per_year) - 1);
}

std::vector<double> getTotalDayCountFractionVector(std::vector<double> dayCountFractionVector) {
    std::vector<double> totalDayCountFractionVector{};
    totalDayCountFractionVector.reserve(dayCountFractionVector.size() - 1);
    double cummulator = 0.0;
    for (unsigned int i = 0; i < dayCountFractionVector.size(); i++) {
        cummulator += dayCountFractionVector.at(i);
        totalDayCountFractionVector.emplace_back(cummulator);
    }

    return totalDayCountFractionVector;
}