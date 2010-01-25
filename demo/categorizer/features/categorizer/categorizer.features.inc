<?php

/**
 * Implementation of hook_views_default_views().
 */
function categorizer_views_default_views() {
  module_load_include('inc', 'categorizer', 'categorizer.features.views');
  $args = func_get_args();
  return call_user_func_array('_categorizer_views_default_views', $args);
}
