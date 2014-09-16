format 74

classinstance 128111 class_ref 128751 // BaseFileParser
  name ""   xyz 372 10 2000 life_line_z 2000
classinstance 128239 class_ref 129519 // IAnalyzer
  name ""   xyz 37 5 2000 life_line_z 2000
fragment 129135 "loop for each BPCriteria in itsBasePortCriteriaList"
  xyzwh 116 259 1995 766 229
end
continuation 130031 "Perform Text analyzis on inpTextContent"
  xyzwh 611.5 315.5 2015 252 37
continuation 130159 "Update inOutIComponent"
  xyzwh 658.5 386.5 2015 171 41
note 130287 "Validity check as well"
  xyzwh 247 116 2000 145 37
fragment 130543 "alt validity check passes OK"
  xyzwh 103 223 1990 800 283
end
classinstance 130671 class_ref 185327 // BasePortCriteria
  name ""   xyz 689 8 2000 life_line_z 2000
durationcanvas 128367 classinstance_ref 128239 // :IAnalyzer
  xyzwh 60 73 2010 11 490
end
durationcanvas 128495 classinstance_ref 128111 // :BaseFileParser
  xyzwh 416 73 2010 11 480
  overlappingdurationcanvas 129647
    xyzwh 422 157 2020 11 25
  end
end
durationcanvas 130799 classinstance_ref 130671 // :BasePortCriteria
  xyzwh 736 278 2010 11 180
end
msg 128623 synchronous
  from durationcanvas_ref 128367
  to durationcanvas_ref 128495
  yz 73 2015 msg operation_ref 354159 // "fulfillComponentData(in self : IFileParser, in cmpName : string, in filePath : string, inout inoutIComponent : IComponent)"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "cmpName, filePath, inOutIComponent"
  label_xy 82 57
msg 128879 return
  from durationcanvas_ref 128495
  to durationcanvas_ref 128367
  yz 529 2015 explicitmsg "inOutIComponent"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 189 513
reflexivemsg 129775 synchronous
  to durationcanvas_ref 129647
  yz 157 2025 msg operation_ref 182255 // "preprocessFile(in self : any, in inpFilePath : string) : bool"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "filePath"
  label_xy 432 139
msg 130927 synchronous
  from durationcanvas_ref 128495
  to durationcanvas_ref 130799
  yz 278 3005 msg operation_ref 182127 // "execute(in self : , in inpTextContent : string, inout inoutIComponent : IComponent) : IComponent"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "inpTextContent, inOutIComponent"
  label_xy 489 264
msg 131055 return
  from durationcanvas_ref 130799
  to durationcanvas_ref 128495
  yz 443 2015 explicitmsg "inOutIComponent"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 538 427
line 130415 -_-_
  from ref 130287 z 2021 to ref 129647
end
