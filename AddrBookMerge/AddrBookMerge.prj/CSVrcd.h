// Status Update CSV Data


#pragma once
#include "IterT.h"
#include "CSVRcdB.h"
#include "CSVRcdsT.h"
#include "ExpandableP.h"


class CSVfld {
public:
String name;

  CSVfld() {}
  CSVfld(CSVfld& fd) {copy(fd);}

 ~CSVfld() {}

  void    clear() {name.clear();}

  CSVfld& operator=(CSVfld& fd)  {copy(fd); return *this;}

  void    replaceBlanks(TCchar ch);
  void    put(TCchar* s) {name = s;}
  String* get() {return &name;}

private:

  void copy(CSVfld& src) {name = src.name;}
  };


class CSVRcd;
typedef DatumPtrT<CSVfld, int> CSVFldP;
typedef IterT<CSVRcd, CSVfld>  CFldIter;



class CSVRcd : public CSVRcdB {

ExpandableP <CSVfld, int, CSVFldP, 128> fields;

public:

  CSVRcd() {}
 ~CSVRcd() {clear();}

  virtual void clear() {fields.clear();}

  int       nFields() {return fields.end();}

  String*   get(int i) {CSVfld* f = datum(i);  return f ? f->get() : 0;}

private:

  virtual void    put(TCchar* s) {fields.nextData().put(s);}

  virtual String* get() {CSVfld* f = fields[getI].p; return f ? f->get() : 0;}

  virtual void    copy(CSVRcd& r) { }

  // returns either a pointer to data (or datum) at index i in array or zero

  CSVfld* datum(int i) {return 0 <= i && i < nData() ? fields[i].p : 0;}       // or data[i].p

  int     nData()      {return fields.end();}             // returns number of data items in array

  friend typename CFldIter;
  };

