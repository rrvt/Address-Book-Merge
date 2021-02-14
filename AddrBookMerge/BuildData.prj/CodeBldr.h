// Code Builder


#pragma once
#include "CSVrcds.h"
#include "Expandable.h"


class Archive;



class CodeBldr {

String eMailName;
int    eMailX;

public:

CSVRcd csvRcd;

  CodeBldr() : eMailX(-1) { }
 ~CodeBldr() { }

  void load(Archive& ar);
  void onPickEmail();
  void OnPrepAddr_h();
  void OnPrepAddr_cpp();

private:

  void prepAddrCls();
  void prepComparison(TCchar* op);
  void prepAddrIter();

  void prepOpAssn();
  void prepSetFld();
  void prepGetFld();
  void prepDspAsCSV();
  void prepDataOut();
  void prepNData();
  };



extern CodeBldr codeBldr;

