//
// Created by Paulo Chang on 5/1/18.
//

#ifndef SQF_FLOATINGLEG_H
#define SQF_FLOATINGLEG_H

#include "Leg.h"
#include <algorithm>

//Clase que implementa una pata flotante
class FloatingLeg : public Leg {
    int periodsPerYear;
public:

    // Constructor (LLamamos al constructor de la superclase)
    FloatingLeg(double notional, std::vector<boost::gregorian::date> referenceDates,
                DayCountCalculator &dayCalculator, ZeroCouponCurve &zeroCouponCurve, int periodsPerYear) :
            Leg(notional, std::move(referenceDates), dayCalculator, zeroCouponCurve) {
        this->periodsPerYear = periodsPerYear;
    }

    std::vector<double> getLegCashFlows(std::vector<double> dayCountFractionVector) override;

    std::vector<double> getForwardRatesVector(std::vector<double> totalDayCountFractionVector);

    std::vector<double> getDiscreteFwdRatesVector(std::vector<double> forwardRatesVector);

};

#endif //SQF_FLOATINGLEG_H
