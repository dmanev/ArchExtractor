format 74

classinstance 128111 class_ref 137071 // User
  name ""   xyz 31 4 2000 life_line_z 2000
classinstance 128239 class_ref 128111 // BaseAnalyzer
  name ""   xyz 362 4 2000 life_line_z 2000
classinstance 128751 class_ref 143599 // os
  name ""   xyz 673 7 2000 life_line_z 2000
classinstance 129135 class_ref 128751 // BaseFileParser
  name ""   xyz 731 5 2005 life_line_z 2000
fragment 129263 "loop for each dirPath, dirList, fileList in os.walk(topDir)"
  xyzwh 75 162 1970 815 557
end
fragment 129903 "loop for BFParser in self.itsBaseFileParserList"
  xyzwh 104 269 1975 756 429
end
fragment 130415 "alt bResult=True"
  xyzwh 127 365 1980 703 314
end
fragment 131183 "loop for cmpName in componentNameList"
  xyzwh 147 450 1985 660 210
end
note 132463 "Walk over Project under analysis files/directories structure"
  xyzwh 818 77 2000 167 69
note 132847 "based on Component's name it will either be found in the AEModel or it will be created"
  xyzwh 819 422 2000 167 91
note 133103 "Component's details will be updated"
  xyzwh 819 545 2000 163 65
durationcanvas 128367 classinstance_ref 128111 // :User
  xyzwh 42 93 2010 11 672
end
durationcanvas 128495 classinstance_ref 128239 // :BaseAnalyzer
  xyzwh 402 94 2010 11 665
end
durationcanvas 128879 classinstance_ref 128751 // :os
  xyzwh 679 114 2010 11 44
end
durationcanvas 129519 classinstance_ref 128751 // :os
  xyzwh 679 211 2010 11 31
end
durationcanvas 130031 classinstance_ref 129135 // :BaseFileParser
  xyzwh 775 316 2010 11 37
end
durationcanvas 130543 classinstance_ref 129135 // :BaseFileParser
  xyzwh 775 396 2010 11 40
end
durationcanvas 130927 classinstance_ref 128111 // :User
  xyzwh 42 660 2010 11 99
end
durationcanvas 131311 classinstance_ref 128751 // :os
  xyzwh 679 480 2010 11 33
end
durationcanvas 131695 classinstance_ref 129135 // :BaseFileParser
  xyzwh 775 542 2010 11 31
end
durationcanvas 132079 classinstance_ref 129135 // :BaseFileParser
  xyzwh 775 596 2010 11 34
end
msg 128623 synchronous
  from durationcanvas_ref 128367
  to durationcanvas_ref 128495
  yz 98 2015 msg operation_ref 353775 // "scan(in self : IAnalyzer, in topDir : string, inout inoutAEModel : AEModel)"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "ProjectDir, inOutAEModel"
  label_xy 112 82
msg 129007 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 128879
  yz 123 2015 explicitmsg "os.walk()"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "topDir"
  label_xy 453 107
msg 129391 return
  from durationcanvas_ref 128879
  to durationcanvas_ref 128495
  yz 147 2020 unspecifiedmsg
  show_full_operations_definition default drawing_language default show_context_mode default
msg 129647 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 129519
  yz 214 2015 explicitmsg "os.path.join()"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "dirPath, fileList"
  label_xy 453 198
msg 129775 return
  from durationcanvas_ref 129519
  to durationcanvas_ref 128495
  yz 231 2015 explicitmsg "filePath"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 432 221
msg 130159 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 130031
  yz 321 2015 msg operation_ref 157551 // "fileFilter(in self : , in fileName : string)"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "filePath"
  label_xy 523 305
msg 130287 return
  from durationcanvas_ref 130031
  to durationcanvas_ref 128495
  yz 342 2020 explicitmsg "bResult"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 431 330
msg 130671 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 130543
  yz 398 2015 msg operation_ref 129391 // "getComponentNameList(in self : , in fileName : )"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "filePath"
  label_xy 478 382
msg 130799 return
  from durationcanvas_ref 130543
  to durationcanvas_ref 128495
  yz 425 2020 explicitmsg "ComponentNameList"
  stereotype "<<list>>" xyz 546 433 3000
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 511 409
msg 131055 return
  from durationcanvas_ref 128495
  to durationcanvas_ref 130927
  yz 748 2015 explicitmsg "inOutAEModel"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 186 732
msg 131439 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 131311
  yz 480 2015 explicitmsg "os.path.relpath(filePath, os.path.split(topDir)[0])"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 417 462
msg 131567 return
  from durationcanvas_ref 131311
  to durationcanvas_ref 128495
  yz 502 2020 explicitmsg "baseDir"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 431 489
msg 131823 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 131695
  yz 543 2015 msg operation_ref 188783 // "updateComponent(in self : any, in inpName : string, in filePath : string, out outIComponent : IComponent) : IComponent"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "cmpName, baseDir, iCmp"
  label_xy 468 527
msg 131951 return
  from durationcanvas_ref 131695
  to durationcanvas_ref 128495
  yz 562 2015 explicitmsg "iCmp"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 432 551
msg 132207 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 132079
  yz 598 2015 msg operation_ref 189039 // "fulfillComponentData(in self : any, in cmpName : string, in filePath : string, inout inoutIComponent : IComponent)"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "cmpName, filePath, iCmp"
  label_xy 462 582
msg 132335 return
  from durationcanvas_ref 132079
  to durationcanvas_ref 128495
  yz 619 2020 explicitmsg "iCmp"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 436 604
line 132719 -_-_
  from ref 132463 z 2011 to ref 128879
line 132975 -_-_
  from ref 132847 z 2011 to ref 131695
line 133231 -_-_
  from ref 133103 z 2011 to ref 132079
end
