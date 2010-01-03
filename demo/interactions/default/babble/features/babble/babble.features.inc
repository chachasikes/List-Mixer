<?php
// $Id$

/**
 * @file
 */
 
/**
 * Implementation of hook_views_default_views().
 */
function babble_views_default_views() {
  module_load_include('inc', 'babble', 'babble.features.views');
  $args = func_get_args();
  return call_user_func_array('_babble_views_default_views', $args);
}
