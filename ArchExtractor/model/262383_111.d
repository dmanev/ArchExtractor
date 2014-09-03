format 74

classcanvas 128111 class_ref 128751 // BaseFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 298 262 2000
end
classcanvas 128239 class_ref 130159 // IFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 294 40 2006
end
classcanvas 128495 class_ref 258543 // FactoryProvider
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 575.5 132.5 2010
end
classcanvas 129135 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 122 148 2006
end
relationcanvas 128367 relation_ref 129263 // <realization>
  from ref 128111 z 2007 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128623 relation_ref 275951 // <unidirectional association>
  from ref 128495 z 2011 to point 545 132
  line 128751 z 2011 to point 545 162
  line 128879 z 2011 to ref 128495
  role_a_pos 495 152 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129007 relation_ref 276463 // <generalisation>
  from ref 128111 z 2011 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129263 relation_ref 158063 // <dependency>
  from ref 128111 z 2007 stereotype "<<import>>" xyz 210 214 2007 to ref 129135
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
