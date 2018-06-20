//
// Created by Paulo Chang on 6/19/18.
//

#include "Asset.h"

double Asset::price() const {
    return m_spot_price;
}

Asset::Asset(double spot_price, double volatility) : Instrument(),
                                                     m_spot_price(spot_price), m_volatility(volatility) {}

double Asset::getVolatility() const {
    return m_volatility;
}
