<?php

/**
 * Implementation of hook_views_default_views().
 */
function photo_gallery_sortable_views_default_views() {
  module_load_include('inc', 'photo_gallery_sortable', 'photo_gallery_sortable.features.views');
  $args = func_get_args();
  return call_user_func_array('_photo_gallery_sortable_views_default_views', $args);
}
