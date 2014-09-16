format 74

classcanvas 128239 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 30.5 131.5 2000
end
classcanvas 128367 class_ref 211439 // StkJilProdControlCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 156 134 2000
end
classcanvas 128879 class_ref 204911 // StkControlIf
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 526.5 233 2000
end
classcanvas 129135 class_ref 163695 // ProvidedPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 271 233 2000
end
classcanvas 129391 class_ref 185327 // BasePortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 398 17 2006
end
relationcanvas 128623 relation_ref 218351 // <dependency>
  decenter_end 508
  from ref 128367 z 2001 stereotype "<<import>>" xyz 63 161 3000 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129007 relation_ref 218479 // <dependency>
  from ref 128367 z 2001 stereotype "<<import>>" xyz 504 191 3000 to ref 128879
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129263 relation_ref 218607 // <dependency>
  from ref 128367 z 2001 stereotype "<<import>>" xyz 332 195 3000 to ref 129135
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129519 relation_ref 227439 // <generalisation>
  decenter_begin 499
  from ref 128367 z 2007 to ref 129391
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
