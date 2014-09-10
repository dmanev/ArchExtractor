format 74

classcanvas 128111 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 321.5 63 2000
end
classcanvas 128623 class_ref 224879 // StkCHeaderProvReadDataCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 70 218 2000
end
classcanvas 129007 class_ref 163695 // ProvidedPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 132.5 383.5 2000
end
classcanvas 129263 class_ref 164079 // SenderReceiverInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 424.5 303.5 2000
end
classcanvas 129391 class_ref 164335 // DataElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 298 401 2006
end
classcanvas 129903 class_ref 185199 // ArrayDataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 455.5 79.5 2005
end
classcanvas 130287 class_ref 218351 // StkPortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 66 39 3005
end
relationcanvas 128879 relation_ref 236143 // <dependency>
  from ref 128623 z 2001 stereotype "<<import>>" xyz 264 147 3000 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129135 relation_ref 236271 // <dependency>
  from ref 128623 z 2001 stereotype "<<import>>" xyz 142 325 3000 to ref 129007
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129519 relation_ref 167663 // <directional composition>
  from ref 129263 z 2007 stereotype "<<list>>" xyz 400 389 3000 to ref 129391
  role_a_pos 385 374 3000 no_role_b
  multiplicity_a_pos 385 403 3000 no_multiplicity_b
end
relationcanvas 129647 relation_ref 236399 // <dependency>
  from ref 128623 z 2001 stereotype "<<import>>" xyz 314 292 3000 to ref 129263
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129775 relation_ref 236527 // <dependency>
  from ref 128623 z 2007 stereotype "<<import>>" xyz 260 324 3000 to ref 129391
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130159 relation_ref 236783 // <dependency>
  from ref 128623 z 2006 stereotype "<<import>>" xyz 319 181 3000 to ref 129903
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130415 relation_ref 227951 // <dependency>
  from ref 130287 z 3006 stereotype "<<import>>" xyz 231 86 3006 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130671 relation_ref 243439 // <generalisation>
  decenter_begin 311
  from ref 128623 z 3006 to ref 130287
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
