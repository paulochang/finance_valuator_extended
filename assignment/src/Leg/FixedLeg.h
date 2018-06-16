//
// Created by Paulo Chang on 5/1/18.
//

#ifndef SQF_FIXEDLEG_H
#define SQF_FIXEDLEG_H

#include "Leg.h"

//Clase que implementa una pata fijado
class FixedLeg : public Leg {

    double m_rate;
public:

    // Constructor (LLamamos al constructor de la superclase)
    FixedLeg(double notional, double rate, std::vector<boost::gregorian::date> referenceDates,
             DayCountCalculator &dayCalculator, ZeroCouponCurve &zeroCouponCurve)
            :
            Leg(notional, std::move(referenceDates), dayCalculator, zeroCouponCurve),
            m_rate{rate} {}

    std::vector<double> getLegCashFlows(std::vector<double> dayCountFractionVector) override;
};

#endif //SQF_FIXEDLEG_H
