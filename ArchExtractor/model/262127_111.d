format 74

classcanvas 128111 class_ref 128111 // BaseAnalyzer
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 172 268 2000
end
classcanvas 128239 class_ref 129519 // IAnalyzer
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 361 117 2006
end
classcanvas 128495 class_ref 258543 // FactoryProvider
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 555.5 98.5 2000
end
classcanvas 129135 class_ref 143599 // os
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 30 284 2006
end
classcanvas 129647 class_ref 128751 // BaseFileParser
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 757 244 3011
end
relationcanvas 128367 relation_ref 128623 // <realization>
  from ref 128111 z 2007 to ref 128239
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128623 relation_ref 275951 // <unidirectional association>
  from ref 128495 z 2001 to point 525 110
  line 128751 z 2001 to point 525 140
  line 128879 z 2001 to ref 128495
  role_a_pos 475 123 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129007 relation_ref 276079 // <generalisation>
  from ref 128111 z 2001 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129263 relation_ref 151151 // <dependency>
  from ref 128111 z 2007 stereotype "<<import>>" xyz 80.5 312 2007 to ref 129135
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129903 relation_ref 276463 // <generalisation>
  from ref 129647 z 3012 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130415 relation_ref 343407 // <directional composition>
  from ref 128111 z 3012 stereotype "<<list>>" xyz 663 311.5 3000 to ref 129647
  role_a_pos 631 291 3000 no_role_b
  multiplicity_a_pos 741 320 3000 no_multiplicity_b
end
end
