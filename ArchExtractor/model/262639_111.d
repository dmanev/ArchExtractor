format 74

classcanvas 128111 class_ref 258799 // PackageableElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 16.5 162.5 2000
end
classcanvas 128239 class_ref 164463 // Identifiable
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 48 44 2005
end
classcanvas 128495 class_ref 258671 // AEPackage
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 397 166.5 3005
end
relationcanvas 128367 relation_ref 276719 // <generalisation>
  from ref 128111 z 2006 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128623 relation_ref 277103 // <generalisation>
  decenter_begin 80
  from ref 128495 z 3006 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128751 relation_ref 276975 // <directional aggregation>
  decenter_begin 204
  decenter_end 521
  from ref 128495 z 3006 stereotype "<<map>>" xyz 250 197.5 3006 to ref 128111
  role_a_pos 166 177 3000 no_role_b
  multiplicity_a_pos 166 206 3000 no_multiplicity_b
end
relationcanvas 129391 relation_ref 292335 // <directional aggregation>
  decenter_end 683
  from ref 128111 z 3006 to point 83 273
  line 129519 z 3006 to ref 128495
  role_a_pos 290 254 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
