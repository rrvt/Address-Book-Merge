// Merge Address Books


#pragma once
#include "Addr.h"


class  AddrBook;
typedef DatumPtrT<AddrRcd, String>  AddrRcdP;
typedef IterT<AddrBook, AddrRcd>    ABIter;


class AddrBook {

ExpandableP<AddrRcd, String, AddrRcdP, 2> data;

AddrRcd header;

public:

  AddrBook() {}
 ~AddrBook();

  void onProcess();

  void dspRecords();

  void dataOut(Archive& ar);

  int      nData()      {return data.end();}              // returns number of data items in array

private:

  void     getRecords();
  void     cleanupRecords();
  void     removeTroublesomeEmails();
  void     noDups();

  bool     splitStg(String s, String& first, String& last, int& firstLng, int& lastLng);

  bool     validate(AddrRcd& rcd);
  bool     validateEmail(String& fld);
  bool     fixEmail(AddrRcd& rcd);
  void     removeJr(String& s);


  bool     adjacentRcdsEmailsSame(ABIter abIter);
  void     mergeDups(ABIter abIter);
  bool     fieldsAreSame(String& s, String& t) {return _tcsicmp(s.str(), t.str()) == 0;}

  bool     isTroublesomeEmail(String& eMail);
  bool     displIsEmail(AddrRcd& rcd);
  String*  getFldRcd();                                   // Specifies Record, gets field

  // returns either a pointer to data (or datum) at index i in array or zero

  AddrRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}       // or data[i].p


  void     removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename ABIter;

  };


extern AddrBook addrBook;



