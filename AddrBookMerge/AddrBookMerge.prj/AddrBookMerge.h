// AddrBookMerge.h : main header file for the AddrBookMerge application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class AddrBookMergeDoc;
class AddrBookMergeView;


class AddrBookMerge : public CApp {

String roamPath;
String appPath;

public:

               AddrBookMerge() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          AddrBookMergeDoc*  doc()         {return (AddrBookMergeDoc*)  CApp::getDoc();}
          AddrBookMergeView* view()        {return (AddrBookMergeView*) CApp::getView();}
          MainFrame*       mainFrm()     {return (MainFrame*)       m_pMainWnd;}
          String&          roamingPath() {return roamPath;}
          String&          thisAppPath() {return appPath;}

  DECLARE_MESSAGE_MAP()

  afx_msg void onAppAbout();
  afx_msg void onHelp();
  };


extern AddrBookMerge theApp;

inline void             invalidate() {theApp.invalidate();}
inline AddrBookMergeDoc*  doc()        {return theApp.doc();}
inline AddrBookMergeView* view()       {return theApp.view();}
inline MainFrame*       mainFrm()    {return theApp.mainFrm();}
inline MyToolBar&       getToolBar() {return mainFrm()->getToolBar();}

