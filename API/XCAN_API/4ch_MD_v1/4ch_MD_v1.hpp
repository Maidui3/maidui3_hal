
#pragma once
#include "mXCAN.hpp"

namespace Multiple_ch_MD_v1 {

class multiple_ch_md_v1
{
private:
    maidui3_hal::Drivers::XCAN::xcan& can_bus_;

public:
    multiple_ch_md_v1(maidui3_hal::Drivers::XCAN::xcan& _can_bus) : can_bus_(_can_bus)
    {
        can_bus_.init(maidui3_hal::Drivers::XCAN::receive_id_filter::only_four_id);
    };

    bool Send();
    bool Get();
};

}  // namespace Multiple_ch_MD_v1

extern Multiple_ch_MD_v1::multiple_ch_md_v1 multi_ch_md;