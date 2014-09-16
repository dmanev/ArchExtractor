format 74

classcanvas 128111 class_ref 156655 // re
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 58 229.5 2000
end
classcanvas 128623 class_ref 163695 // ProvidedPort
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 298 335 2000
end
classcanvas 128879 class_ref 218351 // StkPortCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 428.5 21.5 3005
end
classcanvas 130031 class_ref 238191 // StkCHeaderProvDATControlCriteria
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 201 231 2000
end
classcanvas 130287 class_ref 238063 // StkDATControlIf
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 560 335 2000
end
relationcanvas 129263 relation_ref 227951 // <dependency>
  from ref 128879 z 3006 stereotype "<<import>>" xyz 221 171.5 3006 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130159 relation_ref 251759 // <generalisation>
  decenter_begin 497
  from ref 130031 z 3006 to ref 128879
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130415 relation_ref 251887 // <dependency>
  from ref 130031 z 2001 stereotype "<<import>>" xyz 522 308.5 3000 to ref 130287
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130543 relation_ref 252015 // <dependency>
  decenter_begin 365
  from ref 130031 z 2001 stereotype "<<import>>" xyz 365 308.5 3000 to ref 128623
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130927 relation_ref 252143 // <dependency>
  from ref 130031 z 2001 stereotype "<<import>>" xyz 108 256.5 3000 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
