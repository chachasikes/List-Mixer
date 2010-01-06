<?php
// $Id$

/**
 * @file
 */

/*
 * Load preset based on its id
 * @param preset_id
 *   an listmixer preset array.
 * @return
 */
function listmixer_preset($preset_id, $reset = FALSE) {
  $presets = listmixer_presets($reset);
  return (isset($presets[$preset_id])) ? $presets[$preset_id] : array();
}

/*
 * Load list of all presets
 * @TODO: Cache needs to be updated when the edit page is loaded
 */
function listmixer_presets($reset = TRUE) {
  static $presets = array();

  // Clear  caches if $reset is TRUE;
  if ($reset) {
    $presets = array();
    cache_clear_all('listmixer:presets', 'cache');
  }
  // Return presets if the array is populated.
  if (!empty($presets)) {
    return $presets;
  }

  // Grab from cache or build the array. To ensure that the Drupal 5 upgrade
  // path works, we also check whether the presets list is an array.
  /*if (($cache = cache_get('listmixer:presets', 'cache')) && is_array($cache->data)) {
    $presets = $cache->data;
  }*/
  else {
    $normal_presets = array();

    $result = db_query('SELECT * FROM {listmixer_preset} ORDER BY preset_name');

    while ($preset = db_fetch_array($result)) {
      $presets[$preset['preset_id']] = $preset;
      $presets[$preset['preset_id']]['behaviors'] = listmixer_behaviors_load(array('preset_id' => $preset['preset_id']));
      $presets[$preset['preset_id']]['interactions'] = listmixer_interactions_load($preset);

      $presets[$preset['preset_id']]['storage'] = LISTMIXER_STORAGE_NORMAL;

      // Collect normal preset names so we can skip defaults and mark overrides accordingly
      $normal_presets[$preset['preset_name']] = $preset['preset_id'];
    }


    // @TODO We are not using this
    
    // Collect default presets and allow modules to modify them before they
    // are cached.
    $default_presets = module_invoke_all('listmixer_default_presets');
    drupal_alter('listmixer_default_presets', $default_presets);

    // Add in default presets if they don't conflict with any normal presets.
    // Mark normal presets that take the same preset namespace as overrides.
    foreach ($default_presets as $preset) {
      if (!empty($preset['preset_name'])) {
        if (!isset($normal_presets[$preset['preset_name']])) {
          $preset['storage'] = LISTMIXER_STORAGE_DEFAULT;
          // Use a string preset identifier
          $preset['preset_id'] = $preset['preset_name'];
          $presets[$preset['preset_name']] = $preset;
        }
        else {
          $preset_id = $normal_presets[$preset['preset_name']];
          $presets[$preset_id]['storage'] = LISTMIXER_STORAGE_OVERRIDE;
        }
      }
    }
    // Set the cache for the complete preset object.
    // cache_set('listmixer:presets', $presets);
  }
  return $presets;
}

/**
 * Load a preset by name.
 *
 * @param preset_name
 *
 * @return
 *   preset array( 'preset_name' => string, 'preset_id' => integer)
 *   empty array if preset_name is an invalid preset
 */
function listmixer_preset_by_name($preset_name) {
  static $presets_by_name = array();
  if (!$presets_by_name &&  $presets = listmixer_presets()) {
    foreach ($presets as $preset) {
      $presets_by_name[$preset['preset_name']] = $preset;
    }
  }
  return (isset($presets_by_name[$preset_name])) ? $presets_by_name[$preset_name] : array();
}

/**
 * Load title for a preset
 */
function listmixer_preset_title_callback($title, $preset = array()) {
  $replacements = array();
  if (!empty($preset)) {
    $replacements['!preset_name'] = $preset['preset_name'];
    $replacements['!preset_id'] = $preset['preset_id'];
  }
 /* if (!empty($action) && !is_array($action)) {
    $replacements['!actionname'] = $action;
  }
  elseif (!empty($action)) {
    $replacements['!action'] = $action['action'];
  }*/
  return t($title, $replacements);
}

/**
 * Main form for presets
 */
function listmixer_ui_preset_form($form_state, $preset = array()) {
  // Clear presets cache
  cache_clear_all('listmixer:presets', 'cache');
  $form = array();

  $form['preset_id'] = array(
    '#type' => 'value',
    '#value' => $preset['preset_id'],
  );

  // Browsers don't submit disabled form values so we've got to put two copies
  // of the name on the form: one for the submit handler and one for the user.
  if ($preset['storage'] === LISTMIXER_STORAGE_DEFAULT) {
    $form['preset_name'] = array(
      '#type' => 'value',
      '#value' => $preset['preset_name'],
    );
    $form['preset_name_display'] = array(
      '#type' => 'textfield',
      '#size' => '64',
      '#title' => t('Preset Namespace'),
      '#default_value' => $preset['preset_name'],
      '#disabled' => TRUE,
    );
  }
  else {
    $form['preset_name'] = array(
      '#type' => 'textfield',
      '#size' => '64',
      '#title' => t('Preset Namespace'),
      '#default_value' => $preset['preset_name'],
      '#description' => t('This is the machine name of the preset, used by Drupal. Please only use alphanumeric characters, underscores (_), and hyphens (-) for preset names.'),
      '#validate' => array('listmixer_element_preset_name_validate' => array()),
      '#weight' => 1,
    );
  }
  $form['preset_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Preset Description'),
    '#default_value' => $preset['preset_description'],
    '#description' => t('Provide a description of this interaction preset.'),
    '#rows' => 3,
    '#weight' => 2,
  );
  $form['preset_method'] = array(
    '#type' => 'select',
    '#title' => t('Select the type of storage method for this interaction'),
    '#default_value' => $preset['preset_method'],
    '#options' => listmixer_listmixer_storage_register_load(),
    '#description' => t('Choose the method of how list data should be stored. (Currently just \'Nodes\', which must be enabled.)'),
    '#weight' => 3,
  );
   $form['preset_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => $preset['preset_enabled'] ? $preset['preset_enabled'] : 1,
    '#description' => t('Uncheck box to disable this preset'),
    '#weight' => 4,
  ); 
  if (!empty($preset['preset_id'])) {
    // Add interactions form.
    $form = listmixer_interactions_form($form, $form_state, $preset); 
    // Add behaviors form.
    $form = listmixer_behaviors_form($form, $form_state, $preset);
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $preset['storage'] === LISTMIXER_STORAGE_DEFAULT ? t('Override Defaults') : t('Save Preset'),
    '#weight' => 9,
  );

  // For new presets don't show the preview or all actions to be added.
  if (empty($preset['preset_id'])) {
    return $form;
  }

  return $form;
}

function listmixer_ui_preset_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  // Check for duplicates
  foreach (listmixer_presets() as $preset) {
    if ($values['preset_name'] == $preset['preset_name'] && $values['preset_id'] != $preset['preset_id']) {
      form_set_error('preset_name', t('The preset name you have chosen is already in use.'));
      break;
    }
  }

  // Check for illegal characters in preset names
  if (preg_match('/[^0-9a-zA-Z_\-]/', $values['preset_name'])) {
    form_set_error('preset_name', t('Please only use alphanumeric characters, underscores (_), and hyphens (-) for preset names.'));
  }
}

function listmixer_ui_preset_form_submit($form, &$form_state) {
  // Save the preset first to retrieve the preset_id when overriding
  $preset = listmixer_preset_save($form_state['values']);
  // Save Behaviors
  if (isset($form_state['values']['behaviors'])) {
      listmixer_behavior_save($form, &$form_state);
  }
  // Save Interactions
  if (isset($form_state['values']['interactions'])) {
      listmixer_interactions_save($form, &$form_state);
  } 


  // Push back to the preset form
  $form_state['redirect'] = 'admin/build/listmixer/'. $preset['preset_id'];
}

function listmixer_ui_preset_delete_form($form_state, $preset = array()) {

  if (empty($preset)) {
    drupal_set_message(t('The specified preset was not found'), 'error');
    drupal_goto('admin/build/listmixer');
  }

  $form = array();
  $form['preset_id'] = array('#type' => 'value', '#value' => $preset['preset_id']);
  return confirm_form(
    $form,
    t('Are you sure you want to delete the preset %preset?',
      array('%preset' => $preset['preset_name'])
    ),
    'admin/build/listmixer',
    t('This action cannot be undone.'),
    t('Delete'),  t('Cancel')
  ); 
}

function listmixer_ui_preset_delete_form_submit($form, &$form_state) {
  $preset = listmixer_preset($form_state['values']['preset_id']);
  listmixer_preset_delete($preset);
  drupal_set_message(t('Preset %name (ID: @id) was deleted.', array('%name' => $preset['preset_name'], '@id' => $preset['preset_id'])));
  $form_state['redirect'] = 'admin/build/listmixer';
}

/**
 * listmixer preset export form.
 */
function listmixer_ui_preset_export_form(&$form_state, $preset = array()) {
  if (empty($preset)) {
    drupal_set_message(t('The specified preset was not found'), 'error');
    $form_state['redirect'] = 'admin/build/listmixer';
  }

  $preset = listmixer_presets(TRUE);

  $exported = '$presets = array();';
  $exported .= "\n";
  $exported .= '$presets[\''. $preset['preset_name'] .'\'] = ';
  
  $exported .= var_export($preset, TRUE) .';';
  $rows = substr_count($exported, "\n") + 1;

  $form = array();
  $form['export'] = array(
    '#type' => 'textarea',
    '#default_value' => $exported,
    '#rows' => $rows,
    '#resizable' => FALSE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Done'),
    '#weight' => 9,
  );
  $form_state['redirect'] = 'admin/build/listmixer';
  return $form;
}

/**
 *
 */
function listmixer_ui_preset_export_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/listmixer';
}

/**
 * Import preset by cutting and pasting preset array (1 at a time)
 */
 
/**
 * Use hook that creates a preset (stored in a module)
 * hook_listmixer_preset_default
 */

/**
 * Override default preset
 */


/**
 * Save an listmixer preset.
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   a preset array.  In the case of a new preset, 'preset_id' will be populated.
 */
function listmixer_preset_save($preset) {
  if (isset($preset['preset_id']) && is_numeric($preset['preset_id'])) {
    drupal_write_record('listmixer_preset', $preset, 'preset_id');
  }
  else {
    drupal_write_record('listmixer_preset', $preset);
  }

  // Reset presets cache.
  listmixer_presets(TRUE);

  // Rebuild Theme Registry
  drupal_rebuild_theme_registry();
  
  // User feedback
  drupal_set_message('List Mixer preset saved', 'status');
  return $preset;
}

/**
 * Delete a listmixer preset.
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   boolean
 */
function listmixer_preset_delete($preset) {
  db_query('DELETE FROM {listmixer_preset} where preset_id = %d', $preset['preset_id']);
  
  listmixer_behavior_delete($preset);
  listmixer_interactions_delete($preset);
  
  listmixer_presets(TRUE);
  return TRUE;
}