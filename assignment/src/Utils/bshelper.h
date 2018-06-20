#ifndef BSHELPER_H
#define BSHELPER_H

enum OptionType {
    call, put
};

/// Computes the d1 or d+ component of the option's black-scholes pricing model
/// \param asset_price The underlying asset's price
/// \param strike The option strike price if the exercise is completed.
/// \param rate The discount rate used to calculate the option present value
/// \param volatility The underlying asset's volatility
/// \param time_to_maturity The remaining time for the option to reach maturity
/// \return the result of the d1 calculation
const double getD1(double asset_price, double strike, double rate, double volatility, double time_to_maturity);

/// Computes the d2 or d- component of the option's black-scholes pricing model
/// \param asset_price The underlying asset's price
/// \param strike The option strike price if the exercise is completed.
/// \param rate The discount rate used to calculate the option present value
/// \param volatility The underlying asset's volatility
/// \param time_to_maturity The remaining time for the option to reach maturity
/// \return the result of the d2 calculation
const double getD2(double asset_price, double strike, double rate, double volatility, double time_to_maturity);

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

/// Computes the option price using the Black-Scholes model
/// \param option_type The kind of option to value
/// \param option_strike The option strike value
/// \param time_to_maturity The remaining time for the option to reach maturity
/// \param rate The yearly discount rate used to calculate the option present value
/// \param volatility The underlying asset's volatility
/// \param asset_price The underlying asset's price
/// \return the price of the option according to the Black-Scholes model
const double
blackScholes(enum OptionType option_type, double option_strike, double time_to_maturity, double rate, double volatility,
             double asset_price);

/// Computes a CALL option price using the Black-Scholes model
/// \param option_strike The call strike value
/// \param time_to_maturity The remaining time for the call to reach maturity
/// \param rate The yearly discount rate used to calculate the option present value
/// \param volatility The underlying asset's volatility
/// \param asset_price The underlying asset's price
/// \return the price of the call option according to the Black-Scholes model
const double
evaluateCall(double option_strike, double time_to_maturity, double rate, double volatility, double asset_price);

/// Computes a PUT option price using the Black-Scholes model
/// \param option_strike The put strike value
/// \param time_to_maturity The remaining time for the put to reach maturity
/// \param rate The yearly discount rate used to calculate the put option present value
/// \param volatility The underlying asset's volatility
/// \param asset_price The underlying asset's price
/// \return the price of the put option according to the Black-Scholes model
const double
evaluatePut(double option_strike, double time_to_maturity, double rate, double volatility, double asset_price);

#endif
