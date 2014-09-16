format 74

classcanvas 128111 class_ref 285423 // DataTypeFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 23 28 2000
end
classcanvas 128239 class_ref 170991 // DataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 305 37 2000
end
classcanvas 128623 class_ref 185199 // ArrayDataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 253 250 2006
end
classcanvas 128879 class_ref 185071 // CompositeDataType
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 276 152 2012
end
relationcanvas 128495 relation_ref 308463 // <directional aggregation>
  from ref 128111 z 2001 stereotype "<<map>>" xyz 202 73.5 3000 to ref 128239
  role_a_pos 205 51 3000 no_role_b
  multiplicity_a_pos 289 80 3000 no_multiplicity_b
end
relationcanvas 129007 relation_ref 190959 // <generalisation>
  from ref 128879 z 2013 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129135 relation_ref 191087 // <generalisation>
  from ref 128623 z 2013 to ref 128879
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129391 relation_ref 308591 // <dependency>
  from ref 128111 z 2007 stereotype "<<import>>" xyz 160 193 3000 to ref 128623
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
