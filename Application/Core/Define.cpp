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
#include "Define.hpp"
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
vector<string> DEFINE_split(const string &s, char delimiter) {
  vector<std::string> tokens;
  stringstream ss(s);
  string token;

  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
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
