format 74

classinstance 128111 class_ref 128751 // BaseFileParser
  name ""   xyz 361 6 2000 life_line_z 2000
classinstance 128239 class_ref 129519 // IAnalyzer
  name ""   xyz 37 5 2000 life_line_z 2000
classinstance 129007 class_ref 130415 // IPortCriteria
  name ""   xyz 709 4 2000 life_line_z 2000
fragment 129135 "loop for each iPortCriteria in itsIPortCriteria"
  xyzwh 141 354 1995 713 225
end
continuation 130031 "Perform Text analyzis"
  xyzwh 671.5 406.5 2015 149 37
continuation 130159 "Update Component"
  xyzwh 666.5 479.5 2015 153 41
note 130287 "Validity check as well"
  xyzwh 247 207 2000 145 37
fragment 130543 "alt validity check passes OK"
  xyzwh 122 313 2000 753 279
end
durationcanvas 128367 classinstance_ref 128239 // :IAnalyzer
  xyzwh 60 129 2010 11 487
end
durationcanvas 128495 classinstance_ref 128111 // :BaseFileParser
  xyzwh 405 128 2010 11 487
  overlappingdurationcanvas 129647
    xyzwh 411 248 2020 11 25
  end
end
durationcanvas 129263 classinstance_ref 129007 // :IPortCriteria
  xyzwh 739 376 2010 11 187
end
msg 128623 synchronous
  from durationcanvas_ref 128367
  to durationcanvas_ref 128495
  yz 129 2015 msg operation_ref 149359 // "fulfillComponentData(in self : any, in cmpName : string, in filePath : string, inout inoutIComponent : IComponent)"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "inpIComponent, cmpName, filePath"
  label_xy 82 113
msg 128879 return
  from durationcanvas_ref 128495
  to durationcanvas_ref 128367
  yz 596 2015 unspecifiedmsg
  show_full_operations_definition default drawing_language default show_context_mode default
msg 129391 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 129263
  yz 380 2020 msg operation_ref 182127 // "execute(in self : , in inpTextContent : string, inout inoutIComponent : IComponent) : IComponent"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "inpTextContent, inpIComponent"
  label_xy 447 364
msg 129519 return
  from durationcanvas_ref 129263
  to durationcanvas_ref 128495
  yz 548 2015 unspecifiedmsg
  show_full_operations_definition default drawing_language default show_context_mode default
reflexivemsg 129775 synchronous
  to durationcanvas_ref 129647
  yz 248 2025 msg operation_ref 182255 // "preprocessFile(in self : any, in inpFilePath : string) : bool"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "filePath"
  label_xy 421 230
line 130415 -_-_
  from ref 130287 z 2021 to ref 129647
end
