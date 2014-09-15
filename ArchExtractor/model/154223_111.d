format 74

classcanvas 130927 class_ref 156783 // StkFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 276 285.5 2000
end
classcanvas 131183 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 190.5 35.5 2000
end
classcanvas 131311 class_ref 128751 // BaseFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 59.5 239.5 2024
end
classcanvas 131439 class_ref 143599 // os
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 342.5 185.5 2000
end
relationcanvas 131567 relation_ref 159087 // <generalisation>
  decenter_end 544
  from ref 130927 z 2025 to ref 131311
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131695 relation_ref 159471 // <dependency>
  from ref 130927 z 2001 stereotype "<<import>>" xyz 253 147 3000 to ref 131183
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131823 relation_ref 159343 // <dependency>
  from ref 130927 z 2001 stereotype "<<import>>" xyz 352 253 3000 to ref 131439
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 132079 relation_ref 158063 // <dependency>
  from ref 131311 z 2025 stereotype "<<import>>" xyz 107 141 3000 to ref 131183
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
