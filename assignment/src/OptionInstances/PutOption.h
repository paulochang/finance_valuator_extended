//
// Created by Paulo Chang on 6/20/18.
//

#ifndef SQF_PUTOPTION_H
#define SQF_PUTOPTION_H

#include <Instrument/Option.h>

class PutOption : public Option {

public :

    PutOption(double strike, double rate, const boost::gregorian::date &start_date,
              const boost::gregorian::date &end_date, DayCountCalculator &dayCalculator, Asset &underlying_asset);

    double getReceiving() const override;

    double getPaying() const override;
};


#endif //SQF_PUTOPTION_H
