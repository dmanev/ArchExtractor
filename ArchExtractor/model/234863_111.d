format 74

classcanvas 128111 class_ref 128751 // BaseFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 123.5 264 2024
end
classcanvas 128367 class_ref 129519 // IAnalyzer
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 364.5 463 2000
end
classcanvas 128495 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 256.5 41 2000
end
classcanvas 128623 class_ref 150127 // StkJilFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 583.5 318 2000
end
classcanvas 129647 class_ref 156783 // StkFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 342 291 2000
end
classcanvas 130799 class_ref 128239 // BaseComponent
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 124 486 2000
end
relationcanvas 128879 relation_ref 158703 // <dependency>
  decenter_end 157
  from ref 128623 z 2001 stereotype "<<import>>" xyz 447 174 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129263 relation_ref 158063 // <dependency>
  from ref 128111 z 2025 stereotype "<<import>>" xyz 169 196 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129775 relation_ref 159087 // <generalisation>
  decenter_end 544
  from ref 129647 z 2025 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129903 relation_ref 159215 // <generalisation>
  from ref 128623 z 2001 to ref 129647
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130543 relation_ref 159471 // <dependency>
  from ref 129647 z 2001 stereotype "<<import>>" xyz 300 187 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131055 relation_ref 243951 // <dependency>
  from ref 129647 z 2001 stereotype "<<import>>" xyz 264 457 3000 to ref 130799
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
