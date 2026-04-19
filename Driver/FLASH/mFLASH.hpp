
#pragma once
#include "mFLASH_data_template.hpp"

namespace maidui3_hal_FLASH{

class mFLASHfunction : mFLASHtemplate{
    public:
        State Init();
        State Write();
        State Read();
};

};

extern maidui3_hal_FLASH::mFLASHfunction mFLASH;
