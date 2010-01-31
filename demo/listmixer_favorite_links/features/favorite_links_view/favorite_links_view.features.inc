<?php

/**
 * Implementation of hook_views_default_views().
 */
function favorite_links_view_views_default_views() {
  module_load_include('inc', 'favorite_links_view', 'favorite_links_view.features.views');
  $args = func_get_args();
  return call_user_func_array('_favorite_links_view_views_default_views', $args);
}
