// Code Builder


#include "stdafx.h"
#include "CodeBldr.h"
#include "Archive.h"
#include "NotePad.h"
#include "PickEmailDlg.h"


CodeBldr codeBldr;


void CodeBldr::load(Archive& ar) {
CSVLex   lex(ar);
CFldIter iter(csvRcd);
CSVfld*  d;
int      i;
String   s;

  csvRcd.load(lex);

  for (i = 0, d = iter(); d; i++, d = iter++) {
    d->replaceBlanks(_T('_'));

    s.format(_T("Field %2i: %s"), i, d->name.str());
    notePad << s << nCrlf;
    }

  notePad << _T("\nNumber of Status CSV Records: ") << csvRcd.nFields() << nCrlf;
  }


void CodeBldr::onPickEmail() {
PickEmailDlg dlg;
CFldIter     iter(codeBldr.csvRcd);
CSVfld*      fld;
int          i;

  if (dlg.DoModal() == IDOK) {
    eMailName = dlg.comboBox;

    for (i = 0, fld = iter(); fld; i++, fld = iter++) if (fld->name == eMailName) {eMailX = i; return;}
    }
  }


void CodeBldr::OnPrepAddr_h() {
  prepAddrCls();  notePad << nCrlf << nCrlf;
  prepAddrIter();
  }


void CodeBldr::prepAddrCls() {
CFldIter iter(csvRcd);
CSVfld*  d;

  notePad.clear();

  notePad << _T("// Address Record") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"Archive.h\"") << nCrlf;
  notePad << _T("#include \"CSVRcd.h\"") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("class AddrRcd {") << nCrlf;
  notePad << _T("static int eMailX;") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  for (d = iter(); d; d = iter++) notePad << _T("String ") + d->name + _T(";") << nCrlf;

  notePad << nCrlf;
  notePad << _T("  AddrRcd& operator= (CSVRcd& csvRcd);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void     dspAsCSV();") << nCrlf;
  notePad << _T("  void     dataOut(Archive& ar);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  // Required for Insertion Sort, i.e. data = dtm;") << nCrlf;
  prepComparison(_T(">="));
  prepComparison(_T("=="));   notePad << nCrlf;

  prepComparison(_T("!="));
  prepComparison(_T("> "));
  prepComparison(_T("< "));
  prepComparison(_T("<="));  notePad << nCrlf;

  notePad << _T("// returns either a pointer to data (or datum) at index i in array or zero");
  notePad << nCrlf << nCrlf;

  notePad << _T("  String* datum(int i) {return 0 <= i && i < nData() ? getFld(i) : 0;}") << nCrlf;
  notePad << _T("  String& getEmail()   {return *datum(eMailX);}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  void     setFld(int i, String& s);") << nCrlf;
  notePad << _T("  String*  getFld(int i);") << nCrlf << nCrlf;

  notePad << _T("  int     nData();") << nCrlf << nCrlf;

  notePad << _T("  friend class ARIter;") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }


void CodeBldr::prepComparison(TCchar* op) {

  notePad << _T("  bool     operator") << op << _T(" (AddrRcd& x) {return _tcsicmp(");
  notePad << eMailName << _T(", x.") << eMailName << _T(") ") << op << _T(" 0;}") << nCrlf;
  }



void CodeBldr::prepAddrIter() {

  notePad << _T("class ARIter {") << nCrlf << nCrlf;

  notePad << _T("int      iterX;") << nCrlf;
  notePad << _T("AddrRcd& rcd;") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  enum Dir {Fwd, Rev};") << nCrlf << nCrlf;

  notePad << _T("  ARIter(AddrRcd& addrRcd) : rcd(addrRcd) { }") << nCrlf;
  notePad << _T("  ARIter(ARIter& iter)     : iterX(iter.iterX), rcd(iter.rcd) { }");
  notePad << nCrlf << nCrlf;

  notePad << _T("  String* operator() (Dir rev = Fwd)") << nCrlf;
  notePad << _T("                                ");
  notePad << _T("{iterX = rev ? rcd.nData() : 0;   return rev ? decr() : current();}") << nCrlf;
  notePad << _T("  String* operator++ (int)           {return iterX < rcd.nData() ? incr() : 0;}");
  notePad << nCrlf;
  notePad << _T("  String* operator-- (int)           {return iterX > 0           ? decr() : 0;}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  String* current()                  {return rcd.getFld(iterX);}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  ARIter& operator= (ARIter& iter)   {iterX = iter.iterX; rcd = iter.rcd;}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  bool  isLast()                     {return iterX + 1 == rcd.nData();}");
  notePad << nCrlf;
  notePad << _T("  bool  isFirst()                    {return iterX <= 0;}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  String* incr() {return iterX < rcd.nData() ? rcd.datum(++iterX) : 0;}");
  notePad << nCrlf;
  notePad << _T("  String* decr() {return iterX > 0           ? rcd.datum(--iterX) : 0;}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  ARIter() : rcd(*(AddrRcd*)0) { }") << nCrlf;
  notePad << _T("  };") << nCrlf;
  }


void CodeBldr::OnPrepAddr_cpp() {
String   s;

  notePad.clear();

  notePad << _T("// Address Record") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("#include \"pch.h\"") << nCrlf;
  notePad << _T("#include \"Addr.h\"") << nCrlf;
  notePad << _T("#include \"Utilities.h\"") << nCrlf;

  notePad << nCrlf << nCrlf;

  s.format(_T("static const int noAddrRcdFlds = %i;"), csvRcd.nFields());    notePad << s << nCrlf;
  s.format(_T("int AddrRcd::eMailX = %i;"), eMailX);                         notePad << s << nCrlf;
  notePad << nCrlf << nCrlf;

  prepOpAssn();   notePad << nCrlf << nCrlf;

  prepSetFld();   notePad << nCrlf << nCrlf;

  prepGetFld();   notePad << nCrlf << nCrlf;

  prepDspAsCSV(); notePad << nCrlf << nCrlf;

  prepDataOut();  notePad << nCrlf << nCrlf;

  prepNData();
  }


void CodeBldr::prepOpAssn() {

  notePad << _T("AddrRcd& AddrRcd::operator= (CSVRcd& csvRcd) {") << nCrlf;
  notePad << _T("CFldIter iter(csvRcd);") << nCrlf;
  notePad << _T("CSVfld*  fld;") << nCrlf;
  notePad << _T("int      i;") << nCrlf << nCrlf;

  notePad << _T("  for (fld = iter(), i = 0; fld; fld = iter++, i++)") << nCrlf;
  notePad << _T("                                 {String& p = removeQuotes(fld->name);");
  notePad << _T("   p.trim();   setFld(i, p);}") << nCrlf;

  notePad << _T("  return *this;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }



void CodeBldr::prepSetFld() {
CFldIter iter(csvRcd);
CSVfld*  d;
int      i;
String   s;

  notePad << _T("void AddrRcd::setFld(int i, String& s) {") << nCrlf;
  notePad << _T("  switch(i) {") << nCrlf;

  for (d = iter(), i = 0; d; d = iter++, i++) {
    s.format(_T("    case %2i: %-24s = s; return;"), i, d->name.str());   notePad << s << nCrlf;
    }
  notePad << _T("    default: return;") << nCrlf;
  notePad << _T("    };") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void CodeBldr::prepGetFld() {
CFldIter iter(csvRcd);
CSVfld*  d;
int      i;
String   s;

  notePad << _T("String* AddrRcd::getFld(int i) {") << nCrlf;
  notePad << _T("static String nS = _T(\"\");") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  switch(i) {") << nCrlf;

  for (d = iter(), i = 0; d; d = iter++, i++) {
    s.format(_T("    case %2i: return &%s;"), i, d->name.str());   notePad << s << nCrlf;
    }
  notePad << _T("    default: return &nS;") << nCrlf;
  notePad << _T("    };") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }



void CodeBldr::prepDspAsCSV() {
String s;
String t;

  notePad << _T("void AddrRcd::dspAsCSV() {") << nCrlf;
  notePad << _T("ARIter  iter(*this);") << nCrlf;
  notePad << _T("String* p;") << nCrlf;
  notePad << _T("int     i;") << nCrlf;
  notePad << _T("String  s;") << nCrlf << nCrlf;


  notePad << _T("  notePad << nClrTabs << nSetTab(40);") << nCrlf << nCrlf;

  t = _T("%-35s:");
  s.format(_T("  s.format(_T(\"%s \"), Primary_Email.str());"), t.str());
  s += _T("   notePad << s << nTab;");

  notePad << s << nCrlf << nCrlf;

  notePad << _T("  for (i = 0, p = iter(); p; i++, p = iter++) {") << nCrlf;
  notePad << _T("    if (i) notePad << _T(',');") << nCrlf << nCrlf;

  notePad << _T("    notePad << *p;") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;
  notePad << _T("  notePad << nCrlf;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void CodeBldr::prepDataOut() {

  notePad << _T("void AddrRcd::dataOut(Archive& ar) {") << nCrlf;
  notePad << _T("ARIter  iter(*this);") << nCrlf;
  notePad << _T("String* p;") << nCrlf;
  notePad << _T("int     i;") << nCrlf;
  notePad << _T("int     pos;") << nCrlf << nCrlf;

  notePad << _T("  for (i = 0, p = iter(); p; i++, p = iter++)  {") << nCrlf;
  notePad << _T("    if (i) ar << _T(',');") << nCrlf << nCrlf;

  notePad << _T("    pos = p->find(_T(','));") << nCrlf << nCrlf;

  notePad << _T("    if (pos < 0) ar << *p;") << nCrlf;
  notePad << _T("    else         ar << _T('\"') << *p << _T('\"');") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  ar << aCrlf;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void CodeBldr::prepNData() {
  notePad << _T("int AddrRcd::nData() {return noAddrRcdFlds;}") << nCrlf;
  }
