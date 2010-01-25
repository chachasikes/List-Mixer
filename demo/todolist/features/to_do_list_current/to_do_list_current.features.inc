<?php

/**
 * Implementation of hook_views_default_views().
 */
function to_do_list_current_views_default_views() {
  module_load_include('inc', 'to_do_list_current', 'to_do_list_current.features.views');
  $args = func_get_args();
  return call_user_func_array('_to_do_list_current_views_default_views', $args);
}
