format 74

classcanvas 128367 class_ref 185327 // BasePortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 402 41.5 2000
end
classcanvas 128495 class_ref 211695 // StkTOSSignalIf
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 541 250.5 2000
end
classcanvas 128623 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 48.5 147.5 2000
end
classcanvas 130415 class_ref 251631 // StkCFileReqReadTOSSignalCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 160 149 2000
end
classcanvas 131055 class_ref 163567 // RequiredPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 263.5 250.5 2000
end
relationcanvas 130671 relation_ref 267503 // <generalisation>
  decenter_begin 497
  from ref 130415 z 2001 to ref 128367
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130799 relation_ref 267631 // <dependency>
  from ref 130415 z 2001 stereotype "<<import>>" xyz 76.5 177 3000 to ref 128623
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130927 relation_ref 267759 // <dependency>
  from ref 130415 z 2001 stereotype "<<import>>" xyz 516.5 207 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131183 relation_ref 267887 // <dependency>
  from ref 130415 z 2001 stereotype "<<import>>" xyz 329 212 3000 to ref 131055
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
