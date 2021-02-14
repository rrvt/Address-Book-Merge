// BuildDataDoc.cpp : implementation of the BuildDataDoc class


#include "stdafx.h"
#include "BuildDataDoc.h"
#include "BuildData.h"
#include "BuildDataView.h"
#ifdef Examples
#include "Store.h"
#endif
#include "ExtraResource.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "ToolBar.h"


// BuildDataDoc

IMPLEMENT_DYNCREATE(BuildDataDoc, CDoc)

BEGIN_MESSAGE_MAP(BuildDataDoc, CDoc)
  ON_COMMAND(ID_File_Open,     &OnFileOpen)
  ON_COMMAND(ID_PickEmail,     &OnPickEmail)
  ON_COMMAND(ID_PrepAddr_h,    &OnPrepAddr_h)
  ON_COMMAND(ID_PrepAddr_cpp,  &OnPrepAddr_cpp)
  ON_COMMAND(ID_File_Save,     &OnFileSave)
  ON_COMMAND(ID_Options,       &OnOptions)

#ifdef Examples
  ON_COMMAND(ID_Test,          &OnTest)
  ON_COMMAND(ID_SelDataStr,    &displayDataStore)

  ON_COMMAND(ID_MyBtn,         &myButton)

  ON_CBN_SELCHANGE(ID_CB,      &OnComboBoxChng)
  ON_COMMAND(      ID_CB,      &OnComboBoxChng)

  ON_COMMAND(ID_EditBox,       &OnTBEditBox)
  ON_COMMAND(ID_MyBtn1,        &onOption1)
  ON_COMMAND(ID_Option1,       &onOption1)
  ON_COMMAND(ID_Option2,       &onOption2)
  ON_COMMAND(ID_Option3,       &onOption3)
  ON_COMMAND(ID_Btn2,          &onOption21)
  ON_COMMAND(ID_Option21,      &onOption21)
  ON_COMMAND(ID_Option22,      &onOption22)
  ON_COMMAND(ID_Option23,      &onOption23)
#endif
END_MESSAGE_MAP()


// BuildDataDoc construction/destruction

BuildDataDoc::BuildDataDoc() noexcept : dataSource(NotePadSrc) {
  pathDsc = {_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt")};
  }

BuildDataDoc::~BuildDataDoc() { }


BOOL BuildDataDoc::OnNewDocument() {return CDocument::OnNewDocument();}

#ifdef Examples

static TCchar* cbText[] = {_T("Zeta"),
                           _T("Beta"),
                           _T("Alpha"),
                           _T("Omega"),
                           _T("Phi"),
                           _T("Mu"),
                           _T("Xi"),
                           _T("Omicron"),
                           _T("Pi"),
                           _T("Rho"),
                           _T("Sigma"),
                           _T("Nu"),
                           _T("Kappa"),
                           _T("Iota")
                           };


void BuildDataDoc::myButton() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int n = noElements(cbText);
int i;
int x;

  dataSource = NotePadSrc;

  notePad << _T("My Button") << nCrlf;

  if (!cb) {invalidate();  return;}

//  cb->SetText(_T("Greeks"));

  for (i = 0; i < n; i++) if (cb->findExact(cbText[i]) < 0) {

    x = cb->AddSortedItem(cbText[i], i);                           //AddSortedItem

    String s;  s.format(_T("%02i: "), i);

    notePad << s << _T("Pos = ") << x << _T(". Added ") << cbText[i] << nCrlf;
    }

  cb->SelectItem(-1);
  cb->SetText(_T("Greeks"));

  notePad << _T("Greeks") << nCrlf;  display(NotePadSrc);
  }


void BuildDataDoc::OnComboBoxChng() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int        i;
String     s;
int        x;
MainFrame* mf = theApp.mainFrm();

  if (!cb)   return;
  i  = cb->GetCurSel();    if (i < 0) return;
  s  = cb->GetItem(i);
  x  = cb->GetItemData(i);   mf->SetFocus();

  notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;

  display(NotePadSrc);
  }



void BuildDataDoc::OnTBEditBox() {
TBEditBox*  eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String      s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void BuildDataDoc::myButton1() {
TBEditBox* eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String     s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void BuildDataDoc::onOption1() {notePad << _T("Option 1") << nCrlf; wholePage(); display(NotePadSrc);}
void BuildDataDoc::onOption2() {notePad << _T("Option 2") << nCrlf; display(NotePadSrc);}
void BuildDataDoc::onOption3() {notePad << _T("Option 3") << nCrlf; display(NotePadSrc);}


void BuildDataDoc::onOption21() {notePad << _T("Option 21") << nCrlf; display(NotePadSrc);}
void BuildDataDoc::onOption22() {notePad << _T("Option 22") << nCrlf; display(NotePadSrc);}
void BuildDataDoc::onOption23() {notePad << _T("Option 23") << nCrlf; display(NotePadSrc);}


void BuildDataDoc::OnTestEditBoxes() {display(NotePadSrc);}


// BuildDataDoc commands


void BuildDataDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = options.orient == Landscape ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display(NotePadSrc);
  }


void BuildDataDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


void BuildDataDoc::wholePage() {
int    i;
int    j;
String s;

  notePad << nSetRTab(4) << nSetTab(6) << nSetTab(8) << nSetRTab(12) << nSetTab(14);

  for (i = 0; i < 100; i++) {
    s.format(_T("%3i:"), i);

    notePad << nTab << s << nTab << _T("X") << nTab << _T("Y") << nTab << i << nTab;

    for (j = i+1; j < i+68; j++) {s.format(_T("%i"), j);   s = s.substr(s.length()-1);  notePad << s;}

    notePad << nCrlf;
    }
  }


void BuildDataDoc::displayDataStore() {display(StoreSrc);}

#endif


void BuildDataDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void BuildDataDoc::OnFileOpen() {

  notePad.clear();   dataSource = AddrSrc;

  pathDsc = {_T("CSV File"), pathDsc.name, _T("csv"), _T("*.csv")};

  if (!setPath(pathDsc)) return;

  pathDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));
  #ifdef Examples
    store.setName(pathDsc.name);
  #endif
  display(AddrSrc);
  }


void BuildDataDoc::OnPickEmail() {codeBldr.onPickEmail(); display(AddrSrc);}


void BuildDataDoc::OnPrepAddr_h() {
  pathDsc = {_T("Save Addr.h"), _T("Addr.h"), _T("h"), _T("*.h")};

  codeBldr.OnPrepAddr_h();  display(HeaderSrc);
  }


void BuildDataDoc::OnPrepAddr_cpp() {
  pathDsc = {_T("Save Addr.cpp"), _T("Addr.cpp"), _T("cpp"), _T("*.cpp")};

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
      case NotePadSrc : notePad.archive(ar);  return;
#ifdef Examples
      case StoreSrc   : store.store(ar); return;
#endif
      default         : return;
      }

  else
    switch(dataSource) {
      #ifdef Examples
      case StoreSrc : store.load(ar); return;
      #endif
      case AddrSrc: codeBldr.load(ar); return;
      case NilSrc   :
      default       : return;
      }
  }


// BuildDataDoc diagnostics

#ifdef _DEBUG
void BuildDataDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void BuildDataDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

