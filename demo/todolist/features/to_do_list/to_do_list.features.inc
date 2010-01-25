<?php

/**
 * Implementation of hook_content_default_fields().
 */
function to_do_list_content_default_fields() {
  module_load_include('inc', 'to_do_list', 'to_do_list.defaults');
  $args = func_get_args();
  return call_user_func_array('_to_do_list_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function to_do_list_node_info() {
  module_load_include('inc', 'to_do_list', 'to_do_list.features.node');
  $args = func_get_args();
  return call_user_func_array('_to_do_list_node_info', $args);
}
