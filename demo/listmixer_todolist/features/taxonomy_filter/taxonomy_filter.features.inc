<?php

/**
 * Implementation of hook_node_info().
 */
function taxonomy_filter_node_info() {
  module_load_include('inc', 'taxonomy_filter', 'taxonomy_filter.features.node');
  $args = func_get_args();
  return call_user_func_array('_taxonomy_filter_node_info', $args);
}
