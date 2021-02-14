// CSV records, one record per line


#include "stdafx.h"
#include "CSVrcds.h"

CSVRcds csvRcds;


void CSVfld::replaceBlanks(TCchar ch) {
int lng = name.length();
int i;

  for (i = 0; i < lng; i++) if (name[i] == ' ') name[i] = ch;
  }
