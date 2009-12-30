<?php
// $Id$

/**
 * @file
 * Implementation of hook_content_default_fields().
 */
function drag_list_content_default_fields() {
  module_load_include('inc', 'drag_list', 'drag_list.defaults');
  $args = func_get_args();
  return call_user_func_array('_drag_list_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function drag_list_node_info() {
  module_load_include('inc', 'drag_list', 'drag_list.features.node');
  $args = func_get_args();
  return call_user_func_array('_drag_list_node_info', $args);
}
