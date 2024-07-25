// Address Record


#include "pch.h"
#include "Addr.h"
#include "Utilities.h"


static const int noAddrRcdFlds = 37;
int AddrRcd::eMailX = 4;


AddrRcd& AddrRcd::operator= (CSVRcd& csvRcd) {
CFldIter iter(csvRcd);
CSVfld*  fld;
int      i;

  for (fld = iter(), i = 0; fld; fld = iter++, i++)
                                 {String& p = removeQuotes(fld->name);   p.trim();   setFld(i, p);}
  return *this;
  }


void AddrRcd::setFld(int i, String& s) {
  switch(i) {
    case  0: First_Name               = s; return;
    case  1: Last_Name                = s; return;
    case  2: Display_Name             = s; return;
    case  3: Nickname                 = s; return;
    case  4: Primary_Email            = s; return;
    case  5: Secondary_Email          = s; return;
    case  6: Screen_Name              = s; return;
    case  7: Work_Phone               = s; return;
    case  8: Home_Phone               = s; return;
    case  9: Fax_Number               = s; return;
    case 10: Pager_Number             = s; return;
    case 11: Mobile_Number            = s; return;
    case 12: Home_Address             = s; return;
    case 13: Home_Address_2           = s; return;
    case 14: Home_City                = s; return;
    case 15: Home_State               = s; return;
    case 16: Home_ZipCode             = s; return;
    case 17: Home_Country             = s; return;
    case 18: Work_Address             = s; return;
    case 19: Work_Address_2           = s; return;
    case 20: Work_City                = s; return;
    case 21: Work_State               = s; return;
    case 22: Work_ZipCode             = s; return;
    case 23: Work_Country             = s; return;
    case 24: Job_Title                = s; return;
    case 25: Department               = s; return;
    case 26: Organization             = s; return;
    case 27: Web_Page_1               = s; return;
    case 28: Web_Page_2               = s; return;
    case 29: Birth_Year               = s; return;
    case 30: Birth_Month              = s; return;
    case 31: Birth_Day                = s; return;
    case 32: Custom_1                 = s; return;
    case 33: Custom_2                 = s; return;
    case 34: Custom_3                 = s; return;
    case 35: Custom_4                 = s; return;
    case 36: Notes                    = s; return;
    default: return;
    };
  }


String* AddrRcd::getFld(int i) {
static String nS = _T("");

  switch(i) {
    case  0: return &First_Name;
    case  1: return &Last_Name;
    case  2: return &Display_Name;
    case  3: return &Nickname;
    case  4: return &Primary_Email;
    case  5: return &Secondary_Email;
    case  6: return &Screen_Name;
    case  7: return &Work_Phone;
    case  8: return &Home_Phone;
    case  9: return &Fax_Number;
    case 10: return &Pager_Number;
    case 11: return &Mobile_Number;
    case 12: return &Home_Address;
    case 13: return &Home_Address_2;
    case 14: return &Home_City;
    case 15: return &Home_State;
    case 16: return &Home_ZipCode;
    case 17: return &Home_Country;
    case 18: return &Work_Address;
    case 19: return &Work_Address_2;
    case 20: return &Work_City;
    case 21: return &Work_State;
    case 22: return &Work_ZipCode;
    case 23: return &Work_Country;
    case 24: return &Job_Title;
    case 25: return &Department;
    case 26: return &Organization;
    case 27: return &Web_Page_1;
    case 28: return &Web_Page_2;
    case 29: return &Birth_Year;
    case 30: return &Birth_Month;
    case 31: return &Birth_Day;
    case 32: return &Custom_1;
    case 33: return &Custom_2;
    case 34: return &Custom_3;
    case 35: return &Custom_4;
    case 36: return &Notes;
    default: return &nS;
    };
  }


void AddrRcd::dspAsCSV() {
ARIter  iter(*this);
String* p;
int     i;
String  s;

  notePad << nClrTabs << nSetTab(40);

  s.format(_T("%-35s: "), Primary_Email.str());   notePad << s << nTab;

  for (i = 0, p = iter(); p; i++, p = iter++) {
    if (i) notePad << _T(',');

    notePad << *p;
    }

  notePad << nCrlf;
  }


void AddrRcd::dataOut(Archive& ar) {
ARIter  iter(*this);
String* p;
int     i;
int     pos;

  for (i = 0, p = iter(); p; i++, p = iter++)  {
    if (i) ar << _T(',');

    pos = p->find(_T(','));

    if (pos < 0) ar << *p;
    else         ar << _T('"') << *p << _T('"');
    }

  ar << aCrlf;
  }


int AddrRcd::nData() {return noAddrRcdFlds;}
