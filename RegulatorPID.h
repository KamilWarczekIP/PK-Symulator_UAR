#ifndef REGULATOR_PID_H
#define REGULATOR_PID_H

/**
 * @brief
 *
 */
enum class IntegType {
    outside,
    insde,
};

/**
 * @brief
 *
 */
class RegulatorPID
{
    double k; /**< TODO: describe */
    double T_i; /**< TODO: describe */
    double T_d; /**< TODO: describe */
    double sum_of_e_inside_integ; /**< TODO: describe */
    double sum_of_e_outside_integ; /**< TODO: describe */
    double previous_e; /**< TODO: describe */
    IntegType integration_type; /**< TODO: describe */

public:
    /**
     * @brief
     *
     * @param e_i
     * @return double
     */
double tick(double e_i);
    /**
     * @brief
     *
     * @param k
     * @param T_i
     * @param T_d
     * @param integration_type
     */
    RegulatorPID(double k,
                 double T_i = 0.0,
                 double T_d = 0.0,
                 IntegType integration_type = IntegType::outside);
    /**
     * @brief
     *
     * @param k
     */
void setK(double k);
    /**
     * @brief
     *
     * @param T_i
     */
void setT_i(double T_i);
    /**
     * @brief
     *
     * @param T_d
     */
void setT_d(double T_d);
    /**
     * @brief
     *
     * @param integ_type
     */
void setIntegrationType(IntegType integ_type);
    /**
     * @brief
     *
     * @return IntegType
     */
IntegType getIntegrationType() const;
    /**
     * @brief
     *
     * @return double
     */
double getK() const;
    /**
     * @brief
     *
     * @return double
     */
double getT_i() const;
    /**
     * @brief
     *
     * @return double
     */
double getT_d() const;
    /**
     * @brief
     *
     */
void resetIntegrationPart();
    /**
     * @brief
     *
     */
void resetDerrivativePart();
    /**
     * @brief
     *
     */
void reset();
};

#endif // REGULATOR_PID_H
