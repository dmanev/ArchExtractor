format 74

classcanvas 128111 class_ref 258671 // AEPackage
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 161 377 2000
end
classcanvas 128239 class_ref 258799 // PackageableElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 434 303 2000
end
classcanvas 129903 class_ref 164463 // Identifiable
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 378 85 2006
end
classcanvas 130287 class_ref 258927 // AEModel
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 148 81 2000
end
relationcanvas 128495 relation_ref 276975 // <directional aggregation>
  from ref 128111 z 2001 stereotype "<<map>>" xyz 331 400 3000 to ref 128239
  role_a_pos 342 341 3000 no_role_b
  multiplicity_a_pos 418 370 3000 no_multiplicity_b
end
relationcanvas 129007 relation_ref 277231 // <directional aggregation>
  from ref 128111 z 2001 stereotype "<<list>>" xyz 98 420 3000 to point 131 377
  line 129135 z 2001 to point 131 407
  line 129263 z 2001 to ref 128111
  role_a_pos 55 405 3000 no_role_b
  multiplicity_a_pos 145 434 3000 no_multiplicity_b
end
relationcanvas 130031 relation_ref 277103 // <generalisation>
  from ref 128111 z 2007 to ref 129903
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130159 relation_ref 276719 // <generalisation>
  from ref 128239 z 2007 to ref 129903
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130543 relation_ref 278511 // <directional aggregation>
  from ref 130287 z 2001 stereotype "<<list>>" xyz 183 311.5 3000 to ref 128111
  role_a_pos 241 355 3000 no_role_b
  multiplicity_a_pos 216 355 3000 no_multiplicity_b
end
relationcanvas 130799 relation_ref 292335 // <directional aggregation>
  from ref 128239 z 2001 to point 342 497
  line 130927 z 2001 to ref 128111
  role_a_pos 311 465 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131055 relation_ref 301551 // <generalisation>
  from ref 130287 z 2007 to ref 129903
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131183 relation_ref 301807 // <directional aggregation>
  decenter_begin 710
  decenter_end 915
  from ref 128111 z 2001 to point 135 474
  line 131311 z 2001 to point 135 504
  line 131695 z 2001 to ref 128111
  role_a_pos 54 510 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
