<?php

/**
 * Implementation of hook_views_default_views().
 */
function photoset_shuffler_views_default_views() {
  module_load_include('inc', 'photoset_shuffler', 'photoset_shuffler.features.views');
  $args = func_get_args();
  return call_user_func_array('_photoset_shuffler_views_default_views', $args);
}
