/************************************************** Description
 * *******************************************************/
/*
    File : main.cpp
    Programmer : Mohammad Lotfi
    Used : main
    Design Pattern : none
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2025/1/26
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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <sys/stat.h>
#include <unistd.h>
#include <sqlite3.h>
#include "../Module/Print.hpp"
#include "../nlohmann/json.hpp"
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
void MAIN_Blink(void);
/************************************************** Opjects
 * ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions
 * *********************************************************/
/*// Function to get network interface type (Ethernet or Wireless)
std::string getInterfaceType(const std::string& iface) {
    std::ifstream iface_file("/sys/class/net/" + iface + "/type");
    if (iface_file.is_open()) {
        std::string type;
        std::getline(iface_file, type);
        iface_file.close();
        return type == "1" ? "Ethernet" : "Wireless";  // '1' indicates Ethernet type
    }
    return "Unknown";
}
// Function to get network interface status (up/down)
std::string getInterfaceStatus(const std::string& iface) {
    std::ifstream status_file("/sys/class/net/" + iface + "/operstate");
    if (status_file.is_open()) {
        std::string status;
        std::getline(status_file, status);  // Read the status (e.g., "up" or "down")
        status_file.close();
        return status;
    }
    return "Unknown";  // If the status file is not available, return "Unknown"
}
// Function to parse /proc/net/dev for TX and RX stats
cJSON* getNetworkInterfaces() {
    std::ifstream file("/proc/net/dev");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open /proc/net/dev" << std::endl;
        return nullptr;
    }

    std::string line;
    std::map<std::string, std::pair<long, long>> stats; // {interface: {RX bytes, TX bytes}}

    // Skip the first two lines (headers)
    std::getline(file, line);
    std::getline(file, line);

    // Parse the file for network interface stats
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string iface;
        long rx_bytes, tx_bytes;
        ss >> iface;  // Read interface name
        ss.ignore(256, ':');  // Ignore the ':' after the interface name

        // Read RX and TX bytes
        ss >> rx_bytes >> rx_bytes >> tx_bytes >> tx_bytes;

        // Remove any extra spaces and the trailing colon from the interface name
        iface = iface.substr(0, iface.find(':'));

        stats[iface] = {rx_bytes, tx_bytes};
    }

    file.close();

    // Print the statistics for each interface
    cJSON *json_Respose  = cJSON_CreateObject();        
    cJSON *json_Return  = cJSON_CreateObject();       
    cJSON *json_Data = cJSON_CreateArray(); 
    cJSON_AddStringToObject(json_Return, "State", "Ok");
    for (const auto& stat : stats) {
        const std::string& iface = stat.first;
        std::string rx_bytes = std::to_string(stat.second.first);
        std::string tx_bytes = std::to_string(stat.second.second);

        // Get the interface type (Ethernet or Wireless)
        std::string iface_type = getInterfaceType(iface);

        // Get the interface status (up/down)
        std::string iface_status = getInterfaceStatus(iface);

        cJSON *json_Elm = cJSON_CreateObject(); 
        cJSON_AddStringToObject(json_Elm, "Name", iface.c_str());
        cJSON_AddStringToObject(json_Elm, "Type", iface_type.c_str());
        cJSON_AddStringToObject(json_Elm, "TX", tx_bytes.c_str());
        cJSON_AddStringToObject(json_Elm, "RX", rx_bytes.c_str());
        cJSON_AddStringToObject(json_Elm, "Status", iface_status.c_str());
        cJSON_AddItemToArray(json_Data, json_Elm);   
    }
    cJSON_AddItemToObject(json_Return, "Data", json_Data); 
    cJSON_AddItemToObject(json_Respose, "Return", json_Return);

    return json_Respose;
}*/
/*--------------------------------------------------------------------------------------------------------------------*/
// Callback function to process query results
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        Print((char*)azColName[i]);
        Print((char*)" = ");
        Println((char*)(argv[i] ? argv[i] : "NULL"));
    }
    Println((char*)"----------------------");
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* The main function start of program in cpp language */
int main() {
Println((char *)"Application: Start");

    sqlite3* db;
    char* errorMessage = 0;

    // Open database (creates if not exists)
    if (sqlite3_open("database.db", &db)) {
        Print((char*)"Error opening database: ");
        Println((char*)sqlite3_errmsg(db));
        return 1;
    }

    // SQL commands
    const char* sqlClearData = "DELETE FROM Users;";
    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY, Name TEXT, Age INTEGER);";
    const char* sqlInsertData = "INSERT INTO Users (Name, Age) VALUES ('Mohammad', 21), ('Zohre', 20);";
    const char* sqlSelectData = "SELECT * FROM Users;";

    // Execute SQL statements
    sqlite3_exec(db, sqlClearData, 0, 0, &errorMessage);
    sqlite3_exec(db, sqlCreateTable, 0, 0, &errorMessage);
    sqlite3_exec(db, sqlInsertData, 0, 0, &errorMessage);
    sqlite3_exec(db, sqlSelectData, callback, 0, &errorMessage);

    // Close database
    sqlite3_close(db);
    return 0;

/*
    // Get the content length
    //char buffer[1024];
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;

    Print((char*)"Content-type: application/json\n\n");

    if (content_length > 0) {
        // Read the JSON payload
        char *json_payload = (char *)malloc(content_length + 1);
        fread(json_payload, 1, content_length, stdin);
        json_payload[content_length] = '\0';

        // Parse the JSON
        cJSON *json = cJSON_Parse(json_payload);
        if (!json) {
            Print((char*)"{\"error\": \"Invalid JSON\"}\n");
            free(json_payload);
            system("echo 0 > ../../sys/class/leds/cubieboard2:green:usr/brightness");
            return 1;
        }

        // Extract values from JSON
        cJSON *Task = cJSON_GetObjectItemCaseSensitive(json, "Task");        

        if(strcmp(Task->valuestring, "get-network-interfaces")==0){
            Print (cJSON_Print(getNetworkInterfaces()));
        }

        // Clean up
        cJSON_Delete(json);
        free(json_payload);
    } else {
        Print((char*)"{\"error\": \"No data received\"}\n");
    }

    */

    //Print((char*)"{\"error\": \"No data received\"}\n");
    //return 0;
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
