// AddrBookMergeView.h : interface of the AddrBookMergeView class


#pragma once
#include "CScrView.h"
#include "ReportNtPd.h"


class AddrBookMergeDoc;


class AddrBookMergeView : public CScrView {

CMenu      menu;
CMenu      sub;

protected: // create from serialization only

  AddrBookMergeView() noexcept;

  DECLARE_DYNCREATE(AddrBookMergeView)

public:

  virtual           ~AddrBookMergeView() { }

  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn();
  virtual void       saveRptOrietn();
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}

  virtual BOOL       PreCreateWindow(CREATESTRUCT& cs);
  virtual void       OnInitialUpdate();

  virtual void       displayHeader(DevStream& dev);
  virtual void       displayFooter(DevStream& dev);

  virtual void       onPreparePrinting(CPrintInfo* info);
  virtual void       onBeginPrinting();
  virtual void       onDisplayOutput();

  virtual void       printHeader(DevStream& dev, int pageNo);
  virtual void       printFooter(DevStream& dev, int pageNo);
  virtual void       OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  AddrBookMergeDoc*  GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();

  afx_msg void OnSetFocus(CWnd* pOldWnd);

  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

  afx_msg void OnContextMenu(  CWnd* ,      CPoint point);
  afx_msg void onCopy();
  afx_msg void onPup1();
  afx_msg void onPup2();
  };



#ifndef _DEBUG  // debug version in AddrBookMergeView.cpp
inline AddrBookMergeDoc* AddrBookMergeView::GetDocument() const
                                           {return reinterpret_cast<AddrBookMergeDoc*>(m_pDocument);}
#endif





#ifdef Examples
#include "StoreRpt.h"
#endif
#ifdef Examples
StoreRpt   dspStore;
StoreRpt   prtStore;
#endif
#ifdef Examples
  StoreRpt&       storeRpt()  {return dspStore;}
#endif

