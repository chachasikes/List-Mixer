<?php

/**
 * Implementation of hook_views_default_views().
 */
function favorite_links_views_default_views() {
  module_load_include('inc', 'favorite_links', 'favorite_links.features.views');
  $args = func_get_args();
  return call_user_func_array('_favorite_links_views_default_views', $args);
}
