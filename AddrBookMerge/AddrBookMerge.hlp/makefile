

AddrBookMerge.chm : *.htm AddrBookMerge.hhp AddrBookMerge.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" AddrBookMerge


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F AddrBookMerge.chm


Release/AddrBookMerge.chm : AddrBookMerge.chm
  copy $(MAKEDIR)\AddrBookMerge.chm  $(MAKEDIR)\..\Release\AddrBookMerge.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del AddrBookMerge.chm
  cd $(MAKEDIR)


Debug/AddrBookMerge.chm : AddrBookMerge.chm
  copy $(MAKEDIR)\AddrBookMerge.chm  $(MAKEDIR)\..\Debug\AddrBookMerge.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del AddrBookMerge.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/AddrBookMerge.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/AddrBookMerge.chm


