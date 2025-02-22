#ifndef __DO_HPP
#define __DO_HPP
//----------------------------------------------------------
#include "Core/Define.hpp"
//----------------------------------------------------------
class DO {
    private:
        using json = nlohmann::json;
    public:
        enum Status {
            Success=0,
            Failed,
            HIGH
        };
        Status Analize(char* Request_Packet, int Request_Length, void(*CallBack)(char* Respond_Packet));
};
#endif