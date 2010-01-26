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
 */
function listmixer_utilities_convert_url_to_nid($value) {
    // Convert link to value
    // The value is set in the javascript.
    $is_relative_link = strpos($value, '/');
    $is_absolute_link = strpos($value, 'http://');
    $is_local_link = strpos($value, base_path());

    // If a link is a relative link to something in the drupal system, strip off the drupal path and replace it with absolute path.
    if (empty($is_absolute_link)) {
      if ($is_local_link == 0) {
      // Remove drupal path from the link
      $value = str_replace(base_path(), '', $value);
      // Get the node id by looking up the path alias.
      // This will try to store the node id in the nodereference field.
      // The nodereference field will be validated, and ignored if necessary during the node_save() function.
      $path = drupal_get_normal_path($value);
      // If the path points to a node, get the nid value
      if (strpos($path, 'node/') >= 0) {
        $nid = str_replace('node/', '', $path);
        // Return the node id if is exists
        return $nid;
      }
    }
  }
}


/**
 * Pass a URL as a $value.
 * If the value is relative to Drupal, convert the url to nid for the path.
 */
function listmixer_utilities_convert_url_to_path($value) {
    // Convert link to value
    // The value is set in the javascript.
    $is_relative_link = strpos($value, '/');
    $is_absolute_link = strpos($value, 'http://');
    $is_local_link = strpos($value, base_path());

    // If a link is a relative link to something in the drupal system, strip off the drupal path and replace it with absolute path.
    if (empty($is_absolute_link)) {
      // @BUG Check how this validates, it is probably wrong
      if ($is_local_link == 0) {
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
    drupal_set_message("Node " . $node->title . " saved. " . l(t("View"), "node/" . $node->nid) . "| " . l(t("Edit"), "node/" . $node->nid . "/edit") . " " . date("F j, Y, g:i:s a"), "status");
  }
  else {
    drupal_set_message("Node not saved. User does not have permission to update node " . $node->title. " " . date("F j, Y, g:i:s a"), "status");
  }
}

function listmixer_behaviors_check_duplicate($field, $field_target, $input, $data) {
  $return = TRUE;

  return $return;
}

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
  drupal_set_message(t('List Mixer preset saved'), 'status');
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