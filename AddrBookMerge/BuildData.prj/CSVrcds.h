// CSV records, one record per line


#pragma once
#include "CSVRcd.h"


typedef RcdPtrT< CSVRcd> CSVRcdP;
typedef CSVRcdsT<CSVRcd, CSVRcdP> CSVRcds;
typedef CSVIterT<CSVRcd, CSVRcdP> CSVIter;

extern CSVRcds csvRcds;

