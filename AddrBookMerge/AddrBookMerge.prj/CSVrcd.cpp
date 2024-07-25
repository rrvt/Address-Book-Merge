// Status Update CSV Data


#include "pch.h"
#include "CSVrcd.h"


void CSVRcd::put(TCchar* tc) {
Tchar  ch;
String s;

  for (ch = *tc++; ch; ch = *tc++) {
    if (ch < _T(' ') || _T('~') < ch) s += _T(" *** ");
    else                              s += ch;
    }

  fields.nextData().put(s);
  }

