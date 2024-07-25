// AddrBookMergeView.cpp : implementation of the AddrBookMergeView class


#include "pch.h"
#include "AddrBookMergeView.h"
#include "AddrBookMerge.h"
#include "AddrBookMergeDoc.h"
#include "ClipLine.h"
#include "IniFile.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgTwo.h"


static TCchar* StrOrietnKey = _T("Store");


IMPLEMENT_DYNCREATE(AddrBookMergeView, CScrView)

BEGIN_MESSAGE_MAP(AddrBookMergeView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()                     // Right Mouse Popup Menu
  ON_COMMAND(ID_CopySel, &onCopy)
  ON_COMMAND(ID_Pup1,    &onPup1)
  ON_COMMAND(ID_Pup2,    &onPup2)

END_MESSAGE_MAP()


AddrBookMergeView::AddrBookMergeView() noexcept {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);

  sub.LoadMenu(IDR_RtMouseMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


BOOL AddrBookMergeView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}


void AddrBookMergeView::OnInitialUpdate() {CScrView::OnInitialUpdate();}


void AddrBookMergeView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void AddrBookMergeView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Store:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
    saveRptOrietn();
    }
  }


void AddrBookMergeView::initRptOrietn() { }


void AddrBookMergeView::saveRptOrietn() {
  saveNoteOrietn();

  }



void AddrBookMergeView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);     break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AddrBookMergeView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    }
  }


void AddrBookMergeView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this); break;
    }
  }


void AddrBookMergeView::displayHeader(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspHeader(dev);   break;
    }
  }


void AddrBookMergeView::displayFooter(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspFooter(dev);   break;
    }
  }


void AddrBookMergeView::printHeader(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc: prtNote.prtHeader(dev, pageNo);   break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void AddrBookMergeView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    }
  }



void AddrBookMergeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void AddrBookMergeView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void AddrBookMergeView::OnLButtonDown(UINT nFlags, CPoint point)
                   {clipLine.set(point);   invalidate();   CScrView::OnLButtonDown(nFlags, point);}


void AddrBookMergeView::OnLButtonDblClk(UINT nFlags, CPoint point) {
  clipLine.set(point);   RedrawWindow();   clipLine.load();

  CScrView::OnLButtonDblClk(nFlags, point);
  }


void AddrBookMergeView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
        {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void AddrBookMergeView::onCopy() {clipLine.load();  invalidate();}


void AddrBookMergeView::onPup1() {  }


void AddrBookMergeView::onPup2() {  }


// AddrBookMergeView diagnostics

#ifdef _DEBUG
void AddrBookMergeView::AssertValid() const          {CScrollView::AssertValid();}
void AddrBookMergeView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                    // non-debug version is inline
AddrBookMergeDoc* AddrBookMergeView::GetDocument() const {          // non-debug version is inline
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AddrBookMergeDoc)));
  return (AddrBookMergeDoc*)m_pDocument;
  }
#endif //_DEBUG






#ifdef Examples
AddrBookMergeView::AddrBookMergeView() noexcept : dspStore(dMgr.getNotePad()),
                                              prtStore(pMgr.getNotePad()) {
#else
#endif
#ifdef Examples
  dlg.rpt1 = printer.toStg(prtStore.prtrOrietn);
#endif
#ifdef Examples
    prtStore.prtrOrietn = printer.toOrient(dlg.rpt1);
#endif
#ifdef Examples
  {prtStore.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StrOrietnKey, PortOrient);}
#else
#endif
#ifdef Examples
  iniFile.write(RptOrietnSect, StrOrietnKey,  (int) prtStore.prtrOrietn);
#endif
#ifdef Examples
    case StoreSrc   : prtStore.onPreparePrinting(info);    break;
#endif
#ifdef Examples
    case StoreSrc   : prtStore.onBeginPrinting(*this); break;
#endif
#ifdef Examples
    case StoreSrc   : dspStore.display(*this); break;
#endif
#ifdef Examples
    case StoreSrc     : dspStore.dspHeader(dev);  break;
#endif
#ifdef Examples
    case StoreSrc     : dspStore.dspFooter(dev);  break;
#endif
#ifdef Examples
    case StoreSrc  : dspStore.prtHeader(dev, pageNo);  break;
#endif
#ifdef Examples
    case StoreSrc   : prtStore.prtFooter(dev, pageNo); break;
#endif

