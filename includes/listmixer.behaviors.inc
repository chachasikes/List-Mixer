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
  $preset_behaviors['activate'] = listmixer_behavior_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'activate'));
  $preset_behaviors['interact'] = listmixer_behavior_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'interact'));
  $preset_behaviors['push'] =  listmixer_behavior_load(array('preset_id' => $preset['preset_id'], 'behavior_type' =>'push'));

  $form['behaviors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Behaviors'),
    '#tree' => TRUE,
    '#weight' => 9,
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
function listmixer_behavior_load($behavior_key = array()) {
 
  if(!empty($behavior_key['id'])) {
    $behaviors = array();
    $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE id = %d", $behavior_key['id']);
    while ($row = db_fetch_array($result)) {
      $behaviors[$row['id']] = $row;
    }
  }
  elseif(!empty($behavior_key['preset_id']) && empty($behavior_key['behavior_type'])) {
    $behaviors = array();
    $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE preset_id = %d", $behavior_key['preset_id']);
    while ($row = db_fetch_array($result)) {
      $behaviors[$row['id']]= $row;
    }
  }
  elseif(!empty($behavior_key['preset_id']) && !empty($behavior_key['behavior_type'])) {
    $behaviors = array();
    $result = db_query("SELECT * FROM {listmixer_behaviors} WHERE preset_id = %d AND behavior_type = '%s'",  $behavior_key['preset_id'], $behavior_key['behavior_type']);
    while ($row = db_fetch_array($result)) {
      $behaviors[$row['behavior_type']] = $row;
    }
    
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
}
 
/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_behaviors_load_form_options($preset = NULL, $type) {
  // Load behaviors from the behavior registry table
  $behaviors = listmixer_behavior_registry_load();
  
  // Push behavior information into array
  $behaviors_options = array();  
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
      if ($behavior['behavior_name'] == $name) {
        return $behavior;
      }
    }

  }
  return $behaviors;
}

/*
REFERENCE: theme.inc registry functions
saved to cache, not variable table
/**
 * Get the theme_registry cache from the database; if it doesn't exist, build
 * it.
 *
 * @param $theme
 *   The loaded $theme object.
 * @param $base_theme
 *   An array of loaded $theme objects representing the ancestor themes in
 *   oldest first order.
 * @param theme_engine
 *   The name of the theme engine.

function _theme_load_registry($theme, $base_theme = NULL, $theme_engine = NULL) {
  // Check the theme registry cache; if it exists, use it.
  $cache = cache_get("theme_registry:$theme->name", 'cache');
  if (isset($cache->data)) {
    $registry = $cache->data;
  }
  else {
    // If not, build one and cache it.
    $registry = _theme_build_registry($theme, $base_theme, $theme_engine);
    _theme_save_registry($theme, $registry);
  }
  _theme_set_registry($registry);
}
 */
/**
 * Write the theme_registry cache into the database.

function _theme_save_registry($theme, $registry) {
  cache_set("theme_registry:$theme->name", $registry);
}
 */




/*

for each allowed behavior (admin/settings/listmixer)
if module exists, load include for push behavior
create callback for the push behavior
inc adds js for the behavior
javascript contains transformation from data to form

add utlities for behaviors (php,js)


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
function listmixer_behaviors_registry_form($form_state, $behavior = array()) {
  $admin_setting = TRUE;
  $listmixer_behaviors_registry = array();  
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'push_nodereference',
      'behavior_label' => t('Content: Nodereference'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'push',
      'behavior_include' => 'behaviors/push/content/link/listmixer_push_nodereference.inc',
      'behavior_javascript' => 'behaviors/push/content/link/listmixer_push_nodereference.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/push/content/nodereference', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/push/content/nodereference', 
      'behavior_description' => t('Nodereference description'),
  ); 
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'push_link',
      'behavior_label' => t('Content: Link'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'push',
      'behavior_include' => 'behaviors/push/content/link/listmixer_push_link.inc',
      'behavior_javascript' => 'behaviors/push/content/link/listmixer_push_link.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/push/content/link', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/push/content/link', 
      'behavior_description' => t('Link description'),
  );    
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'activate_button',
      'behavior_label' => t('Button'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'activate',
      'behavior_include' => 'behaviors/activate/button/listmixer_activate_button.inc',
      'behavior_javascript' => 'behaviors/activate/button/listmixer_activate_button.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/activate/button', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/activate/button', 
      'behavior_description' => t('Activate Button description'),
  );
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'activate_mousedown',
      'behavior_label' => t('Mousedown'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'activate',
      'behavior_include' => 'behaviors/activate/mousedown/listmixer_activate_mousedown.inc',
      'behavior_javascript' => 'behaviors/activate/mousedown/listmixer_activate_mousedown.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/activate/mousedown', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/activate/mousedown', 
      'behavior_description' => t('Activate Mousedown description'),
  );
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'activate_drag',
      'behavior_label' => t('Drag'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'activate',
      'behavior_include' => 'behaviors/activate/drag/listmixer_activate_mousedown.inc',
      'behavior_javascript' => 'behaviors/activate/drag/listmixer_activate_drag.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/activate/drag', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/activate/drag', 
      'behavior_description' => t('Activate Drag description'),
  );        
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'interact_click',
      'behavior_label' => t('Click Links'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'interact',
      'behavior_include' => 'behaviors/interact/click/listmixer_interact_click.inc',
      'behavior_javascript' => 'behaviors/interact/click/listmixer_interact_click.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/interact/click', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/interact/click', 
      'behavior_description' => t('Click links description'),
  ); 
  $listmixer_behaviors_registry[] = array(
      'behavior_name' => 'interact_checkbox',
      'behavior_label' => t('Checkbox'),
      'behavior_enabled' => $admin_setting, 
      'behavior_type' => 'interact',
      'behavior_include' => 'behaviors/interact/checkbox/listmixer_interact_checkbox.inc',
      'behavior_javascript' => 'behaviors/interact/checkbox/listmixer_interact_checkbox.inc.js',
      'behavior_callback' => '/admin/ajax/listmixer/behavior/interact/checkbox', 
      'behavior_redirect' => '/admin/ajax/listmixer/redirect/interact/checkbox', 
      'behavior_description' => t('Checkbox description'),
  ); 
  // Registry stores a serialized array of all of the registry settings.  
  $form['listmixer_behavior_registry'] = array(
    '#type' => 'textarea',
    '#title' => t('List Mixer Behavior Registry'),
    '#description' => t('Registered behaviors'),
    '#default_value' => serialize($listmixer_behaviors_registry),
  );  
  return system_settings_form($form);

}