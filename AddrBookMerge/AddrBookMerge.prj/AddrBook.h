// Merge Address Books


#pragma once
#include "Addr.h"



#if 0
struct AddrRcdP {
AddrRcd* p;

  AddrRcdP() : p(0) {}
  AddrRcdP(AddrRcdP& rcd) {p = rcd.p;}
 ~AddrRcdP() {p = 0;}

  AddrRcdP& operator= (AddrRcdP& q) {p = q.p; return *this;}
  };
#endif



class  AddrBook;
typedef DatumPtrT<AddrRcd> AddrRcdP;
typedef IterT<AddrBook, AddrRcd> ABIter;



class AddrBook {

ExpandableP<AddrRcd, AddrRcdP, 2> rcds;

AddrRcd header;

public:

  AddrBook() {}
 ~AddrBook() { }

  void onProcess();

  void dspRecords();

  void dataOut(Archive& ar);

private:

  void     getRecords();
  void     cleanupRecords();
  void     removeTroublesomeEmails();
  void     sort();
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
  String*  getFldRcd();                                    // Specifies Record, gets field

  // returns either a pointer to data (or datum) at index i in array or zero

  AddrRcd* datum(int i) {return 0 <= i && i < nData() ? rcds[i].p : 0;}       // or data[i].p

  int      nData()      {return rcds.end();}                       // returns number of data items in array

  void     removeDatum(int i) {if (0 <= i && i < nData()) rcds.del(i);}

  friend typename ABIter;

  };


extern AddrBook addrBook;




//  void     delRcd(int x);

//  AddrRcd* allocateRcd() {NewAlloc(AddrRcd); return rcds[rcdX].p = AllocNode;}

//  AddrRcd* firstNewRcd() {rcdX = 0; fldX = 0; return rcdX < rcds.end() ? rcds[rcdX].p : allocateRcd();}
//  AddrRcd* nextNewRcd() { rcdX++;   fldX = 0; return rcdX < rcds.end() ? rcds[rcdX].p : allocateRcd();}
//int                               fldX;    : fldX(0)

