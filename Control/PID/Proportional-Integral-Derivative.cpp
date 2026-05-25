
#include "Proportional-Integral-Derivative.hpp"

namespace maidui3_hal {
namespace Control {
namespace PID {

void Proportional_Integral_Derivative::set_gain(float Kp_, float Ki_, float Kd_)
{
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    return;
}

void Proportional_Integral_Derivative::set_control_cycle(uint16_t cycle)
{
    control_cycle = 1 / (float)(cycle);
}

void Proportional_Integral_Derivative::reset_deviation()
{
    sum_deviation = 0;
}

float Proportional_Integral_Derivative::PID(float deviation)
{
    return P(deviation) + I(deviation) + D(deviation);
}

float Proportional_Integral_Derivative::P(float deviation)
{
    return Kp * deviation;
}

float Proportional_Integral_Derivative::I(float deviation)
{
    sum_deviation += deviation;
    return Ki * sum_deviation * control_cycle;
}

float Proportional_Integral_Derivative::D(float deviation)
{
    static float return_value;
    return_value   = Kd * (deviation - last_deviation) * control_cycle;
    last_deviation = deviation;
    return return_value;
}

}  // namespace PID
}  // namespace Control
}  // namespace maidui3_hal