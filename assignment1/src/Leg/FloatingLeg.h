//
// Created by Paulo Chang on 5/1/18.
//

#ifndef SQF_FLOATINGLEG_H
#define SQF_FLOATINGLEG_H

#include <Leg/ZeroCurve/ZeroCouponCurve.h>
#include <algorithm>
#include "Leg.h"

//Clase que implementa una pata flotante
class FloatingLeg : public Leg {
    int periodsPerYear;
public:

    // Constructor (LLamamos al constructor de la superclase)
    FloatingLeg(double notional, double rates, std::vector<boost::gregorian::date> referenceDates,
                DayCountCalculator &dayCalculator, ZeroCouponCurve &zeroCouponCurve, int periodsPerYear) :
            Leg(notional, rates, std::move(referenceDates), dayCalculator, zeroCouponCurve) {
        this->periodsPerYear = periodsPerYear;
    }

    std::vector<double> getLegCashFlows(std::vector<double> dayCountFractionVector) override;

    std::vector<double> getForwardRatesVector(std::vector<double> totalDayCountFractionVector);

};

#endif //SQF_FLOATINGLEG_H
