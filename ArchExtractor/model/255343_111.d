format 74

classcanvas 128367 class_ref 185327 // BasePortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 389 18.5 2000
end
classcanvas 128495 class_ref 211695 // StkTOSSignalIf
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 483 213.5 2000
end
classcanvas 128623 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 36.5 116.5 2000
end
classcanvas 131055 class_ref 163567 // RequiredPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 264.5 213.5 2000
end
classcanvas 131439 class_ref 251759 // StkCFileReqWriteTOSSignalCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 147 119 2000
end
relationcanvas 131567 relation_ref 268015 // <generalisation>
  decenter_begin 500
  from ref 131439 z 2001 to ref 128367
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131695 relation_ref 268143 // <dependency>
  from ref 131439 z 2001 stereotype "<<import>>" xyz 75 151.5 3000 to ref 128623
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131823 relation_ref 268271 // <dependency>
  decenter_end 471
  from ref 131439 z 2001 stereotype "<<import>>" xyz 497 174.5 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131951 relation_ref 268399 // <dependency>
  from ref 131439 z 2001 stereotype "<<import>>" xyz 325 177.5 3000 to ref 131055
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
