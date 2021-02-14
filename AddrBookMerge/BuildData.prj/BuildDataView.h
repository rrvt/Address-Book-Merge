// BuildDataView.h : interface of the BuildDataView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"
#ifdef Examples
#include "StoreRpt.h"
#endif

class BuildDataDoc;


class BuildDataView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;
#ifdef Examples
StoreRpt   dspStore;
StoreRpt   prtStore;
#endif

protected: // create from serialization only

  BuildDataView() noexcept;

  DECLARE_DYNCREATE(BuildDataView)

public:

  virtual ~BuildDataView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  BuildDataDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in BuildDataView.cpp
inline BuildDataDoc* BuildDataView::GetDocument() const
   { return reinterpret_cast<BuildDataDoc*>(m_pDocument); }
#endif

