<?php
// $Id$

/**
 * @file listmixer_ui.interactions.inc
 * 
 */
 

/**
 *
 */
function listmixer_interactions_form(&$form) {
  // Based on the type of interaction $preset['preset_method'] load data from the table to be used with the interaction form.  
  $form['interaction'] = array(
    '#type' => 'fieldset',
    '#title' => t('Interaction'),
    '#tree' => TRUE,
    '#weight' => 8,
   // '#theme' => 'listmixer_ui_preset_interaction',
  );
  
  // The preset method is stored as the module name for the storage method.
  if(!empty($form['preset_method']['#default_value'])) {
    $form_load_function = $form['preset_method']['#default_value'] . '_load_interaction_form';
    if(function_exists($form_load_function)) {
      $form['interaction'][] = call_user_func($form_load_function, $form);
    }
  }

  return $form;
}

/**
 * Save an listmixer preset.
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   a preset array.  In the case of a new preset, 'preset_id' will be populated.
 */
function listmixer_interactions_save($preset_id, $behavior_name, $behavior_id, $behavior = array()) {
  if(empty($behavior)) {
    // Get behavior data
    $behavior = listmixer_behavior_registry_load($behavior_name);
    // Add preset id to behavior
    $behavior['preset_id'] = $preset_id;
  }
  // If an id already exists
  if (!empty($behavior['id'])) {
  dpm(' in update');
    drupal_write_record('listmixer_behaviors', $behavior, array('preset_id', 'behavior_type'));
  }
  else {
  dpm('not in update');
    drupal_write_record('listmixer_behaviors', $behavior);
  }
  return $behavior;
}