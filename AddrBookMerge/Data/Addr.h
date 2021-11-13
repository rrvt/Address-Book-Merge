// Address Record


#pragma once
#include "Archive.h"
#include "CSVRcd.h"


extern const int nFlds;


struct AddrRcd {
String First_Name;
String Last_Name;
String Display_Name;
String Nickname;
String Primary_Email;
String Secondary_Email;
String Screen_Name;
String Work_Phone;
String Home_Phone;
String Fax_Number;
String Pager_Number;
String Mobile_Number;
String Home_Address;
String Home_Address_2;
String Home_City;
String Home_State;
String Home_ZipCode;
String Home_Country;
String Work_Address;
String Work_Address_2;
String Work_City;
String Work_State;
String Work_ZipCode;
String Work_Country;
String Job_Title;
String Department;
String Organization;
String Web_Page_1;
String Web_Page_2;
String Birth_Year;
String Birth_Month;
String Birth_Day;
String Custom_1;
String Custom_2;
String Custom_3;
String Custom_4;
String Notes;

  AddrRcd& operator= (CSVRcd& csvRcd);
  void     setFld(int i, String& s);
  String*  getFld(int i);

  void     dspAsCSV();
  void     dataOut(Archive& ar);
  };

