<?php
// $Id$

/**
 * @file
 */

/**
 * Call form save function from module
 */
function listmixer_interactions_load($preset) {
  $interactions = array();
  // The preset method is stored as the module name for the storage method.
  if (!empty($preset['preset_method'])) {
    $form_load_function = $preset['preset_method'] . '_listmixer_storage_load';
    if (function_exists($form_load_function)) {
      $interactions = call_user_func($form_load_function, $preset);
    }
  }
  return $interactions;
}