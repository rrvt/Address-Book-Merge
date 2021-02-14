// AddrBookMergeView.cpp : implementation of the AddrBookMergeView class


#include "stdafx.h"
#include "AddrBookMergeView.h"
#include "AddrBookMerge.h"
#include "AddrBookMergeDoc.h"
#include "Options.h"
#include "Resources.h"


// AddrBookMergeView

IMPLEMENT_DYNCREATE(AddrBookMergeView, CScrView)

BEGIN_MESSAGE_MAP(AddrBookMergeView, CScrView)
END_MESSAGE_MAP()


AddrBookMergeView::AddrBookMergeView() noexcept :
                                              dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL AddrBookMergeView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void AddrBookMergeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AddrBookMergeView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case AddrMergSrc:
      case NotePadSrc : prtNote.print(*this);  break;
      }

  else
    switch(ds) {
      case AddrMergSrc:
      case NotePadSrc : dspNote.display(*this);  break;
      }


  CScrView::onPrepareOutput(printing);
  }


void AddrBookMergeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case AddrMergSrc:
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    case StoreSrc   : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void AddrBookMergeView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case AddrMergSrc:
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
    }
  }



void AddrBookMergeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case AddrMergSrc:
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void AddrBookMergeView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case AddrMergSrc:
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


// AddrBookMergeView diagnostics

#ifdef _DEBUG

void AddrBookMergeView::AssertValid() const {CScrollView::AssertValid();}

void AddrBookMergeView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
AddrBookMergeDoc* AddrBookMergeView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AddrBookMergeDoc))); return (AddrBookMergeDoc*)m_pDocument;}

#endif //_DEBUG
