// BuildDataDoc.h : interface of the BuildDataDoc class


#pragma once
#include "CDoc.h"
#include "CodeBldr.h"
#include "MainFrame.h"
#include "TBComboBox.h"
#include "TBEditBox.h"


enum DataSource {NilSrc, NotePadSrc, AddrSrc, HeaderSrc, BodySrc, StoreSrc};


class BuildDataDoc : public CDoc {

PathDlgDsc  pathDsc;

DataSource  dataSource;

protected: // create from serialization only

  BuildDataDoc() noexcept;
  DECLARE_DYNCREATE(BuildDataDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~BuildDataDoc();
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
  afx_msg void OnPickEmail();
  afx_msg void OnPrepAddr_h();
  afx_msg void OnPrepAddr_cpp();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();

#ifdef Examples
  afx_msg void OnTest();
  afx_msg void displayDataStore();
  afx_msg void myButton();

  afx_msg void OnComboBoxChng();

  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
  afx_msg void onOption1();
  afx_msg void onOption2();
  afx_msg void onOption3();
  afx_msg void onOption21();
  afx_msg void onOption22();
  afx_msg void onOption23();
  afx_msg void OnTestEditBoxes();
#endif
  };
