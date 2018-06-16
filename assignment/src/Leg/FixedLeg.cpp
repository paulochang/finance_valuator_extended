#include "FixedLeg.h"

/**
 * Implementacion de la clase 'FixedLeg' que representa los pagos fijos
 * Para calcular los flujos de caja se necesitan saber los periodos de pago, para calcular las fracciones de año
 * El interes esta acordado previamente y se supone que es en la duracion de los periodos de pago,
 * las clases superiores se ocuparan de calcularlo.
 */


std::vector<double> FixedLeg::getLegCashFlows(std::vector<double> dayCountFractionVector) {
    std::vector<double> legCashFlows{};

    legCashFlows.reserve(dayCountFractionVector.size());
    for (auto currentFraction : dayCountFractionVector)
        legCashFlows.emplace_back(m_rate * currentFraction * m_notional);
    return legCashFlows;
}

