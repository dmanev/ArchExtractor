format 74

classcanvas 128111 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 43.5 232 2000
end
classcanvas 129007 class_ref 163695 // ProvidedPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 301.5 376.5 2000
end
classcanvas 129263 class_ref 164079 // SenderReceiverInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 716.5 385.5 2000
end
classcanvas 129391 class_ref 164335 // DataElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 456 385 2006
end
classcanvas 129903 class_ref 185199 // ArrayDataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 86.5 361.5 2005
end
classcanvas 130287 class_ref 218351 // StkPortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 405 14 3005
end
classcanvas 130799 class_ref 237935 // StkCHeaderProvWriteDataCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 178 234 2000
end
relationcanvas 129519 relation_ref 167663 // <directional composition>
  from ref 129263 z 2007 stereotype "<<list>>" xyz 618 420 3000 to ref 129391
  role_a_pos 574 399 3000 no_role_b
  multiplicity_a_pos 574 428 3000 no_multiplicity_b
end
relationcanvas 130415 relation_ref 227951 // <dependency>
  decenter_end 263
  from ref 130287 z 3006 stereotype "<<import>>" xyz 202.5 166 3006 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130927 relation_ref 250479 // <generalisation>
  decenter_begin 499
  from ref 130799 z 3006 to ref 130287
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131311 relation_ref 250607 // <dependency>
  from ref 130799 z 2001 stereotype "<<import>>" xyz 88.5 260 3000 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131439 relation_ref 250735 // <dependency>
  from ref 130799 z 2001 stereotype "<<import>>" xyz 382.5 330 3000 to ref 129007
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131567 relation_ref 250863 // <dependency>
  from ref 130799 z 2006 stereotype "<<import>>" xyz 309 328.5 3000 to ref 129903
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131695 relation_ref 250991 // <dependency>
  from ref 130799 z 2001 stereotype "<<import>>" xyz 594.5 334 3000 to ref 129263
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131823 relation_ref 251119 // <dependency>
  from ref 130799 z 2007 stereotype "<<import>>" xyz 463.5 331 3000 to ref 129391
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
