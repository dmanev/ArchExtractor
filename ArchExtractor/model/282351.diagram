format 74

classinstance 128111 class_ref 278511 // XMIConverter
  name ""   xyz 233 5 2000 life_line_z 2000
classinstance 128239 class_ref 137071 // User
  name ""   xyz 36 4 2000 life_line_z 2000
fragment 129263 "loop for aePack in inpAEModel.itsAEPackageList"
  xyzwh 107 206 2015 563 450
end
note 129519 "* Convert inpAEModel
into XMI model"
  xyzwh 367 36 2000 203 71
durationcanvas 128367 classinstance_ref 128239 // :User
  xyzwh 47 116 2010 11 610
end
durationcanvas 128495 classinstance_ref 128111 // :XMIConverter
  xyzwh 272 116 2010 11 610
end
msg 128623 synchronous
  from durationcanvas_ref 128367
  to durationcanvas_ref 128495
  yz 116 2015 msg operation_ref 275695 // "convert(in self : , in inpAEModel : AEModel, out outXMIMdlRepo : )"
  show_full_operations_definition default drawing_language default show_context_mode default
  args "inpAEModel, outXMIModel"
  label_xy 69 101
msg 129007 return
  from durationcanvas_ref 128495
  to durationcanvas_ref 128367
  yz 715 2020 explicitmsg "outXMIModel"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 121 699
end
