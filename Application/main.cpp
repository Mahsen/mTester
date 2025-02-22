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
#include "Core/Define.hpp"
#include "Do.hpp"
#include "Module/Print.hpp"
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

/*--------------------------------------------------------------------------------------------------------------------*/
// Callback function to process query results
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  for (int i = 0; i < argc; i++) {
    Print((char *)azColName[i]);
    Print((char *)" = ");
    Println((char *)(argv[i] ? argv[i] : "NULL"));
  }
  Println((char *)"----------------------");
  return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* The main function start of program in cpp language */
int main() {
  /* Get the content data by length */
  char *Packet_Length_str = getenv("CONTENT_LENGTH");
  int Packet_Length = Packet_Length_str ? atoi(Packet_Length_str) : 0;
  if (Packet_Length > 0) {
    char *Packet_Request = (char *)malloc(Packet_Length + 1);
    fread(Packet_Request, 1, Packet_Length, stdin);
    Packet_Request[Packet_Length] = '\0';
    /* send data to analize module */
    DO::Status status = Do.Analize(Packet_Request, Packet_Length, Print);
    return status;
  } else {
    Print((char *)"Content-type: application/json\n\n");
    Print((char *)"{\"error\": \"No data received\"}\n");
  }

  /*
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
      const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Users (ID INTEGER
     PRIMARY KEY, Name TEXT, Age INTEGER);"; const char* sqlInsertData = "INSERT
     INTO Users (Name, Age) VALUES ('Mohammad', 21), ('Zohre', 20);"; const
     char* sqlSelectData = "SELECT * FROM Users;";

      // Execute SQL statements
      sqlite3_exec(db, sqlClearData, 0, 0, &errorMessage);
      sqlite3_exec(db, sqlCreateTable, 0, 0, &errorMessage);
      sqlite3_exec(db, sqlInsertData, 0, 0, &errorMessage);
      sqlite3_exec(db, sqlSelectData, callback, 0, &errorMessage);

      // Close database
      sqlite3_close(db);
      return 0;
  */

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
              system("echo 0 >
     ../../sys/class/leds/cubieboard2:green:usr/brightness"); return 1;
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

  // Print((char*)"{\"error\": \"No data received\"}\n");
  // return 0;
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
