// CSV records, one record per line


#pragma once
#include "CSVRcd.h"


typedef DatumPtrT<CSVRcd, int>          CSVRcdP;
typedef CSVRcdsT< CSVRcd, int, CSVRcdP> CSVRcds;
typedef CSVIterT< CSVRcd, int, CSVRcdP> CSVIter;

extern CSVRcds csvRcds;

