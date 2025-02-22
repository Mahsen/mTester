/************************************************** Description
 * *******************************************************/
/*
    File : DO.cpp
    Programmer : Mohammad Lotfi
    Used : analize packet
    Design Pattern : none
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2025/2/22
*/
/************************************************** Warnings
 * **********************************************************/
/*
    Only for learning
*/
/************************************************** Wizards
 * ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes
 * **********************************************************/
#include "Do.hpp"
/************************************************** Defineds
 * **********************************************************/
/*
    Nothing
*/
/************************************************** Names
 * *************************************************************/
/*
    Nothing
*/
/************************************************** Variables
 * *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects
 * ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions
 * *********************************************************/
DO::Status DO::Analize(char *Request_Packet, int Request_Length,
                       void (*CallBack)(char *Respond_Packet)) {
  Status status;
  json Request_Data;
  json Respond_Data;
  string Respond_Packet;
  string Command;
  string Value;
  status = Status::Success;

  CallBack((char *)"Content-type: application/json\n\n");

  Request_Data = json::parse(Request_Packet);
  Command = Request_Data["Command"].get<std::string>();
  Respond_Data["Command"] = Command;
  Respond_Data["Value"] = "Command_Not_Find";
  if (Command == "TEST") {
    Value = "123456789";
    Respond_Data["Value"] = Value;
  }
  Respond_Packet = Respond_Data.dump();
  CallBack((char *)Respond_Packet.c_str());

  return status;
}
/************************************************** Tasks
 * *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors
 * ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
