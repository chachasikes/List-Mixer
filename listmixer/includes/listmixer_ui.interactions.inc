<?php
// $Id$

/**
 * @file
 * Interactions are loaded from hooks.
 */


/**
 * Load form from module
 */
function listmixer_ui_interactions_form(&$form, &$form_state, $preset = array()) {
  // Based on the type of interaction $preset['preset_method'] load data from the table to be used with the interaction form.
  $form['interactions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Interactions'),
    '#tree' => TRUE,
    '#weight' => 8,
  );

  // The preset method is stored as the module name for the storage method.
  if (!empty($form['preset_method']['#default_value']) && ($form != NULL)) {
    $form_load_function = $form['preset_method']['#default_value'] . '_load_interactions_form';
    if (function_exists($form_load_function)) {
      $form['interactions'][] = call_user_func($form_load_function, $form, $form_state, $preset);
    }
  }

  return $form;
}

/**
 * Call form save function from module
 */
function listmixer_ui_interactions_save(&$form, $form_state) {
  // The preset method is stored as the module name for the storage method.
  if (!empty($form['preset_method']['#default_value'])) {
    $form_save_function = $form['preset_method']['#default_value'] . '_listmixer_storage_save';
    if (function_exists($form_save_function)) {
      call_user_func($form_save_function, $form, $form_state);
    }
  }
  return $form;
}

function listmixer_ui_interactions_delete($preset) {
  if (!empty($preset['preset_method'])) {
    $form_delete_function = $preset['preset_method'] . '_listmixer_storage_delete';
    if (function_exists($form_delete_function)) {
      call_user_func($form_delete_function, $preset);
    }
  }
  return TRUE;
}
