// AddrBookMergeView.cpp : implementation of the AddrBookMergeView class


#include "stdafx.h"
#include "AddrBookMergeView.h"
#include "AddrBookMerge.h"
#include "AddrBookMergeDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "ResourceExtra.h"
#include "Resources.h"
#include "RptOrientDlgOne.h"


// AddrBookMergeView

IMPLEMENT_DYNCREATE(AddrBookMergeView, CScrView)

BEGIN_MESSAGE_MAP(AddrBookMergeView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


AddrBookMergeView::AddrBookMergeView() noexcept {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL AddrBookMergeView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}


void AddrBookMergeView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void AddrBookMergeView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl00 = _T("Media:");

  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);

  if (dlg.DoModal() == IDOK) {prtNote.prtrOrietn = printer.toOrient(dlg.ntpd);   saveNoteOrietn();}
  }



// Perpare output (i.e. report) then start the output with the call to SCrView

void AddrBookMergeView::onBeginPrinting() {prtNote.onBeginPrinting(*this);}


void AddrBookMergeView::onDisplayOutput() {dspNote.display(*this);}


void AddrBookMergeView::displayHeader(DevBase& dev) {dspNote.dspHeader(dev);}


void AddrBookMergeView::displayFooter(DevBase& dev) {dspNote.dspFooter(dev);}


void AddrBookMergeView::printHeader(DevBase& dev, int pageNo) {prtNote.prtHeader(dev, pageNo);}


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void AddrBookMergeView::printFooter(DevBase& dev, int pageNo) {prtNote.prtFooter(dev, pageNo);}


void AddrBookMergeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) { }


void AddrBookMergeView::OnSetFocus(CWnd* pOldWnd) {CScrView::OnSetFocus(pOldWnd);}


// AddrBookMergeView diagnostics

#ifdef _DEBUG

void AddrBookMergeView::AssertValid() const {CScrollView::AssertValid();}

void AddrBookMergeView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                            // non-debug version is inline
AddrBookMergeDoc* AddrBookMergeView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AddrBookMergeDoc))); return (AddrBookMergeDoc*)m_pDocument;}

#endif //_DEBUG
