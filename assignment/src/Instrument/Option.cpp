//
// Created by Paulo Chang on 6/19/18.
//

#include "Option.h"

double Option::price() const {
    return getReceiving() - getPaying();
}

double Option::getTimeToMaturity() const {
    return m_dayCalculator.getDayRatio(m_start_date, m_end_date);
}

Option::Option(double strike, double rate, const boost::gregorian::date &start_date,
               const boost::gregorian::date &end_date,
               DayCountCalculator &dayCalculator, Asset &underlying_asset) : Instrument(),
                                                                             m_strike(strike), m_rate(rate),
                                                                             m_start_date(start_date),
                                                                             m_end_date(end_date),
                                                                             m_dayCalculator(dayCalculator),
                                                                             m_Asset(underlying_asset) {}
