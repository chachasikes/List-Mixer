<?php
// $Id$

/**
 * @file listmixer_ui.behaviors.inc
 * Much of this module was based on the structure for creating presets in listmixer
 */
 
/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_behaviors_form(&$form, &$form_state, $preset = array()) {
  $preset_behaviors = array();
  $preset_behaviors['activate'] = listmixer_behaviors_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'activate'));
  $preset_behaviors['interact'] = listmixer_behaviors_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'interact'));
  $preset_behaviors['push'] =  listmixer_behaviors_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'push'));
  $preset_behaviors['submit'] =  listmixer_behaviors_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'submit'));
  $form['behaviors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Behaviors'),
    '#tree' => TRUE,
    '#weight' => 7,
  );
 $form['behaviors']['activate'] = array(
    '#type' => 'select',
    '#title' => t('Activate'),
    '#default_value' => $preset_behaviors['activate']['activate']['behavior_name'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'activate'),
    '#description' => t('Choose activate behaviors.'),
    '#id'=> 'activate-' . $preset_behaviors['activate']['activate']['id'] 
            . ' interaction-preset-id-' . $preset['preset_id'] . ' activate-name-' . $preset_behaviors['activate']['activate']['behavior_name'],
    'id' => array('#value' => $preset_behaviors['activate']['activate']['id']),
    'behavior_name' => array('#value' => $preset_behaviors['activate']['activate']['behavior_name']),
  );
  $form['behaviors']['push'] = array(
    '#type' => 'select',
    '#title' => t('Push'),
    '#default_value' => $preset_behaviors['push']['push']['behavior_name'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'push'),
    '#description' => t('Choose push behaviors.'),
    '#id'=> 'push-' . $preset_behaviors['push']['push']['id'] 
            . ' interaction-preset-id-' . $preset['preset_id'] . ' push-name-' . $preset_behaviors['push']['push']['behavior_name'],
    'id' => array('#value' => $preset_behaviors['push']['push']['id']),
    'behavior_name' => array('#value' => $preset_behaviors['push']['push']['behavior_name']),
  );
  $form['behaviors']['interact'] = array(
    '#type' => 'select',
    '#title' => t('Interact'),
    '#default_value' => $preset_behaviors['interact']['interact']['behavior_name'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'interact'),
    '#description' => t('Choose interact behaviors.'),
    '#id'=> 'interact-' . $preset_behaviors['interact']['interact']['id'] 
            . ' interaction-preset-id-' . $preset['preset_id'] . ' interact-name-' . $preset_behaviors['interact']['interact']['behavior_name'],
    'id' => array('#value' => $preset_behaviors['interact']['interact']['id']),
    'behavior_name' => array('#value' => $preset_behaviors['interact']['interact']['behavior_name']),
  );
  $form['behaviors']['submit'] = array(
    '#type' => 'select',
    '#title' => t('Submit'),
    '#default_value' => $preset_behaviors['submit']['submit']['behavior_name'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'submit'),
    '#description' => t('Choose submit behaviors.'),
    '#id'=> 'submit-' . $preset_behaviors['submit']['submit']['id'] 
            . ' submition-preset-id-' . $preset['preset_id'] . ' submit-name-' . $preset_behaviors['submit']['submit']['behavior_name'],
    'id' => array('#value' => $preset_behaviors['submit']['submit']['id']),
    'behavior_name' => array('#value' => $preset_behaviors['submit']['submit']['behavior_name']),
  );
  return $form;
} 
/**
 * Load a behavior or set of behaviors
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   a preset array.  In the case of a new preset, 'preset_id' will be populated.
 */
function listmixer_behaviors_load($behavior_key = array()) {
 
  if(!empty($behavior_key['id'])) {
    $behaviors = array();
    $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE id = %d", $behavior_key['id']);
    while ($row = db_fetch_array($result)) {
      $behaviors[$row['behavior_type']] = $row;
    }
  }
  elseif(!empty($behavior_key['preset_id']) && empty($behavior_key['behavior_type'])) {
    $behaviors = array();
    $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE preset_id = %d", $behavior_key['preset_id']);
    while ($row = db_fetch_array($result)) {
      $behaviors[$row['behavior_type']] = $row;
    }
  }
  elseif(!empty($behavior_key['preset_id']) && !empty($behavior_key['behavior_type'])) {
    $behaviors = array();
    $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE preset_id = %d AND behavior_type = '%s'",  $behavior_key['preset_id'], $behavior_key['behavior_type']);
    while ($row = db_fetch_array($result)) {
      $behaviors[$row['behavior_type']] = $row;
    }  
  }
  // Add settings for each behavior
  foreach ($behaviors as &$behavior) {
    $behavior['settings'] = listmixer_behavior_registry_load($behavior['behavior_name']);
  }
  return $behaviors;
}

/**
 * Save an listmixer preset.
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   a preset array.  In the case of a new preset, 'preset_id' will be populated.
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

  // Store activate button.
  $form_store = array(
    'id' => $form['behaviors']['activate']['id']['#value'],
    'preset_id' => $preset_id,
    'behavior_name' => $form_state['values']['behaviors']['activate'],
    'behavior_type' => 'activate',
  );
  if (!empty($form['behaviors']['activate']['#default_value'])) {
    // Skip saving id field, just save behaviors
    drupal_write_record('listmixer_behaviors', $form_store, array('id'));
  }
  else {
   drupal_write_record('listmixer_behaviors', $form_store);
  }
  
  // Store interact button.
  $form_store = array(
    'id' => $form['behaviors']['interact']['id']['#value'],
    'preset_id' => $preset_id,
    'behavior_name' => $form_state['values']['behaviors']['interact'],
    'behavior_type' => 'interact',
  );
  if (!empty($form['behaviors']['interact']['#default_value'])) {
    // Skip saving id field, just save behaviors
    drupal_write_record('listmixer_behaviors', $form_store, array('id'));
  }
  else {
   drupal_write_record('listmixer_behaviors', $form_store);
  }
    
  // Store push button.
  $form_store = array(
    'id' => $form['behaviors']['push']['id']['#value'],
    'preset_id' => $preset_id,
    'behavior_name' => $form_state['values']['behaviors']['push'],
    'behavior_type' => 'push',
  );
  if (!empty($form['behaviors']['push']['#default_value'])) {
    // Skip saving id field, just save behaviors
    drupal_write_record('listmixer_behaviors', $form_store, array('id'));
  }
  else {
   drupal_write_record('listmixer_behaviors', $form_store);
  }
  
  // Store submit button.
  $form_store = array(
    'id' => $form['behaviors']['submit']['id']['#value'],
    'preset_id' => $preset_id,
    'behavior_name' => $form_state['values']['behaviors']['submit'],
    'behavior_type' => 'submit',
  );
  if (!empty($form['behaviors']['submit']['#default_value'])) {
    // Skip saving id field, just save behaviors
    drupal_write_record('listmixer_behaviors', $form_store, array('id'));
  }
  else {
   drupal_write_record('listmixer_behaviors', $form_store);
  }
}
 
function listmixer_behavior_delete($preset) {
  db_query('DELETE FROM {listmixer_behaviors} where preset_id = %d', $preset['preset_id']);
  return TRUE;
} 
 
/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_behaviors_load_form_options($preset = NULL, $type) {
  // Load behaviors from the behavior registry table
  $behaviors = listmixer_behavior_registry_load();
  
  // Add behavior information into array
  // Add 'none' value
  // @TODO Should this be NULL, check db structure
  $behaviors_options = array('none' => '--None--');  
  foreach ($behaviors as $behavior) {
    if($type == $behavior['behavior_type']) {
      $behaviors_options[$behavior['behavior_name']] =  $behavior['behavior_label'];
    }
  }
  return $behaviors_options;
}

/**
 * Load registered behaviors
 */
function listmixer_behavior_registry_load($name = NULL) {
  // Load and deserialize behavior registry
  $behaviors = unserialize(variable_get('listmixer_behavior_registry', array('listmixer')));
  if(!empty($name)) {
    foreach($behaviors as $key => $behavior) {
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
 */ 
function listmixer_behaviors_registry_form($form_state, $behavior = array(), $op = NULL) {
  $enabled = TRUE;
  $listmixer_behaviors_registry = listmixer_behaviors_registry_build(); 

  if(function_exists('dpm')){
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
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Button', $enabled, '', 'button', 'activate_button', 'Activate Button', 'Activate.buttonActivate');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'MouseDown', $enabled, '', 'mousedown', 'activate_mousedown', 'Activate Mousedown', 'Activate.mouseDownActivate');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('activate', 'Drag', $enabled, '', 'drag', 'activate_drag', 'Activate Drag description', 'Activate.dragActivate');

  /* INTERACT functions */    
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Click Links', $enabled, '', 'click', 'interact_click', 'Click interaction', 'Interact.clickInteract');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Checkbox', $enabled, '', 'checkbox', 'interact_checkbox', 'Checkbox interaction', 'Interact.checkboxInteract');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Input', $enabled, '', 'input', 'interact_input', 'Input interaction', 'Interact.inputInteract');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('interact', 'Select', $enabled, '', 'select', 'interact_select', 'Select interaction', 'Select.selectInteract');

  /* PUSH functions */
  /* Content push functions */
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store File', $enabled, '/content', 'filefield', 'push_filefield', 'Store File', 'Push.filefieldPush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Link', $enabled, '/content', 'link', 'push_link', 'Store Link', 'Push.linkPush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Nodereference', $enabled, 'push/content', 'nodereference', 'push_nodereference', 'Store Nodereference', 'Push.nodereferencePush');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Text', $enabled, '/content', 'text', 'push_text', 'Store Text', 'Push.textPush'); 
  /* Taxonomy push functions */
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('push', 'Store Term', $enabled, '/taxonomy', 'term', 'push_taxonomy_term', 'Push Taxonomy Term', 'Push.termPush');
  
  /* SUBMIT functions */
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('submit', 'Submit Button', $enabled, '', 'button', 'submit_button', 'Submit Button', 'Submit.buttonSubmit');
  $listmixer_behaviors_registry[] = listmixer_behaviors_registry_build_behavior('submit', 'Submit Checkbox', $enabled, '', 'checkbox', 'submit_checkbox', 'Submit Checkbox', 'Submit.checkboxSubmit');

  // Reset preset cache.
  $presets = listmixer_presets(TRUE);
  
  return $listmixer_behaviors_registry;
}