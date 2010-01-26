<?php
// $Id$

/**
 * @file
 */

/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_ui_behaviors_form(&$form, &$form_state, $preset = array()) {
  // Get the currently selected behavior from the database.
  $preset_behaviors = array();
  $preset['behaviors'] = listmixer_behaviors_load($preset);
  $form['behaviors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Behaviors'),
    '#tree' => TRUE,
    '#weight' => 7,
  );
  listmixer_ui_behaviors_form_elements(&$form, $preset);
  return $form;
}

function listmixer_ui_behaviors_form_elements(&$form, $preset) {
  $behavior_types = listmixer_behaviors_types();
  foreach ($behavior_types['types'] as $behavior_type_setting) {
    $title = $behavior_type_setting['#title'];
    $type = $behavior_type_setting['type'];
    $description = $behavior_type_setting['#description'];

    $behavior_name = $preset['behaviors'][$type]['behavior_name'];
    $id = $preset['behaviors'][$type]['id'];
    $element = array();
    $element = array(
    '#type' => 'select',
    '#title' => $title,
    '#default_value' => $behavior_name,
    '#options' => listmixer_ui_behaviors_load_form_options($preset, $type),
    '#description' => $description,
    '#id' => $type . '-' . $id 
              . ' interaction-preset-id-' . $preset['preset_id']
              . ' ' . $type . '-name-' . $behavior_name,
    'id' => array('#value' => $id),
    'behavior_name' => array('#value' => $behavior_name),
  );
  $form['behaviors'][$type] = $element;
  }
}

/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_ui_behaviors_load_form_options($preset = NULL, $type) {
  // Load behaviors from the behavior registry table
  $behaviors = listmixer_behavior_registry_load();
 
  // Add behavior information into array
  // @TODO Maybe this should never be allowed to be null
  // $behaviors_options = array('none' => '--None--');
  $behaviors_options = array();
  foreach ($behaviors as $behavior) {
    if ($type == $behavior['behavior_type']) {
      $behaviors_options[$behavior['behavior_name']] = $behavior['behavior_label'];
    }
  }
  return $behaviors_options;
}

/**
 * Save each type of behavior to the database.
 */
function listmixer_behavior_save($form, $form_state) {
  // Allow one type of behavior per behavior preset.
  // Copy $form_state.
  $form_state_store = $form_state['values']['behaviors'];
  // Format behavior for database.
  // Set the id. @TODO Not working well.
  $id = $form_state_store['id'];
  // Set the id from the main preset.
  $preset_id = $form_state['values']['preset_id'];
  $behavior_types = listmixer_behaviors_types();
  foreach ($behavior_types['types'] as $behavior_type_setting) {
    $type = $behavior_type_setting['type'];
   // Store data.
    $form_store = array(
      'id' => $form['behaviors'][$type]['id']['#value'],
      'preset_id' => $preset_id,
      'behavior_name' => $form_state['values']['behaviors'][$type],
      'behavior_type' => $type,
    );
    if (!empty($form['behaviors'][$type]['#default_value'])) {
      // Skip saving id field, just save behaviors
      drupal_write_record('listmixer_behaviors', $form_store, array('id'));
    }
    else {
      drupal_write_record('listmixer_behaviors', $form_store);
    }
  }
}

/**
 * Delete preset behaviors from the database.
 */
function listmixer_ui_behavior_delete($preset) {
  db_query('DELETE FROM {listmixer_behaviors} where preset_id = %d', $preset['preset_id']);
  return TRUE;
}