<?php

/**
 * Implementation of hook_content_default_fields().
 */
function favorite_links_content_default_fields() {
  module_load_include('inc', 'favorite_links', 'favorite_links.defaults');
  $args = func_get_args();
  return call_user_func_array('_favorite_links_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function favorite_links_node_info() {
  module_load_include('inc', 'favorite_links', 'favorite_links.features.node');
  $args = func_get_args();
  return call_user_func_array('_favorite_links_node_info', $args);
}
