// BuildDataView.cpp : implementation of the BuildDataView class


#include "stdafx.h"
#include "BuildDataView.h"
#include "BuildData.h"
#include "BuildDataDoc.h"
#include "Options.h"
#include "Resources.h"


// BuildDataView

IMPLEMENT_DYNCREATE(BuildDataView, CScrView)

BEGIN_MESSAGE_MAP(BuildDataView, CScrView)
END_MESSAGE_MAP()


BuildDataView::BuildDataView() noexcept :
                                          #ifdef Examples
                                            dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()),
                                          #endif
                                          dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL BuildDataView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void BuildDataView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void BuildDataView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case AddrSrc    :
      case HeaderSrc  :
      case BodySrc    :
      case NotePadSrc : prtNote.print(*this);  break;
#ifdef Examples
      case StoreSrc   : prtStore.print(*this); break;
#endif
      }

  else
    switch(ds) {
      case AddrSrc    :
      case HeaderSrc  :
      case BodySrc    :
      case NotePadSrc : dspNote.display(*this);  break;
#ifdef Examples
      case StoreSrc   : dspStore.display(*this); break;
#endif
      }


  CScrView::onPrepareOutput(printing);
  }


void BuildDataView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case AddrSrc    :
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    case StoreSrc   : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void BuildDataView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case AddrSrc    :
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
#ifdef Examples
    case StoreSrc   : prtStore.footer(dev, pageNo); break;
#endif
    }
  }



void BuildDataView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case AddrSrc    : break;
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void BuildDataView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case AddrSrc    : break;
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


// BuildDataView diagnostics

#ifdef _DEBUG

void BuildDataView::AssertValid() const {CScrollView::AssertValid();}

void BuildDataView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
BuildDataDoc* BuildDataView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(BuildDataDoc))); return (BuildDataDoc*)m_pDocument;}

#endif //_DEBUG
