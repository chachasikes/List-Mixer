<?php
// $Id$

/*
 * @file
 */

/**
 * Determine which listmixer behavior function should be run based on arguments
 *
 */
function listmixer_behaviors_callback($type, $name, $root) {
  $data_post_value_name = 'data_' . $name;
  $data = $_POST[$data_post_value_name];
  // Load callback function.
  $function_name = 'listmixer_behaviors_' . $name;

  // Load include (path stored with behavior library)
  // @TODO The library might get consolidated to not be all includes,
  // but not until most of the library is actually built.
  // Get the registered behaviors.
  $behavior = listmixer_behavior_registry_load($root);
  // Load include file.
  if (file_exists($behavior['behavior_include'])) {
    include($behavior['behavior_include']);
  }
  // Call function for handling callback.
  if (function_exists($function_name)) {
    $return = call_user_func($function_name, $data);
    if (!empty($return)) {
      /*
      If we need to add more javascript to the page here, use this function.
      $set_rendered_markup = drupal_add_js('Drupal.behaviors.listmixer.behaviors.return.'
      . $behavior['behavior_name'] . '("' . $return['message'] . '");', 'inline');
      // dpm($set_rendered_markup);
      */

      // Return nothing, but set a message.
      // @TODO Date is added for testing purposes. May become unneccessary
      // If debugging messages allowed, set message every time a behavior callback is executed.
      // @TODO actually, only 1 message is set, it seems, not several as one might expect.
      if (variable_get('listmixer_debugging', 0)) {
        drupal_set_message($return['message'] . ' ' . date("F j, Y, g:i:s a"), 'status', TRUE);
      }
    }
    else{
      if (variable_get('listmixer_debugging', 0)) {
        drupal_set_message(t('Warning: Data not saved. Source: '
        . $function_name . ' ' . date("F j, Y, g:i:s a")), 'status');
      }
    }
  }
  else{
      if (variable_get('listmixer_debugging', 0)) {
        drupal_set_message(t('Warning: Data not saved. Source: '
        . $function_name . ' ' . date("F j, Y, g:i:s a")), 'status');
      }
  }
  // @DEBUG Enable for debugging callbacks
  // return '';
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
  /* if (($cache = cache_get('listmixer:presets', 'cache')) && is_array($cache->data)) {
    $presets = $cache->data;
  }*/
  else {
    $normal_presets = array();

    $result = db_query('SELECT * FROM {listmixer_preset} ORDER BY preset_name');

    while ($preset = db_fetch_array($result)) {
      $presets[$preset['preset_id']] = $preset;
     // $presets[$preset['preset_id']]['behaviors'] = listmixer_behaviors_load(array('preset_id' => $preset['preset_id']));
      $presets[$preset['preset_id']]['behaviors'] = listmixer_behaviors_load($preset, array('activate', 'interact', 'push', 'submit'));
      $presets[$preset['preset_id']]['interactions'] = listmixer_interactions_load($preset);

      $presets[$preset['preset_id']]['storage'] = LISTMIXER_STORAGE_NORMAL;

      // Collect normal preset names so we can skip defaults and mark overrides accordingly
      $normal_presets[$preset['preset_name']] = $preset['preset_id'];
    }

    // Collect default presets and allow modules to modify them.
    $default_presets = listmixer_default_presets_load();
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
 * Determine which listmixer behavior function should be run based on arguments
 * @TEST: Create test for each callback
 * @TEST: Check what is returned
 */
function listmixer_behaviors_redirect_callback($type, $name, $root) {
  // @TODO: Fill in if necessary.
}

/**
 * Pass a URL as a $value.
 * If the value is relative to Drupal, convert the url to nid for the path.
 * @TODO This function just changed, test vigorously. 
 */
function listmixer_utilities_convert_url_to_nid($value) {
  $is_relative_link = strpos($value, '/');
  $path = listmixer_utilities_convert_url_to_path($value);
  // If the path points to a node, get the nid value
  if (strpos($path, 'node/') >= 0) {
    $nid = str_replace('node/', '', $path);
    if ($is_relative_link == 0){
      $nid = str_replace('/', '', $nid);
    }
    // Return the node id if is exists
    return $nid;
  }
  else {
    return $value;
  }
}

/**
 * Pass a URL as a $value.
 * If the value is relative to Drupal, convert the url to nid for the path.
 */
function listmixer_utilities_convert_url_to_path($value) {
  // Convert link to value
  // The value is set in the javascript.
  $is_absolute_link = strpos($value, 'http://');
  $is_local_link = strpos($value, base_path());
  $is_node = strpos($value, 'node/');
  // If a link is a relative link to something in the drupal system, strip off the drupal path and replace it with absolute path.
  if (empty($is_absolute_link)) {
    if (($is_local_link == 0) && $is_node == 0) {
      // Remove drupal path from the link
      $value = str_replace(base_path(), '', $value);
      // Get the node id by looking up the path alias.
      // This will try to store the node id in the nodereference field.
      // The nodereference field will be validated, and ignored if necessary during the node_save() function.
      $path = drupal_get_normal_path($value);
      // Only return the path if it is valid
      if (!empty($path)) {
        return $path;
      } 
    }
    else {
      // Is a path to a node.
      $path = drupal_get_normal_path($value);
      return $path;     
    }
  }
  return $value;
}

/**
 * Load a target node, if given nid or path
 */
function listmixer_utilities_load_target_node($target_id_array) {
  $nodes = array();
  $target = explode( ',', $target_id_array);
  foreach ($target as $target_id) {
    $target_id = listmixer_utilities_convert_url_to_nid($target_id);
    $node = node_load($target_id);
    $nodes[] = $node;
  }
  return $nodes;
}

/**
 * Save a target node, if current user has proper permissions
 */
function listmixer_utilities_save_target_node($node) {
  global $user;
  $access = node_access('update', $node, $user);
  if ($access) {
    node_save($node);
    drupal_set_message(t("Node " . $node->title . " saved.") . " " . l(t("View"), "node/" . $node->nid) . "| " . l(t("Edit"), "node/" . $node->nid . "/edit") . " " . date("F j, Y, g:i:s a"), "status");
  }
  else {
    drupal_set_message(t("Node not saved. User does not have permission to update node") . " " . $node->title . " " . date("F j, Y, g:i:s a"), "status");
  }
}

function listmixer_behaviors_check_duplicate($field, $field_target, $input, $data) {
  $return = TRUE;

  return $return;
}

/**
 * Adjust $preset before it is given to javascript
 */
function listmixer_adjust_preset_for_js($preset) {
  if (!empty($preset['interactions'][0])) {
    $preset['interactions'] = $preset['interactions'][0];
  }
  // Remove behavior include
  return $preset;
}

/**
 * Establish which behavior types are allowed for listmixer.
 * @TODO This may get extended eventually.
 * Possibilities: delete, deactivate, undo.
 */
function listmixer_behaviors_types() {
  $behaviors_types = array(
    'types' => array(
      'activate' => array(
        'type' => 'activate',
        '#title' => t('Activate'),
        '#description' => t('Choose activate behaviors.'),
      ),
      'interact' => array(
        'type' => 'interact',
        '#title' => t('Interact'),
        '#description' => t('Choose interact behaviors.'),
      ),
      'push' => array(
        'type' => 'push',
        '#title' => t('Push'),
        '#description' => t('Choose push behaviors.'),
      ),
      'submit' => array(
        'type' => 'submit',
        '#title' => t('Submit'),
        '#description' => t('Choose submit behaviors.'),
      ),
    ),
  );
  return $behaviors_types;
}