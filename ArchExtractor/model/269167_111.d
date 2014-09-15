format 74

classcanvas 128111 class_ref 265455 // ComponentFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations yes show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 24 163 2000
end
classcanvas 128239 class_ref 129647 // IComponent
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 283 14 2000
end
classcanvas 128495 class_ref 128239 // BaseComponent
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 637 8 2006
end
relationcanvas 128367 relation_ref 285039 // <directional aggregation>
  from ref 128111 z 2001 stereotype "<<map>>" xyz 269.5 131 3000 to ref 128239
  role_a_pos 331 108 3000 no_role_b
  multiplicity_a_pos 306 108 3000 no_multiplicity_b
end
relationcanvas 128623 relation_ref 128751 // <realization>
  from ref 128495 z 2007 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128751 relation_ref 285167 // <dependency>
  from ref 128111 z 2007 stereotype "<<import>>" xyz 510 121 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
