#ifndef LEG_H
#define LEG_H

#include <string>
#include <utility>
#include <vector>
#include <Leg/ZeroCurve/ZeroCouponCurve.h>
#include "Btime/DayCountCalculator.h"
#include <Utils/utils.h>

/**
 * Clase que representa una pata de un instrumento financiero.
 * Una pata de un instrumento financiero se considera una serie de peridos en un intervalo de tiempo concreto
 * Para calcular el precio de una pata hace falta el nocional o nominal principal, el interes fijado (en caso de
 * ser una pata flotante, se necesita una curva de interes, que implementa la subclase 'Floating Leg'), las fechas
 * de inicio y fin y el numero de subperiodos que consta el periodo principal (en esta practica se considera un año)
 * NOTA: El interes proporcionado se asume que es acorde al subperiodo concreto (si son dos subperiosos, el interes es semianual,
 * si son 3 subperiodos el interes es trimestarl, etc). Respecto a las fechas, estas deben ser ordenadas de menor a mayor y la primera
 * fecha se corresponde a la fecha de acuerdo del instrumento (bono o swap) y el resto son las fechas correspondientes al pago de flujos
 */


//Clase prinbcipal

class Leg {
protected:
    double m_notional;
    double m_rate;
    std::vector<boost::gregorian::date> m_payingDates;
    DayCountCalculator &m_dayCalculator;
    ZeroCouponCurve &m_zeroCouponCurve;

    virtual std::vector<double> getLegCashFlows(std::vector<double> dayCountFractionVector) = 0;

public:

    /// Creates a base Leg object
    /// \param notional the principal amount of the leg
    /// \param rate represents the fixed rate in a fixed leg requirement or the first "real" rate in floating lets
    /// \param referenceDates a vector with the reference dates (first date is start date, last date is end date)
    /// \param dayCalculator the kind of days calculator to use (depends on convention)
    Leg(double notional, double rate, std::vector<boost::gregorian::date> referenceDates,
        DayCountCalculator &dayCalculator, ZeroCouponCurve &zeroCouponCurve) :
            m_notional{notional}, m_rate{rate}, m_payingDates{std::move(referenceDates)},
            m_dayCalculator{dayCalculator}, m_zeroCouponCurve{zeroCouponCurve} {}

    //Destructor
    virtual ~Leg();

    //Metodo abstracto para calcular el precio de una pata
    virtual double price() = 0;

    virtual double estimate_price(double x) = 0;

    /// Retrieves a vector with the day count fractions between payments
    /// \return the vector with the day count fractions
    std::vector<double> getDayCountFractionVector();

    std::vector<double> getDiscountFactors(std::vector<double> dayCountFractionVector);

    double getDiscountedValue(std::vector<double> &dayCountFractionVector, std::vector<double> &legDiscountFactors,
                              std::vector<double> &legCashFlows);
};

#endif
