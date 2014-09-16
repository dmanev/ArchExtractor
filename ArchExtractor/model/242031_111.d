format 74

classcanvas 128111 class_ref 164079 // SenderReceiverInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 658 355 2000
end
classcanvas 128367 class_ref 185199 // ArrayDataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 27 330 2005
end
classcanvas 128495 class_ref 164335 // DataElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 401.5 356.5 2006
end
classcanvas 128623 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 38 220.5 2000
end
classcanvas 128751 class_ref 218351 // StkPortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 379.5 6.5 3005
end
classcanvas 130031 class_ref 238447 // StkCFileReqWriteDataCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 152 221 2000
end
classcanvas 130671 class_ref 163567 // RequiredPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 270.5 352.5 2000
end
relationcanvas 129519 relation_ref 227951 // <dependency>
  decenter_end 298
  from ref 128751 z 3006 stereotype "<<import>>" xyz 186.5 158 3006 to ref 128623
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129647 relation_ref 167663 // <directional composition>
  from ref 128111 z 2007 stereotype "<<list>>" xyz 569 392.5 3000 to ref 128495
  role_a_pos 519 369 3000 no_role_b
  multiplicity_a_pos 519 398 3000 no_multiplicity_b
end
relationcanvas 130159 relation_ref 253039 // <generalisation>
  decenter_begin 497
  from ref 130031 z 3006 to ref 128751
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130287 relation_ref 253167 // <dependency>
  decenter_begin 261
  from ref 130031 z 2006 stereotype "<<import>>" xyz 222.5 304 3000 to ref 128367
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130415 relation_ref 253295 // <dependency>
  decenter_begin 789
  from ref 130031 z 2001 stereotype "<<import>>" xyz 628.5 313.5 3000 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130543 relation_ref 253423 // <dependency>
  from ref 130031 z 2007 stereotype "<<import>>" xyz 422 310 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130799 relation_ref 253551 // <dependency>
  decenter_begin 370
  from ref 130031 z 2001 stereotype "<<import>>" xyz 320.5 312 3000 to ref 130671
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130927 relation_ref 253679 // <dependency>
  from ref 130031 z 2001 stereotype "<<import>>" xyz 73 246.5 3000 to ref 128623
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
