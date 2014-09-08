format 74

classcanvas 128111 class_ref 164207 // Operation
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 240.5 238 2006
end
classcanvas 128239 class_ref 171119 // ParamData
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 526.5 265 2000
end
classcanvas 128367 class_ref 164463 // Identifiable
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 257.5 51 2000
end
classcanvas 128879 class_ref 170991 // DataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 261 416 3005
end
relationcanvas 128751 relation_ref 175471 // <directional composition>
  from ref 128111 z 2007 stereotype "<<list>>" xyz 395 283 3000 to ref 128239
  role_a_pos 448 279 3000 no_role_b
  multiplicity_a_pos 510 308 3000 no_multiplicity_b
end
relationcanvas 129135 relation_ref 175727 // <directional composition>
  from ref 128239 z 3006 to ref 128879
  role_a_pos 341 404 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129647 relation_ref 219503 // <directional composition>
  from ref 128111 z 3006 to ref 128879
  role_a_pos 305 394 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129775 relation_ref 277871 // <generalisation>
  from ref 128239 z 2001 to ref 128367
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129903 relation_ref 277743 // <generalisation>
  from ref 128111 z 2007 to ref 128367
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
