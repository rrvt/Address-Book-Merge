

AddrBookMerge.chm : *.htm AddrBookMerge.hhp AddrBookMerge.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" AddrBookMerge


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist AddrBookMerge.chm del /F AddrBookMerge.chm


$(TgtFolder)/AddrBookMerge.chm : AddrBookMerge.chm
  copy $(MAKEDIR)\AddrBookMerge.chm  $(MAKEDIR)\..\$(TgtFolder)\AddrBookMerge.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist AddrBookMerge.chm del /F AddrBookMerge.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/AddrBookMerge.chm


