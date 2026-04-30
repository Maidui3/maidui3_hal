
#include "4ch_MD_v1.hpp"

namespace Multiple_ch_MD_v1 {

bool multiple_ch_md_v1::Send()
{
    can_bus_.SendMessage(NULL);
}

bool multiple_ch_md_v1::Get()
{
    can_bus_.GetMessage(NULL);
}

}  // namespace Multiple_ch_MD_v1