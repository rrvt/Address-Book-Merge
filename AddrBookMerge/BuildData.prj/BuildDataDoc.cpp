// BuildDataDoc.cpp : implementation of the BuildDataDoc class


#include "stdafx.h"
#include "BuildDataDoc.h"
#include "BuildData.h"
#include "BuildDataView.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "ResourceExtra.h"
#include "MyToolBar.h"


// BuildDataDoc

IMPLEMENT_DYNCREATE(BuildDataDoc, CDoc)

BEGIN_MESSAGE_MAP(BuildDataDoc, CDoc)
  ON_COMMAND(ID_File_Open,     &OnFileOpen)
  ON_COMMAND(ID_PickEmail,     &OnPickEmail)
  ON_COMMAND(ID_PrepAddr_h,    &OnPrepAddr_h)
  ON_COMMAND(ID_PrepAddr_cpp,  &OnPrepAddr_cpp)
  ON_COMMAND(ID_File_Save,     &OnFileSave)
END_MESSAGE_MAP()


// BuildDataDoc construction/destruction

BuildDataDoc::BuildDataDoc() noexcept : dataSource(NotePadSrc) { }

BuildDataDoc::~BuildDataDoc() { }


BOOL BuildDataDoc::OnNewDocument() {return CDocument::OnNewDocument();}


void BuildDataDoc::OnFileOpen() {

  notePad.clear();   dataSource = AddrSrc;

  pathDsc(_T("CSV File"), pathDsc.name, _T("csv"), _T("*.csv"));

  if (!setOpenPath(pathDsc)) return;

  pathDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  display(AddrSrc);
  }


void BuildDataDoc::OnPickEmail() {codeBldr.onPickEmail(); display(AddrSrc);}


void BuildDataDoc::OnPrepAddr_h() {
  pathDsc(_T("Save Addr.h"), _T("Addr.h"), _T("h"), _T("*.h"));

  codeBldr.OnPrepAddr_h();  display(HeaderSrc);
  }


void BuildDataDoc::OnPrepAddr_cpp() {

  pathDsc(_T("Save Addr.cpp"), _T("Addr.cpp"), _T("cpp"), _T("*.cpp"));

  codeBldr.OnPrepAddr_cpp(); display(BodySrc);
  }


void BuildDataDoc::display(DataSource ds) {dataSource = ds; invalidate();}





void BuildDataDoc::OnFileSave() {if (setSaveAsPath(pathDsc)) OnSaveDocument(path);}


// UglyDoc serialization

void BuildDataDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case HeaderSrc  :
      case BodySrc    :
      case NotePadSrc : ar << notePad;  return;
      default         : return;
      }

  else
    switch(dataSource) {
      case AddrSrc: codeBldr.load(ar); return;
      case NilSrc   :
      default       : return;
      }
  }


// BuildDataDoc diagnostics

#ifdef _DEBUG
void BuildDataDoc::AssertValid() const          {CDocument::AssertValid();}
void BuildDataDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG

