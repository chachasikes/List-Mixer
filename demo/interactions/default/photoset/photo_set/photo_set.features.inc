<?php
// $Id$

/**
 * @file
 */

/**
 * Implementation of hook_content_default_fields().
 */
function photo_set_content_default_fields() {
  module_load_include('inc', 'photo_set', 'photo_set.defaults');
  $args = func_get_args();
  return call_user_func_array('_photo_set_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function photo_set_node_info() {
  module_load_include('inc', 'photo_set', 'photo_set.features.node');
  $args = func_get_args();
  return call_user_func_array('_photo_set_node_info', $args);
}
