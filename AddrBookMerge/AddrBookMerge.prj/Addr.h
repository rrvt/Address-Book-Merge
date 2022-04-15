// Address Record


#pragma once
#include "Archive.h"
#include "CSVRcd.h"


class AddrRcd {
static int eMailX;

public:

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

  void     dspAsCSV();
  void     dataOut(Archive& ar);

  // Required for Insertion Sort, i.e. data = dtm;
  bool     operator>= (AddrRcd& x) {return _tcsicmp(Primary_Email, x.Primary_Email) >= 0;}
  bool     operator== (AddrRcd& x) {return _tcsicmp(Primary_Email, x.Primary_Email) == 0;}

  bool     operator!= (AddrRcd& x) {return _tcsicmp(Primary_Email, x.Primary_Email) != 0;}
  bool     operator>  (AddrRcd& x) {return _tcsicmp(Primary_Email, x.Primary_Email) >  0;}
  bool     operator<  (AddrRcd& x) {return _tcsicmp(Primary_Email, x.Primary_Email) <  0;}
  bool     operator<= (AddrRcd& x) {return _tcsicmp(Primary_Email, x.Primary_Email) <= 0;}

// returns either a pointer to data (or datum) at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? getFld(i) : 0;}
  String& getEmail()   {return *datum(eMailX);}

private:

  void     setFld(int i, String& s);
  String*  getFld(int i);

  int     nData();

  friend class ARIter;
  };


class ARIter {

int      iterX;
AddrRcd& rcd;

public:

  enum Dir {Fwd, Rev};

  ARIter(AddrRcd& addrRcd) : rcd(addrRcd) { }
  ARIter(ARIter& iter)     : iterX(iter.iterX), rcd(iter.rcd) { }

  String* operator() (Dir rev = Fwd) {iterX = rev ? rcd.nData() : 0; return rev ? decr() : current();}
  String* operator++ (int)           {return iterX < rcd.nData() ? incr() : 0;}
  String* operator-- (int)           {return iterX > 0           ? decr() : 0;}

  String* current()                  {return rcd.getFld(iterX);}

  ARIter& operator= (ARIter& iter)   {iterX = iter.iterX; rcd = iter.rcd;}

  bool  isLast()                     {return iterX + 1 == rcd.nData();}
  bool  isFirst()                    {return iterX <= 0;}

private:

  String* incr() {return iterX < rcd.nData() ? rcd.datum(++iterX) : 0;}
  String* decr() {return iterX > 0           ? rcd.datum(--iterX) : 0;}

  ARIter() : rcd(*(AddrRcd*)0) { }
  };
