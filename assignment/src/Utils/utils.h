#ifndef UTILS_H
#define UTILS_H

#include <vector>

/// Computes the discount factor corresponding to a given annual rate if discounted for a given number of years
/// and interests are being calculated once per year
/// \param annual_rate the yearly annual rate used to discount
/// \param years the number of years used to discount
/// \return the factor used to discount
const double annual_discount_factor(double annual_rate, double years);

/// Computes the discount factor corresponding to a given annual rate if discounted for a given number of years
/// and interests are being calculated more than once per year
/// \param annual_rate the yearly annual rate used to discount
/// \param periods_per_year the frecuency per year used to calculate interests
/// \param years the number of years used to discount
/// \return the factor used to discount
const double period_discount_factor(double annual_rate, int periods_per_year, double years);

/// Computes the discount factor corresponding to a given annual rate if discounted for a given number of years
/// and interests are being calculated continuously
/// \param continuous_rate the yearly continuous rate used to discount
/// \param years the number of years used to discount
/// \return the factor used to discount
const double continuous_discount_factor(double continuous_rate, double years);

/// Discounts a given amount with a given annual rate for a number of years
/// \param amount The amount to discount
/// \param annual_rate The yearly rate used to discount
/// \param years The number of years in which the discount will be calculated
/// \return the discounted amount
const double discount_annually(double amount, double annual_rate, double years);

/// Discounts a given amount given that the interests are calculated more than once per year
/// \param amount The amount to discount
/// \param annual_rate  The yearly reate used to discount
/// \param periods_per_year The times per year in which interests are calculated
/// \param years The number of years to discount
/// \return the discounted amount
const double discount_by_periods(double amount, double annual_rate, int periods_per_year, double years);

/// Discounts a given amount with a given annual rate for a number of years and the
/// interests are calculated continuously
/// \param amount The amount to discount
/// \param continuous_rate The yearly rate used to discount
/// \param years The number of years in which the discount will be calculated
/// \return the discounted amount
const double discount_continuously(double amount, double continuous_rate, double years);

/// Capitalizes a given amount with a given annual rate for a number of years
/// \param amount The amount to capitalize
/// \param annual_rate The yearly rate used to capitalize
/// \param years The number of years in which the capitalization will be calculated
/// \return the capitalized amount
const double annual_capitalization(double amount, double annual_rate, double years);

/// Capitalizes a given amount given that the interests are calculated more than once per year
/// \param amount The amount to capitalize
/// \param annual_rate  The yearly reate used to capitalize
/// \param periods_per_year The times per year in which interests are calculated
/// \param years The number of years to capitalize
/// \return the capitalized amount
const double period_capitalization(double amount, double annual_rate, int periods_per_year, double years);

/// Capitalizes a given amount with a given annual rate for a number of years
/// and supposing that the interests are being calculated continuously
/// \param amount The amount to capitalize
/// \param annual_rate The yearly rate used to capitalize
/// \param years The number of years in which the capitalization will be calculated
/// \return the capitalized amount
const double continuous_capitalization(double amount, double continuous_rate, double years);

/// Calculates the implied forward rate between to dates given their day count fraction and rates
/// \param zero_coupon_rate the final date rate according to the zero coupon curve
/// \param daycount_fraction the final day count fraction given a zero coupon curve
/// \param previous_zcrate the previous date rate according to the zero coupon curve
/// \param previous_dcf the previous day count fraction given a zero coupon curve
/// \return the implied forward rate
const double
forward_rate(double zero_coupon_rate, double daycount_fraction, double previous_zcrate, double previous_dcf);

/// Transforms from a yearly rate, given a number of capitalizations per year to a  continuous rate
/// \param periods_per_year the number of capitalization periods per year
/// \param annual_rate the original yearly rate
/// \return the continuous rate given the amount of periods per year defined
const double annual_to_continuous_rate(int periods_per_year, double annual_rate);

/// Transforms from a continuous rate to a yearly rate given a fixed number of capitalizations per year
/// \param periods_per_year the number of capitalization periods per year
/// \param continuous_rate the original yearly rate
/// \return the annual_rate given the amount of periods per year defined
const double continuous_to_annual_rate(int periods_per_year, double continuous_rate);

/// Creates a cummulative vector with the totalDayCountFraction till a certain point
/// \param dayCountFractionVector the dayCountFraction vector
/// \return the cummulated dayCountFractionVector
const std::vector<double> getTotalDayCountFractionVector(std::vector<double> dayCountFractionVector);

#endif 
