format 74

classcanvas 128111 class_ref 218223 // StkJilDataCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 208 196 2000
end
classcanvas 128239 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 40.5 194.5 2000
end
classcanvas 128751 class_ref 163695 // ProvidedPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 386 361 2000
end
classcanvas 129007 class_ref 163567 // RequiredPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 254 361 2000
end
classcanvas 129263 class_ref 164079 // SenderReceiverInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 777 371 2000
end
classcanvas 129775 class_ref 218351 // StkPortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 435 40 2000
end
classcanvas 130159 class_ref 185199 // ArrayDataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 55 347 2005
end
classcanvas 130415 class_ref 164335 // DataElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 515.5 369.5 2006
end
relationcanvas 128623 relation_ref 226415 // <dependency>
  from ref 128111 z 2001 stereotype "<<import>>" xyz 95.5 227.5 3000 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128879 relation_ref 226543 // <dependency>
  from ref 128111 z 2001 stereotype "<<import>>" xyz 436.5 303.5 3000 to ref 128751
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129135 relation_ref 226799 // <dependency>
  from ref 128111 z 2001 stereotype "<<import>>" xyz 359.5 315 3000 to ref 129007
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129391 relation_ref 226927 // <dependency>
  decenter_end 57
  from ref 128111 z 2001 stereotype "<<import>>" xyz 673 297 3000 to ref 129263
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129903 relation_ref 227823 // <generalisation>
  decenter_begin 487
  decenter_end 453
  from ref 128111 z 2001 to ref 129775
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130031 relation_ref 227951 // <dependency>
  from ref 129775 z 2001 stereotype "<<import>>" xyz 235 121 3000 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130287 relation_ref 228079 // <dependency>
  from ref 128111 z 2006 stereotype "<<import>>" xyz 316.5 283.5 3000 to ref 130159
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130543 relation_ref 167663 // <directional composition>
  from ref 129263 z 2007 stereotype "<<list>>" xyz 678 404.5 3000 to ref 130415
  role_a_pos 633 383 3000 no_role_b
  multiplicity_a_pos 633 412 3000 no_multiplicity_b
end
relationcanvas 130671 relation_ref 229487 // <dependency>
  from ref 128111 z 2007 stereotype "<<import>>" xyz 529.5 292.5 3000 to ref 130415
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
