#ifndef BTIME_H
#define BTIME_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
/**
 * Clase que implementa un calculador de dias entre dos fechas usando un calendario gregoriano mediante la libreria
 * Boost.
 * Las fechas se pasan bien por string o bien por un objeto tipo boost::gregorian::date.
 * Tambien tiene un atributo llamado 'nDaysYear()' que indica el número de días que tiene un año (por ejemplo en el convenio 30/360 un año tiene 360 dias). Este
 * atributo sera inicializado por las clases hijas y se puede acceder a traves del metodo miembro 'getNDaysYear()'
 */

//Constantes utiles
const int N_DAYS_ACTUAL_360 = 360;
const int N_DAYS_THIRTY_360 = 360;

//Clase principal
class DayCountCalculator {
private:

    //Dias que tiene un año segun el convenio instanciado
    int nDaysYear;
public:

    //Constructor.Recibe el numero de dias que tiene un año
    explicit DayCountCalculator(int eNDaysYear) : nDaysYear{eNDaysYear} {}

    //Metodo para obtener el numero de dias a partir de un par de fechas en strings o por boost::gregorian::date (DD/MM/YYYY)
    double compute_daycount(const std::string &string_from, const std::string &string_to) const {
        boost::gregorian::date from_date{boost::gregorian::from_string(string_from)};
        boost::gregorian::date to_date{boost::gregorian::from_string(string_to)};
        return compute_daycount(from_date, to_date);
    }


    //Metodo para compuatr el numero de dias a partir de objetos boos::gregorian::date
    virtual double compute_daycount(const boost::gregorian::date &bfrom, const boost::gregorian::date &bto) const = 0;

    //Obtiene el numero de dias que hay en un año
    int getNDaysYear() const {
        return nDaysYear;
    };

    double getDayRatio(const boost::gregorian::date &start_period, const boost::gregorian::date &end_period) const {
        return compute_daycount(start_period, end_period) / getNDaysYear();
    }
};

//Clases hija Actual/360
class Actual_360 : public DayCountCalculator {

public:

    //Constructor.
    Actual_360();

    //Definicion del metodo privado para computar el numero de dias a partir de un objeto boos::gregorian::date
    double compute_daycount(const boost::gregorian::date &bfrom, const boost::gregorian::date &bto) const override;

};

//Clases hija Actual/360
class Thirty_360 : public DayCountCalculator {
private:
    //Metodo auxiliar para el calculo de los dias en 30/360
    double
    compute_daycount(short years, short months, short days_from, short days_to) const;

public:


    //Definicion del metodo privado para computar el numero de dias a partir de un objeto boos::gregorian::date
    double compute_daycount(const boost::gregorian::date &bfrom, const boost::gregorian::date &bto) const override;

    //Constructor.
    Thirty_360();
};

#endif
