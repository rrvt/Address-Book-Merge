 // AddrBookMergeDoc.cpp : implementation of the AddrBookMergeDoc class


#include "pch.h"
#include "AddrBookMergeDoc.h"
#include "AddrBook.h"
#include "AddrBookMerge.h"
#include "AddrBookMergeView.h"
#include "ClipLine.h"
#include "CSVrcds.h"
#include "filename.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Printer.h"
#include "Resource.h"

// AddrBookMergeDoc

IMPLEMENT_DYNCREATE(AddrBookMergeDoc, CDoc)

BEGIN_MESSAGE_MAP(AddrBookMergeDoc, CDoc)
  ON_COMMAND(ID_File_Open,   &onFileOpen)
  ON_COMMAND(ID_Add_Book,    &onAddBook)
  ON_COMMAND(ID_Process,     &onProcess)

  ON_COMMAND(ID_SaveFile,    &onSaveFile)

  ON_COMMAND(ID_EDIT_COPY,   &onEditCopy)


END_MESSAGE_MAP()


// AddrBookMergeDoc construction/destruction

AddrBookMergeDoc::AddrBookMergeDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

AddrBookMergeDoc::~AddrBookMergeDoc() { }


BOOL AddrBookMergeDoc::OnNewDocument() {return CDocument::OnNewDocument();}



void AddrBookMergeDoc::onEditCopy() {clipLine.load();}

#if 0
void AddrBookMergeDoc::onFileOpen() {

  notePad.clear();   dataSource = StoreSrc;

  pathDlgDsc(_T("Ugly Example"), pathDlgDsc.name, _T("txt"), _T("*.txt"));

  if (!setOpenPath(pathDlgDsc)) return;

  pathDlgDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

#ifdef Examples
  store.setName(pathDlgDsc.name);
#endif

  display(StoreSrc);
  }

#else

void AddrBookMergeDoc::onFileOpen() {
String s;

  csvRcds.clear();   nBooks = 0;

  onAddBook();
  }


void AddrBookMergeDoc::onAddBook() {
String s;
String mainName;

  dataSource = AddrMergSrc;

  pathDlgDsc(_T("CSV File"), 0, _T("csv"), _T("*.csv"));

  if (!setOpenPath(pathDlgDsc)) return;

  pathDlgDsc.name = books[nBooks++] = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  notePad.clear();   notePad << nClrTabs;

  notePad << _T("Address Books:") << nCrlf;

  for (int i = 0; i < nBooks; i++) notePad << nTab << books[i] << nCrlf;

  notePad << nTab << _T("No. of Records: ") << csvRcds.nData() << nCrlf;

  notePad << nCrlf;

  csvRcds.display(notePad);

  display();
  }

#endif



void AddrBookMergeDoc::onProcess() {addrBook.onProcess();   addrBook.dspRecords();   display();}


void AddrBookMergeDoc::onSaveFile() {
#if 1
  dataSource = AddrMergSrc;   if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);
#else
  dataSource = StoreSrc; saveFile(_T("Save File"), _T(""), _T("txt")); display(StoreSrc);
#endif
  }



void AddrBookMergeDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void AddrBookMergeDoc::saveFile(TCchar* title, TCchar* suffix, TCchar* fileType) {
String fileName = path;
int    pos      = fileName.find_last_of(_T('\\'));
String ext      = _T("*."); ext += fileType;
String ttl      = title;    ttl += _T(" Output");

  fileName = fileName.substr(pos+1);   pos = fileName.find_first_of(_T('.'));
  fileName = fileName.substr(0, pos);  fileName += suffix;

  pathDlgDsc(ttl, fileName, fileType, ext);

  if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);
  }


// UglyDoc serialization

void AddrBookMergeDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : ar << notePad; return;
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
void AddrBookMergeDoc::AssertValid() const {         CDocument::AssertValid();}
void AddrBookMergeDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG



//-------------------------------------------------------------------------


#ifdef Examples

static CbxItem cbxText[] = {{_T("Zeta"),     1},
                            {_T("Beta"),     2},
                            {_T("Alpha"),    3},
                            {_T("Omega"),    4},
                            {_T("Phi"),      5},
                            {_T("Mu"),       6},
                            {_T("Xi"),       7},
                            {_T("Omicron"),  8},
                            {_T("Pi"),       9},
                            {_T("Rho"),     10},
                            {_T("Sigma"),   11},
                            {_T("Nu"),      12},
                            {_T("Kappa"),   13},
                            {_T("Iota"),    14},
                            {_T("This is a reallyt long Greek"), 15}
                            };
static TCchar* CbxCaption = _T("Greeks");


void AddrBookMergeDoc::myButton() {
MyToolBar& toolBar = getToolBar();
int        i;
int        n;

  for (i = 0, n = noElements(cbxText); i < n; i++) {
    CbxItem& item = cbxText[i];

    toolBar.addCbxItemSorted(ID_CboBx, item.txt, item.data);
    }
  toolBar.setCaption(ID_CboBx, CbxCaption);
  toolBar.setWidth(ID_CboBx);

  notePad << _T("Loaded ") << CbxCaption << _T(" into ComboBx") << nCrlf;  display();
  }


void AddrBookMergeDoc::OnComboBoxChng() {
MyToolBar& toolBar = getToolBar();
String     s;
int        x;

  if (toolBar.getCurSel(ID_CboBx, s, x))
                         notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;
  display();
  }



void AddrBookMergeDoc::OnTBEditBox() {
MyToolBar& toolBar = getToolBar();
CString    cs      = toolBar.getText(ID_EditBox);
String     s       = cs;

  if (!s.isEmpty()) notePad << s << nCrlf;

  display();
  }


void AddrBookMergeDoc::myButton1() {
MyToolBar& toolBar = getToolBar();
CString    cs      = toolBar.getText(ID_EditBox);
String     s       = cs;

  if (!s.isEmpty()) notePad << s << nCrlf;

  display();
  }


void AddrBookMergeDoc::onOption11() {notePad << _T("Option 11") << nCrlf; display();}
void AddrBookMergeDoc::onOption12() {notePad << _T("Option 12") << nCrlf; display();}
void AddrBookMergeDoc::onOption13() {notePad << _T("Option 13") << nCrlf; wholePage(); display();}


void AddrBookMergeDoc::onOption21() {notePad << _T("Option 21") << nCrlf; display();}
void AddrBookMergeDoc::onOption22() {notePad << _T("Option 22") << nCrlf; display();}
void AddrBookMergeDoc::onOption23() {notePad << _T("Option 23") << nCrlf; display();}


void AddrBookMergeDoc::OnTestEditBoxes() {display();}


// AddrBookMergeDoc commands


void AddrBookMergeDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = printer.orient == LandOrient ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display();
  }


void AddrBookMergeDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


void AddrBookMergeDoc::wholePage() {
int    i;
int    j;
String s;

  notePad << nSetRTab(4) << nSetTab(6) << nSetTab(8) << nSetRTab(12) << nSetTab(14);

  for (i = 0; i < 100; i++) {
    s.format(_T("%3i:"), i);

    notePad << nTab << s << nTab << _T("X") << nTab << _T("Y") << nTab << i << nTab;

    for (j = i+1; j < i+68; j++)
                              {s.format(_T("%i"), j);   s = s.substr(s.length()-1);  notePad << s;}
    notePad << nCrlf;
    }
  }


void AddrBookMergeDoc::displayDataStore() {display(StoreSrc);}

#endif
#ifdef Examples
  ON_COMMAND(      ID_Button,      &myButton)
  ON_CBN_KILLFOCUS(ID_EditBox,     &OnTBEditBox)
  ON_COMMAND(      ID_EditBox,     &OnTBEditBox)

  ON_COMMAND(      ID_Menu,        &onOption11)
  ON_COMMAND(      ID_Option11,    &onOption11)
  ON_COMMAND(      ID_Option12,    &onOption12)
  ON_COMMAND(      ID_Option13,    &onOption13)

  ON_COMMAND(      ID_Menu1,       &onOption21)
  ON_COMMAND(      ID_Option21,    &onOption21)
  ON_COMMAND(      ID_Option22,    &onOption22)
  ON_COMMAND(      ID_Option23,    &onOption23)

  ON_CBN_SELCHANGE(ID_CboBx,       &OnComboBoxChng)
  ON_COMMAND(      ID_CboBx,       &OnComboBoxChng)
#endif
#ifdef Examples
  //  ON_COMMAND(      ID_TBSaveMenu,  &onSaveFile)
  //  ON_COMMAND(      ID_SaveStrRpt,  &onSaveStrRpt)
  //  ON_COMMAND(      ID_SaveNotePad, &onSaveNotePad)
  ON_COMMAND(      ID_Test,        &OnTest)
  ON_COMMAND(      ID_SelDataStr,  &displayDataStore)
#endif
#if 0
void AddrBookMergeDoc::onSaveStrRpt() {

  dataSource = StrRptSrc;   if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);

  display(StoreSrc);
  }


void AddrBookMergeDoc::onSaveNotePad() {

  dataSource = NotePadSrc;   if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);

  display(StoreSrc);
  }
#endif
#ifdef Examples
      case StoreSrc : store.load(ar); return;
#endif
#if 0
void AddrBookMergeDoc::displayRcds() {
CSVIter iter(csvRcds);
CSVRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    displayRcd(rcd);
    }
  }


void AddrBookMergeDoc::displayRcd(CSVRcd* rcd){
CFldIter iter(*rcd);
CSVfld*  fld;
int      i;
int      cnt;

  for (i = 0, cnt = 0, fld = iter(); fld; i++, fld = iter++) {
    if (i) notePad << _T(',');
    if (!fld->name.isEmpty()) {displayFld(fld->name);   cnt++;}
    }
  notePad << nCrlf;
  }


void AddrBookMergeDoc::displayFld(String& fld) {
int    n = fld.length();
int    i;
String s;

  for (i = 0; i < n; i++) {
    Tchar ch = fld[i];

    if (ch < _T(' ') || _T('~') < ch) {
      messageBox(_T("Got one"));   continue;
      }

    s += ch;
    }

  notePad << s;
  }
#endif
#ifdef Examples
      case StoreSrc   : store.store(ar); return;
      case StrRptSrc  : view()->storeRpt().txtOut( ar, 1.35); return;
#endif
#ifdef Examples
#include "Store.h"
#endif

