format 74

classcanvas 128111 class_ref 128751 // BaseFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 176 252 2000
end
classcanvas 128239 class_ref 130159 // IFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 429 40 2006
end
classcanvas 128495 class_ref 258543 // FactoryProvider
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 783.5 48.5 2010
end
classcanvas 129135 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 45 310 2006
end
classcanvas 129647 class_ref 185327 // BasePortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 1012 318 2016
end
relationcanvas 128367 relation_ref 129263 // <realization>
  from ref 128111 z 2007 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128623 relation_ref 275951 // <unidirectional association>
  from ref 128495 z 2011 to point 753 37
  line 128751 z 2011 to point 753 67
  line 128879 z 2011 to ref 128495
  role_a_pos 678 46 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129007 relation_ref 276463 // <generalisation>
  from ref 128111 z 2011 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129263 relation_ref 158063 // <dependency>
  from ref 128111 z 2007 stereotype "<<import>>" xyz 110.5 318.5 2007 to ref 129135
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129903 relation_ref 276335 // <generalisation>
  from ref 129647 z 2017 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130031 relation_ref 343535 // <directional composition>
  from ref 128111 z 2017 stereotype "<<list>>" xyz 899 338 3000 to ref 129647
  role_a_pos 880 317 3000 no_role_b
  multiplicity_a_pos 996 346 3000 no_multiplicity_b
end
end
