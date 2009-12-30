<?php
// $Id$

/**
 * @file
 * Implementation of hook_views_default_views().
 */
function drag_list_select_views_default_views() {
  module_load_include('inc', 'drag_list_select', 'drag_list_select.features.views');
  $args = func_get_args();
  return call_user_func_array('_drag_list_select_views_default_views', $args);
}
