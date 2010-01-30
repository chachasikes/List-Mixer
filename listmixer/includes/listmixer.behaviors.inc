<?php
// $Id$

/**
 * @file
 */

/**
 * Load a behavior or set of behaviors
 * This (should?) be based on a bunch of different sets of behavior details.
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   a preset array.  In the case of a new preset, 'preset_id' will be populated.
 */
function listmixer_behaviors_load($preset) {
  $behaviors = array();
  $behavior_types = listmixer_behaviors_types();
  foreach ($behavior_types['types'] as $behavior_type_setting) {
    $behavior_type = $behavior_type_setting['type'];
    $behavior_key = array(
      'preset_id' => $preset['preset_id'],
      'behavior_type' => $behavior_type,
    );
    if (is_numeric($preset['behaviors'][$behavior_type]['id'])) {
      $behavior_key['id'] = $preset['behaviors'][$behavior_type]['id'];
    }
    if (!is_array($preset['behaviors'][$behavior_type])) {
      $behavior_key['behavior_name'] = $preset['behaviors'][$behavior_type];
    }
    else {
      $behavior_key['behavior_name'] = $preset['behaviors'][$behavior_type]['behavior_name'];
    }
    // If an id exists, a behavior is already stored in the database.
    if (!empty($behavior_key['id'])) {
      $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE id = %d", $behavior_key['id']);
      while ($row = db_fetch_array($result)) {
        $behaviors[$row['behavior_type']] = $row;
      }
    }
    // Get all behaviors by preset id.
    elseif (!empty($behavior_key['preset_id']) && empty($behavior_key['behavior_type'])) {
      $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE preset_id = %d", $behavior_key['preset_id']);
      while ($row = db_fetch_array($result)) {
        $behaviors[$row['behavior_type']] = $row;
      }
    }
    // Get a matching record of a behavior by the preset id and behavior type.
    elseif (!empty($behavior_key['preset_id']) && !empty($behavior_key['behavior_type'])) {
      $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE preset_id = %d AND behavior_type = '%s'",  $behavior_key['preset_id'], $behavior_key['behavior_type']);
      while ($row = db_fetch_array($result)) {
        $behaviors[$row['behavior_type']] = $row;
      }
    }
    // If we have the preset name and the type (because preset is loaded from code.)
    // There won't be any database settings, but it would be nice to get the settings by the type.
    elseif (!empty($behavior_key['behavior_name']) && !empty($behavior_key['behavior_type'])) {
      // Load the settings for the type and name of the behavior.
      $behaviors[$behavior_key['behavior_type']] = $behavior_key;
    }
    else {
      // Do nothing. There will not be any behaviors in the database.
    }
  }
  // Add settings for each behavior
  foreach ($behaviors as &$behavior) {
    $behavior['settings'] = listmixer_behavior_registry_load($behavior['behavior_name']);
  }
  return $behaviors;
}

/**
 * Load registered behaviors
 */
function listmixer_behavior_registry_load($name = NULL) {
  // Load behavior registry
  $behaviors = listmixer_behaviors_registry_build();
  // @TODO Figure out the best system for building the registry, if it should be cached or not:
  // an extra db call may be unneccessary.
  // Load and deserialize behavior registry
  // $behaviors = unserialize(variable_get('listmixer_behavior_registry', array()));
  if (!empty($name)) {
    foreach ($behaviors as $key => $behavior) {
      if ($behaviors[$key]['behavior_name'] == $name) {
        $behavior_id = $key;
      }
    }
    return $behaviors[$behavior_id];
  }
  else {
    return $behaviors;
  }
}

/**
 * @TODO
 * For each allowed behavior (admin/settings/listmixer)
 * If module exists, load include for push behavior
 * Create callback for the push behavior
 * Inc adds js for the behavior
 * Javascript contains transformation from data to form
 * Add utlities for behaviors (php,js)
 */


/**
 * Create behavior registry
 * Every new behavior must be added to this array.
 * Behaviors can be disabled on a site by the user, but they must be registered
 * in order to be available.
 *
 * All registry items need to include:
 * *Name - Must be unique
 * *Label
 * *Enabled
 * *Type
 * *Include location
 * *Javascript location
 * *Description
 * *Callback name (data is sent via POST variable)
 *
 * Registry can be updated by clicking the button here: admin/settings/behaviors/update/registry
 */
function listmixer_behaviors_registry_build_behavior($type, $label, $enabled = TRUE, $folder_path, $folder_root, $name, $description, $function) {
  $path = drupal_get_path('module', 'listmixer');
  $element = array(
    'behavior_name' => $name,
    'behavior_label' => t($label),
    'behavior_enabled' => $enabled,
    'behavior_type' => $type,
    'behavior_include' => $path . '/behaviors/' . $type . $folder_path . '/' . $folder_root . '/listmixer_' . $name . '.inc',
    'behavior_function' => $function,
    'behavior_callback' => base_path() . 'admin/ajax/listmixer/behavior/' . $type . '/listmixer_' . $name . '/' . $name,
    'behavior_redirect' => base_path() . 'admin/ajax/listmixer/redirect/' . $type . '/listmixer_' . $name . '/' . $name,
    'behavior_description' => t($description),
  );
  return $element;
}

/**
 * Form for updating the registry
 * @TODO move this from systems to cache system
 * @TODO change order of how registry is updated. include manual button, but also a function.
 * Update: I don't think we'll need this, but will keep the page to see what behaviors are available.
 */
function listmixer_behaviors_registry_form($form_state, $behavior = array(), $op = NULL) {
  $enabled = TRUE;
  $listmixer_behaviors_registry = listmixer_behaviors_registry_build();

  if (function_exists('dpm')) {
    dpm($listmixer_behaviors_registry);
  }

  // Registry stores a serialized array of all of the registry settings.
  $form['listmixer_behavior_registry'] = array(
    '#type' => 'textarea',
    '#title' => t('List Mixer Behavior Registry'),
    '#description' => t('Registered behaviors'),
    '#default_value' => serialize($listmixer_behaviors_registry),
  );

  return system_settings_form($form);
}

/**
 * Build behavior registry array
 */
function listmixer_behaviors_registry_build() {
  $listmixer_behaviors_registry = array();

  /* ACTIVATE functions */
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Load', $enabled, '', 'load', 'activate_load', 'Activate Load', 'loadActivate');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Button', $enabled, '', 'button', 'activate_button', 'Activate Button', 'buttonActivate');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Select', $enabled, '', 'select', 'activate_select', 'Activate Select', 'selectActivate');
  //$listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Radio Button', $enabled, '', 'radio', 'activate_radio', 'Activate Radio', 'radioActivate');
  // $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Drag', $enabled, '', 'drag', 'activate_drag', 'Activate Drag description', 'dragActivate');

  /* INTERACT functions */
  // $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Click Links', $enabled, '', 'click', 'interact_click', 'Click interaction', 'clickInteract');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Input', $enabled, '', 'input', 'interact_input', 'Input interaction', 'inputInteract');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Checkbox', $enabled, '', 'checkbox', 'interact_checkbox', 'Checkbox interaction', 'checkboxInteract');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Sort', $enabled, '', 'sort', 'interact_sort', 'Sort interaction', 'sortInteract');
  // $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Select', $enabled, '', 'select', 'interact_select', 'Select interaction', 'selectInteract');

  /* PUSH functions */
  /* Content push functions */
  // $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store File', $enabled, '/content', 'filefield', 'push_filefield', 'Store File', 'filefieldPush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Nodereference', $enabled, '/content', 'nodereference', 'push_nodereference', 'Store Nodereference', 'nodereferencePush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Text', $enabled, '/content', 'text', 'push_text', 'Store Text', 'textPush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Link', $enabled, '/content', 'link', 'push_link', 'Store Link', 'linkPush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Term', $enabled, '/taxonomy', 'term', 'push_taxonomy_term', 'Store Term', 'termPush');

  /* Taxonomy push functions */
  // $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Term', $enabled, '/taxonomy', 'term', 'push_taxonomy_term', 'Push Taxonomy Term', 'termPush');

  /* SUBMIT functions */
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('submit', 'Submit Button', $enabled, '', 'button', 'submit_button', 'Submit Button', 'buttonSubmit');
  // $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('submit', 'Submit Checkbox', $enabled, '', 'checkbox', 'submit_checkbox', 'Submit Checkbox', 'checkboxSubmit');

  // Reset preset cache.
  // $presets = listmixer_presets(TRUE);

  return $listmixer_behaviors_registry;
}