//
// Created by Paulo Chang on 6/20/18.
//

#ifndef SQF_CALLOPTION_H
#define SQF_CALLOPTION_H


#include <Instrument/Option.h>

class CallOption : public Option {

public :

    CallOption(double strike, double rate, const boost::gregorian::date &start_date,
               const boost::gregorian::date &end_date, DayCountCalculator &dayCalculator, Asset &underlying_asset);

    double getReceiving() const override;

    double getPaying() const override;
};


#endif //SQF_CALLOPTION_H
