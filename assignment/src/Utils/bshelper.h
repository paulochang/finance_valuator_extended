#ifndef BSHELPER_H
#define BSHELPER_H

/// Computes the d1 or d+ component of the option's black-scholes pricing model
/// \param asset_price The underlying asset's price
/// \param strike The option strike price if the exercise is completed.
/// \param rate The discount rate used to calculate the option present value
/// \param volatility The underlying asset's volatility
/// \param time_to_maturity The remaining time for the option to reach maturity
/// \return the result of the d1 calculation
const double d1(double asset_price, double strike, double rate, double volatility, double time_to_maturity);

/// Computes the d2 or d- component of the option's black-scholes pricing model
/// \param asset_price The underlying asset's price
/// \param strike The option strike price if the exercise is completed.
/// \param rate The discount rate used to calculate the option present value
/// \param volatility The underlying asset's volatility
/// \param time_to_maturity The remaining time for the option to reach maturity
/// \return the result of the d2 calculation
const double d2(double asset_price, double strike, double rate, double volatility, double time_to_maturity);

/// Weights the underliying asset contribution to the option price
/// \param asset_price The underlying asset's price
/// \param option_d1 the calculated d1 value for this option
/// \return the asset price weighted contribution to the option price
const double weightAsset(double asset_price, double option_d1);

/// Weights the option strike contribution to the option price
/// \param option_strike The option strike
/// \param option_d2 the calculated d2 value for this option
/// \param rate The discount rate used to calculate the option present value
/// \param time_to_maturity The remaining time for the option to reach maturity
/// \return the strike's weighted contribution to the option price
const double weightStrike(double option_strike, double option_d2, double rate, double time_to_maturity);

#endif
