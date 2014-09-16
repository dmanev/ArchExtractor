format 74

classcanvas 128111 class_ref 163823 // IPortInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 406 28 2000
end
classcanvas 128239 class_ref 258287 // PortInterfaceFactory
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 76 234 2000
end
classcanvas 128495 class_ref 164079 // SenderReceiverInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 666 97 2006
end
classcanvas 128751 class_ref 163951 // ClientServerInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 76 106 2006
end
relationcanvas 128367 relation_ref 274927 // <directional aggregation>
  from ref 128239 z 2001 stereotype "<<map>>" xyz 395.5 171 3000 to ref 128111
  role_a_pos 459 92 3000 no_role_b
  multiplicity_a_pos 434 92 3000 no_multiplicity_b
end
relationcanvas 128623 relation_ref 167151 // <generalisation>
  from ref 128495 z 2007 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128879 relation_ref 167023 // <generalisation>
  decenter_begin 496
  from ref 128751 z 2007 to ref 128111
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129007 relation_ref 275055 // <dependency>
  from ref 128239 z 2007 stereotype "<<import>>" xyz 611.5 193.5 3000 to ref 128495
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129263 relation_ref 275183 // <dependency>
  from ref 128239 z 2007 stereotype "<<import>>" xyz 214.5 192 3000 to ref 128751
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
