<?php
// $Id$

/**
 * @file
 */

/**
 * Implementation of hook_content_default_fields().
 */
function babble_stream_content_default_fields() {
  module_load_include('inc', 'babble_stream', 'babble_stream.defaults');
  $args = func_get_args();
  return call_user_func_array('_babble_stream_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function babble_stream_node_info() {
  module_load_include('inc', 'babble_stream', 'babble_stream.features.node');
  $args = func_get_args();
  return call_user_func_array('_babble_stream_node_info', $args);
}
