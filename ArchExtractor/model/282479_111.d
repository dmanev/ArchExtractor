format 74

classcanvas 128111 class_ref 164463 // Identifiable
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations yes show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 286.5 47 2006
end
classcanvas 128239 class_ref 258927 // AEModel
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility yes show_members_stereotype default show_members_context default show_members_multiplicity yes show_members_initialization yes show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 97.5 196.5 2000
end
classcanvas 128367 class_ref 258671 // AEPackage
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations yes show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 273.5 477.5 2000
end
classcanvas 129903 class_ref 271983 // InfrastructureFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 693 76 2000
end
classcanvas 130287 class_ref 258287 // PortInterfaceFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations yes show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 693 308.5 2000
end
classcanvas 130415 class_ref 265455 // ComponentFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 693 187.5 2000
end
classcanvas 130927 class_ref 285423 // DataTypeFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations yes show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 693 437 2000
end
classcanvas 132207 class_ref 258543 // FactoryProvider
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations yes show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 32 47 2000
end
relationcanvas 128623 relation_ref 301551 // <generalisation>
  from ref 128239 z 2007 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129519 relation_ref 278511 // <directional aggregation>
  from ref 128239 z 2001 stereotype "<<list>>" xyz 271.5 429 3000 to ref 128367
  role_a_pos 333 455 3000 no_role_b
  multiplicity_a_pos 308 455 3000 no_multiplicity_b
end
relationcanvas 130031 relation_ref 301679 // <directional composition>
  decenter_begin 116
  from ref 128239 z 2001 to ref 129903
  role_a_pos 559 127 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130799 relation_ref 309999 // <directional composition>
  decenter_end 292
  from ref 128239 z 2001 to ref 130287
  role_a_pos 561 312 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131055 relation_ref 310127 // <directional composition>
  decenter_end 21
  from ref 128239 z 2001 to ref 130927
  role_a_pos 574 435 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 132079 relation_ref 310255 // <directional composition>
  decenter_begin 367
  from ref 128239 z 2001 to ref 130415
  role_a_pos 566 215 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 132335 relation_ref 310383 // <generalisation>
  from ref 128239 z 2001 to ref 132207
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
