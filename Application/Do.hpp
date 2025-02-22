#ifndef __DO_HPP
#define __DO_HPP
//----------------------------------------------------------
#include "Core/Define.hpp"
//----------------------------------------------------------
class DO {
    private:
        using json = nlohmann::json;
    public:
        json Request_Data;
        json Respond_Data;
        enum Status {
            Success=0,
            Failed,
            HIGH
        };
        Status Analize(char* Request_Packet, int Request_Length, void(*CallBack)(char* Respond_Packet));
};
extern DO Do;
#endif