
#pragma once
#include "mXCAN.hpp"

namespace Multiple_ch_MD_v1 {

class multiple_ch_md_v1
{
public:
    multiple_ch_md_v1(maidui3_hal::Drivers::XCAN::xcan can_bus);

    bool Send();
    bool Get();
};

}  // namespace Multiple_ch_MD_v1

extern Multiple_ch_MD_v1::multiple_ch_md_v1 multi_ch_md;