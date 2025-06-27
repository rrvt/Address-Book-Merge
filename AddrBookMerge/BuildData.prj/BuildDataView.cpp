// BuildDataView.cpp : implementation of the BuildDataView class


#include "stdafx.h"
#include "BuildDataView.h"
#include "BuildData.h"
#include "BuildDataDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "ResourceData.h"
#include "RptOrientDlgOne.h"


// BuildDataView

IMPLEMENT_DYNCREATE(BuildDataView, CScrView)

BEGIN_MESSAGE_MAP(BuildDataView, CScrView)
  ON_COMMAND(ID_Options, &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


BuildDataView::BuildDataView() noexcept {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL BuildDataView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void BuildDataView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void BuildDataView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl00 = _T("Media:");

  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);

  if (dlg.DoModal() == IDOK) {prtNote.prtrOrietn = printer.toOrient(dlg.ntpd);   saveNoteOrietn();}
  }



// Perpare output (i.e. report) then start the output with the call to SCrView

void BuildDataView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case AddrSrc    :
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    }
  }


void BuildDataView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case AddrSrc    :
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : dspNote.display(*this);  break;
    }
  }


void BuildDataView::printHeader(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case AddrSrc   :
    case HeaderSrc :
    case BodySrc   :
    case NotePadSrc: prtNote.prtHeader(dev, pageNo);   break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void BuildDataView::printFooter(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case AddrSrc    :
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    }
  }



void BuildDataView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case AddrSrc    : break;
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : break;
    }
  }


void BuildDataView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case AddrSrc    : break;
    case HeaderSrc  :
    case BodySrc    :
    case NotePadSrc : break;
    }
  }


// BuildDataView diagnostics

#ifdef _DEBUG
void BuildDataView::AssertValid() const          {CScrollView::AssertValid();}
void BuildDataView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                    // non-debug version is inline
BuildDataDoc* BuildDataView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(BuildDataDoc))); return (BuildDataDoc*)m_pDocument;}
#endif //_DEBUG
