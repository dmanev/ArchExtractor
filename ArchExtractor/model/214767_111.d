format 74

classcanvas 128239 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 29.5 148 2000
end
classcanvas 128367 class_ref 211567 // StkJilTOSSignalCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 146 149 2000
end
classcanvas 128751 class_ref 163695 // ProvidedPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 244.5 243.5 2000
end
classcanvas 128879 class_ref 211695 // StkTOSSignalIf
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 493 243.5 2000
end
classcanvas 129263 class_ref 185327 // BasePortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 388 29 2000
end
relationcanvas 128623 relation_ref 218863 // <dependency>
  from ref 128367 z 2001 stereotype "<<import>>" xyz 58.5 180.5 3000 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129007 relation_ref 219631 // <dependency>
  from ref 128367 z 2001 stereotype "<<import>>" xyz 488 205.5 3000 to ref 128879
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129135 relation_ref 219759 // <dependency>
  from ref 128367 z 2001 stereotype "<<import>>" xyz 312 209 3000 to ref 128751
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129391 relation_ref 227567 // <generalisation>
  decenter_begin 499
  from ref 128367 z 2001 to ref 129263
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
