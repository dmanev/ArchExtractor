format 74

classcanvas 128111 class_ref 137071 // User
  class_drawing_mode default show_context_mode default show_stereotype_properties default
  xyz 45 340 2000
end
usecasecanvas 128239 usecase_ref 128111 // Create Architecture model
  xyzwh 552 251 3005 64 32 label_xy 514 283
end
usecasecanvas 128367 usecase_ref 128239 // Extract architecture data
  xyzwh 466 392 3005 64 32 label_xy 433 424
end
usecasecanvas 128495 usecase_ref 128367 // Perform analysis
  xyzwh 227 274 3011 64 32 label_xy 214 306
end
usecasecanvas 128751 usecase_ref 128495 // Prepare File criteria
  xyzwh 419 202 3005 64 32 label_xy 398 234
end
usecasecanvas 128879 usecase_ref 128623 // Prepare analysis criteria
  xyzwh 219 129 3011 64 32 label_xy 185 161
end
usecasecanvas 129135 usecase_ref 128751 // Prepare component criteria
  xyzwh 495 136 3017 64 32 label_xy 453 168
end
usecasecanvas 129391 usecase_ref 128879 // Prepare connector criteria
  xyzwh 407 75 3017 64 32 label_xy 369 107
end
usecasecanvas 129647 usecase_ref 129007 // Scan source files
  xyzwh 375 275 3017 64 32 label_xy 361 307
end
subject 130287 "Architecture Extractor"
  xyzwh 119 17 2000 564 544
classcanvas 130543 class_ref 292079 // Configurator
  class_drawing_mode default show_context_mode default show_stereotype_properties default
  xyz 27 112 2005
end
usecasecanvas 131567 usecase_ref 135535 // Serialize UML model
  xyzwh 227 357 3005 64 32 label_xy 202 389
end
usecasecanvas 132079 usecase_ref 135663 // Generate Base code
  xyzwh 224 445 3005 64 32 label_xy 200 477
end
simplerelationcanvas 129007 simplerelation_ref 141807
  from ref 128879 z 3012 stereotype "<<include>>" xyz 316 180 3000 to ref 128751
end
simplerelationcanvas 129263 simplerelation_ref 142319
  from ref 128879 z 3018 stereotype "<<include>>" xyz 354 146 3000 to ref 129135
end
simplerelationcanvas 129519 simplerelation_ref 142191
  from ref 128879 z 3018 stereotype "<<include>>" xyz 299 97 3000 to ref 129391
end
simplerelationcanvas 129775 simplerelation_ref 141935
  from ref 129647 z 3018 stereotype "<<include>>" xyz 417 348 3000 to ref 128367
end
simplerelationcanvas 129903 simplerelation_ref 142063
  from ref 128495 z 3018 stereotype "<<include>>" xyz 298 289 3000 to ref 129647
end
line 130159 ----
  from ref 128111 z 3012 to ref 128495
line 131055 ----
  from ref 130543 z 3012 to ref 128879
relationcanvas 131183 relation_ref 336879 // <generalisation>
  from ref 130543 z 2006 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
simplerelationcanvas 131439 simplerelation_ref 228591
  from ref 128367 z 3006 stereotype "<<include>>" xyz 503 336 3000 to ref 128239
end
line 131823 ----
  from ref 128111 z 3006 to ref 131567
line 132207 ----
  from ref 128111 z 3006 to ref 132079
end
