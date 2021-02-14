// AddrBookMergeView.h : interface of the AddrBookMergeView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class AddrBookMergeDoc;


class AddrBookMergeView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;

protected: // create from serialization only

  AddrBookMergeView() noexcept;

  DECLARE_DYNCREATE(AddrBookMergeView)

public:

  virtual ~AddrBookMergeView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  AddrBookMergeDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in AddrBookMergeView.cpp
inline AddrBookMergeDoc* AddrBookMergeView::GetDocument() const
   { return reinterpret_cast<AddrBookMergeDoc*>(m_pDocument); }
#endif

