// AddrBookMergeDoc.cpp : implementation of the AddrBookMergeDoc class


#include "stdafx.h"
#include "AddrBookMergeDoc.h"
#include "AddrBook.h"
#include "AddrBookMerge.h"
#include "AddrBookMergeView.h"
#include "CSVrcds.h"
#include "ResourceExtra.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Resource.h"
#include "MyToolBar.h"


// AddrBookMergeDoc

IMPLEMENT_DYNCREATE(AddrBookMergeDoc, CDoc)

BEGIN_MESSAGE_MAP(AddrBookMergeDoc, CDoc)
  ON_COMMAND(ID_File_Open,     &OnFileOpen)
  ON_COMMAND(ID_Add_Book,      &OnAddBook)
  ON_COMMAND(ID_Process,       &OnProcess)
  ON_COMMAND(ID_File_Save,     &OnFileSave)
END_MESSAGE_MAP()


// AddrBookMergeDoc construction/destruction

AddrBookMergeDoc::AddrBookMergeDoc() noexcept : dataSource(NotePadSrc),
                                                   pathDsc{_T("CSV File"), 0, _T("csv"), _T("*.csv")} { }

AddrBookMergeDoc::~AddrBookMergeDoc() { }


BOOL AddrBookMergeDoc::OnNewDocument() {return CDocument::OnNewDocument();}


void AddrBookMergeDoc::OnFileOpen() {
String s;

  csvRcds.clear();   OnAddBook();
  }


void AddrBookMergeDoc::OnAddBook() {
String s;

  dataSource = AddrMergSrc;

  pathDsc(_T("CSV File"), 0, _T("csv"), _T("*.csv"));

  if (!setOpenPath(pathDsc)) return;

  pathDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  notePad.clear();

  s.format(_T("\nNumber of Address Records: %i"), csvRcds.count());

  notePad << s << nCrlf << nCrlf;

  csvRcds.display(notePad);

  display(AddrMergSrc);
  }


void AddrBookMergeDoc::OnProcess()
                                {addrBook.onProcess();   addrBook.dspRecords();   display(AddrMergSrc);}



void AddrBookMergeDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void AddrBookMergeDoc::OnFileSave() {if (setSaveAsPath(pathDsc)) OnSaveDocument(path);}


// UglyDoc serialization

void AddrBookMergeDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;

      case AddrMergSrc: addrBook.dataOut(ar); return;

      default         : return;
      }

  else
    switch(dataSource) {
      case AddrMergSrc: csvRcds.load(ar); return;

      default         : return;
      }
  }


// AddrBookMergeDoc diagnostics

#ifdef _DEBUG
void AddrBookMergeDoc::AssertValid() const {CDocument::AssertValid();}

void AddrBookMergeDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG





#if 0
void AddrBookMergeDoc::OnAddBook() {
String path;
String s;

  notePad.clear();   dataSource = AddrMergSrc;

  if (getPathDlg(_T("CSV File"), 0, _T("csv"), _T("*.csv"), path)) OnOpenDocument(path);

  s.format(_T("\nNumber of Address Records: %i"), csvRcds.count());    notePad << s << nCrlf << nCrlf;

  csvRcds.display(notePad);
  invalidate();
  }
#endif



