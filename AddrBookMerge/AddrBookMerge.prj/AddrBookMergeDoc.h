// AddrBookMergeDoc.h : interface of the AddrBookMergeDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"
#include "TBComboBox.h"
#include "TBEditBox.h"


enum DataSource {NotePadSrc, StoreSrc, AddrMergSrc};


class AddrBookMergeDoc : public CDoc {

PathDlgDsc  pathDsc;

DataSource  dataSource;

protected: // create from serialization only

  AddrBookMergeDoc() noexcept;
  DECLARE_DYNCREATE(AddrBookMergeDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~AddrBookMergeDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void testLine(int n);
  void wholePage();

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnFileOpen();
  afx_msg void OnAddBook();
  afx_msg void OnProcess();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();
  };
