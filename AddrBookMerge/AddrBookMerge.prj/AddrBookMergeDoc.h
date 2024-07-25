// AddrBookMergeDoc.h : interface of the AddrBookMergeDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"

class CSVRcd;


enum DataSource {NotePadSrc, AddrMergSrc};        // , StoreSrc, StrRptSrc, FontSrc


class AddrBookMergeDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

int         nBooks;
String      books[32];

protected: // create from serialization only

  AddrBookMergeDoc() noexcept;
  DECLARE_DYNCREATE(AddrBookMergeDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds = NotePadSrc);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~AddrBookMergeDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void saveFile(TCchar* title, TCchar* suffix, TCchar* fileType);

  void testLine(int n);
  void wholePage();

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onFileOpen();
  afx_msg void onAddBook();
  afx_msg void onProcess();

  afx_msg void onSaveFile();

  afx_msg void onEditCopy();
  };






#ifdef Examples
  afx_msg void onSaveStrRpt();
  afx_msg void onSaveNotePad();
  afx_msg void OnTest();
  afx_msg void displayDataStore();
  afx_msg void myButton();

  afx_msg void OnComboBoxChng();

  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
  afx_msg void onOption11();
  afx_msg void onOption12();
  afx_msg void onOption13();
  afx_msg void onOption21();
  afx_msg void onOption22();
  afx_msg void onOption23();
  afx_msg void OnTestEditBoxes();
#endif

