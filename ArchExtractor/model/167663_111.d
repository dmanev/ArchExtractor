format 74

classcanvas 128239 class_ref 164079 // SenderReceiverInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations no show_members_full_definition yes show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 24 184 2000
end
classcanvas 128495 class_ref 164335 // DataElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 467 184 2006
end
classcanvas 128879 class_ref 163823 // IPortInterface
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 131 41 2006
end
classcanvas 129519 class_ref 258799 // PackageableElement
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 287 51 2012
end
relationcanvas 128623 relation_ref 167663 // <directional composition>
  from ref 128239 z 2007 stereotype "<<list>>" xyz 381 225 2007 to ref 128495
  role_a_pos 354 198 3000 no_role_b
  multiplicity_a_pos 438 227 3000 no_multiplicity_b
end
relationcanvas 129007 relation_ref 167151 // <generalisation>
  from ref 128239 z 2007 to ref 128879
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129903 relation_ref 277615 // <generalisation>
  from ref 128239 z 2013 to ref 129519
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
