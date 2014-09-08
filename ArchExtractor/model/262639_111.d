format 74

classcanvas 128111 class_ref 258799 // PackageableElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 51.5 251.5 2000
end
classcanvas 128239 class_ref 164463 // Identifiable
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 84 76 2005
end
classcanvas 128495 class_ref 258671 // AEPackage
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 375 213 3005
end
relationcanvas 128367 relation_ref 276719 // <generalisation>
  from ref 128111 z 2006 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128623 relation_ref 277103 // <generalisation>
  from ref 128495 z 3006 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128751 relation_ref 276975 // <directional aggregation>
  from ref 128495 z 3006 stereotype "<<map>>" xyz 256 284 3006 to ref 128111
  role_a_pos 201 264 3000 no_role_b
  multiplicity_a_pos 201 293 3000 no_multiplicity_b
end
relationcanvas 129391 relation_ref 292335 // <directional aggregation>
  from ref 128111 z 3006 to point 171 399
  line 129519 z 3006 to ref 128495
  role_a_pos 214 387 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
