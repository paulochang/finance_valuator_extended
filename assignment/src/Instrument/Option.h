//
// Created by Paulo Chang on 6/19/18.
//

#ifndef OPTION_H
#define OPTION_H

#include "Instrument.h"
#include "Asset.h"

class Option : public Instrument {
protected:
    double m_strike;
    double m_rate;
    boost::gregorian::date m_start_date;
    boost::gregorian::date m_end_date;
    DayCountCalculator &m_dayCalculator;
    Asset &m_Asset;

    virtual double getReceiving() const = 0;

    virtual double getPaying() const = 0;

public:

    Option(double strike, double rate, const boost::gregorian::date &start_date, const boost::gregorian::date &end_date,
           DayCountCalculator &dayCalculator, Asset &underlyingAsset);

    double price() const override;

    double getTimeToMaturity() const;
};


#endif //OPTION_H
