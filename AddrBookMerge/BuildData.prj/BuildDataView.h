// BuildDataView.h : interface of the BuildDataView class


#pragma once
#include "CScrView.h"

class BuildDataDoc;
class DevStream;


class BuildDataView : public CScrView {

protected: // create from serialization only

  BuildDataView() noexcept;

  DECLARE_DYNCREATE(BuildDataView)

public:

  virtual ~BuildDataView() { }

  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn()  { }
  virtual void       saveRptOrietn()  { }
  virtual PrtrOrient getOrientation() {return NilOrient;}

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void onPreparePrinting(CPrintInfo* info) {prtNote.onPreparePrinting(info);}
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void printHeader(DevStream& dev, int pageNo);
  virtual void printFooter(DevStream& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  BuildDataDoc* GetDocument() const;

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
  };


#ifndef _DEBUG  // debug version in BuildDataView.cpp
inline BuildDataDoc* BuildDataView::GetDocument() const
                                            {return reinterpret_cast<BuildDataDoc*>(m_pDocument);}
#endif

