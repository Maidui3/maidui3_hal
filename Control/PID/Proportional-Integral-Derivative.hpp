
#pragma once

#include <cstdint>

namespace maidui3_hal {
namespace Control {
namespace PID {
class Proportional_Integral_Derivative
{
private:
    float Kp;  // p gain
    float Ki;  // i gain
    float Kd;  // d gain

    float sum_deviation;
    float last_deviation;

    float control_cycle;

public:
    void set_gain(float Kp_, float Ki_, float Kd_);

    void set_control_cycle(uint16_t cycle);

    void reset_deviation();

    float PID(float deviation);

    float P(float deviation);

    float I(float deviation);

    float D(float deviation);
};
}  // namespace PID
}  // namespace Control
}  // namespace maidui3_hal