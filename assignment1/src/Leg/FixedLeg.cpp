#include "FixedLeg.h"

/**
 * Implementacion de la clase 'FixedLeg' que representa los pagos fijos
 * Para calcular los flujos de caja se necesitan saber los periodos de pago, para calcular las fracciones de año
 * El interes esta acordado previamente y se supone que es en la duracion de los periodos de pago,
 * las clases superiores se ocuparan de calcularlo.
 */


std::vector<double> FixedLeg::getLegCashFlows(std::vector<double> dayCountFractionVector){
    std::vector<double> legCashFlows{};

    legCashFlows.reserve(dayCountFractionVector.size());
    for (auto currentFraction : dayCountFractionVector)
        legCashFlows.emplace_back(m_rate * currentFraction * m_notional);
    return legCashFlows;
}

//Clase FixedLeg
double FixedLeg::price() {

    // TESTED
    //Generate day count fraction vector
    std::vector<double> dayCountFractionVector{getDayCountFractionVector()};

    // TESTED
    //Calculate the legCashFlows
    std::vector<double> legCashFlows{getLegCashFlows(dayCountFractionVector)};

    //Calculate discount factors
    std::vector<double> legDiscountFactors(getDiscountFactors(dayCountFractionVector));

    //Sum up discounted cashflows
    double totalDiscountedValue = getDiscountedValue(legDiscountFactors, legCashFlows);

    return totalDiscountedValue;
}

double FixedLeg::estimate_price(double interestRate) {
    //Generate day count fraction vector
    std::vector<double> dayCountFractionVector{getDayCountFractionVector()};

    std::vector<double> legCashFlows{};
    legCashFlows.reserve(dayCountFractionVector.size());
    for (auto currentFraction : dayCountFractionVector)
        legCashFlows.emplace_back(interestRate * currentFraction * m_notional);

    //Calculate discount factors
    std::vector<double> legDiscountFactors(getDiscountFactors(dayCountFractionVector));

    //Sum up discounted cashflows
    double totalDiscountedValue = getDiscountedValue(legDiscountFactors, legCashFlows);

    return totalDiscountedValue;
};
