<?php
// $Id$

/**
 * @file
 */

/**
 * Implementation of hook_content_default_fields().
 */
function photo_content_default_fields() {
  module_load_include('inc', 'photo', 'photo.defaults');
  $args = func_get_args();
  return call_user_func_array('_photo_content_default_fields', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function photo_imagecache_default_presets() {
  module_load_include('inc', 'photo', 'photo.defaults');
  $args = func_get_args();
  return call_user_func_array('_photo_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_node_info().
 */
function photo_node_info() {
  module_load_include('inc', 'photo', 'photo.features.node');
  $args = func_get_args();
  return call_user_func_array('_photo_node_info', $args);
}
