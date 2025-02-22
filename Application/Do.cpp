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
DO Do;
/************************************************** Functions
 * *********************************************************/
// Callback function to process query results
static int sqlite3_exe_callback(void *NotUsed, int argc, char **argv,
                                char **azColName) {
  Do.Respond_Data["Value"].push_back(string((char *)argv[1]) + ":" +
                                     string((char *)argv[2]));
  return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
DO::Status DO::Analize(char *Request_Packet, int Request_Length,
                       void (*CallBack)(char *Respond_Packet)) {
  Status status;
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
    Respond_Data["Value"] = "OK";
  } else if (Command == "ADD_DEVICE") {
    sqlite3 *db;
    char *errorMessage = 0;
    /* Split IP:PORT */
    Value = Request_Data["Value"].get<std::string>();
    vector<string> IP_Port = DEFINE_split(Value, ':');
    // Open database (creates if not exists)
    if (sqlite3_open("database.db", &db)) {
      status = Status::Failed;
      return status;
    }
    /* Create Table if not exist */
    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Testers (ID INTEGER PRIMARY KEY, IP TEXT, "
        "Port INTEGER, Name TEXT);";
    sqlite3_exec(db, sqlCreateTable, 0, 0, &errorMessage);
    /* Insert to DB */
    string sqlInsertData = "INSERT INTO Testers (IP, Port, Name) VALUES ('" +
                           IP_Port[0] + "', " + IP_Port[1] + ", '" + "Tester-" +
                           IP_Port[0] + "');";
    sqlite3_exec(db, sqlInsertData.c_str(), 0, 0, &errorMessage);
    sqlite3_close(db);
  } else if (Command == "GET_DEVICES") {
    sqlite3 *db;
    char *errorMessage = 0;
    // Open database (creates if not exists)
    if (sqlite3_open("database.db", &db)) {
      status = Status::Failed;
      return status;
    }
    char *sqlSelectData = "SELECT * FROM Testers;";
    Respond_Data["Value"] = nlohmann::json::array();
    sqlite3_exec(db, sqlSelectData, sqlite3_exe_callback, 0, &errorMessage);
    sqlite3_close(db);
  } else if (Command == "RM_DEVICE") {
    sqlite3 *db;
    char *errorMessage = 0;
    /* Split IP:PORT */
    Value = Request_Data["Value"].get<std::string>();
    vector<string> IP_Port = DEFINE_split(Value, ':');
    // Open database (creates if not exists)
    if (sqlite3_open("database.db", &db)) {
      status = Status::Failed;
      return status;
    }
    /* remove record of Table */
    string sqlRMTable = "DELETE FROM Testers WHERE IP = '" + IP_Port[0] +
                        "' AND Port = " + IP_Port[1] + ";";
    sqlite3_exec(db, sqlRMTable.c_str(), 0, 0, &errorMessage);
    sqlite3_close(db);
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
