//
// Created by Paulo Chang on 6/20/18.
//

#include "PutOption.h"
#include <Utils/bshelper.h>

PutOption::PutOption(double strike, double rate, const boost::gregorian::date &start_date,
                     const boost::gregorian::date &end_date, DayCountCalculator &dayCalculator,
                     Asset &underlying_asset) : Option(strike, rate, start_date, end_date, dayCalculator,
                                                       underlying_asset) {}

double PutOption::getReceiving() const {

    const double asset_price = m_Asset.price();
    const double asset_volatility = m_Asset.getVolatility();
    double d2_value = getD2(asset_price, m_strike, m_rate, asset_volatility, getTimeToMaturity());
    double weightedStrike = weightStrike(m_strike, -d2_value, m_rate, getTimeToMaturity());

    return weightedStrike;
}

double PutOption::getPaying() const {

    const double asset_price = m_Asset.price();
    const double asset_volatility = m_Asset.getVolatility();
    double d1_value = getD1(asset_price, m_strike, m_rate, asset_volatility, getTimeToMaturity());
    double weightedAsset = weightAsset(asset_price, -d1_value);

    return weightedAsset;
}