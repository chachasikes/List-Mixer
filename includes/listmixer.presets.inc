<?php
// $Id$

/**
 * @file listmixer.presets.inc
 * 
 *
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
 */
function listmixer_presets ($reset = FALSE){
  static $presets = array();

  // Clear  caches if $reset is TRUE;
  if ($reset) {
    $presets = array();
    cache_clear_all('listmixer:presets', 'cache');

    // Clear the content.module cache (refreshes the list of formatters provided by imagefield.module).
   /* if (module_exists('content')) {
      content_clear_type_cache();
    }*/
  }
  // Return presets if the array is populated.
  if (!empty($presets)) {
    return $presets;
  }

  // Grab from cache or build the array. To ensure that the Drupal 5 upgrade
  // path works, we also check whether the presets list is an array.
  if (($cache = cache_get('listmixer:presets', 'cache')) && is_array($cache->data)) {
    $presets = $cache->data;
  }
  else {
    $normal_presets = array();

    $result = db_query('SELECT * FROM {listmixer_preset} ORDER BY presetname');
    while ($preset = db_fetch_array($result)) {
      $presets[$preset['presetid']] = $preset;
     // $presets[$preset['presetid']]['actions'] = listmixer_preset_actions($preset);
      $presets[$preset['presetid']]['storage'] = LISTMIXER_STORAGE_NORMAL;

      // Collect normal preset names so we can skip defaults and mark overrides accordingly
      $normal_presets[$preset['presetname']] = $preset['presetid'];
    }

    // Collect default presets and allow modules to modify them before they
    // are cached.
    $default_presets = module_invoke_all('listmixer_default_presets');
    drupal_alter('listmixer_default_presets', $default_presets);

    // Add in default presets if they don't conflict with any normal presets.
    // Mark normal presets that take the same preset namespace as overrides.
    foreach ($default_presets as $preset) {
      if (!empty($preset['presetname'])) {
        if (!isset($normal_presets[$preset['presetname']])) {
          $preset['storage'] = LISTMIXER_STORAGE_DEFAULT;
          // Use a string preset identifier
          $preset['presetid'] = $preset['presetname'];
          $presets[$preset['presetname']] = $preset;
        }
        else {
          $presetid = $normal_presets[$preset['presetname']];
          $presets[$presetid]['storage'] = LISTMIXER_STORAGE_OVERRIDE;
        }
      }
    }

    cache_set('listmixer:presets', $presets);
  }
  return $presets;
}

/**
 * Load a preset by name.
 *
 * @param preset_name
 *
 * @return
 *   preset array( 'presetname' => string, 'presetid' => integer)
 *   empty array if preset_name is an invalid preset
 */

function listmixer_preset_by_name($preset_name) {
  static $presets_by_name = array();
  if (!$presets_by_name &&  $presets = listmixer_presets()) {
    foreach ($presets as $preset) {
      $presets_by_name[$preset['presetname']] = $preset;
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
    $replacements['!presetname'] = $preset['presetname'];
    $replacements['!presetid'] = $preset['presetid'];
  }
  if (!empty($action) && !is_array($action)) {
    $replacements['!actionname'] = $action;
  }
  elseif (!empty($action)) {
    $replacements['!action'] = $action['action'];
  }
  return t($title, $replacements);
}

/**
 * Save an listmixer preset.
 *
 * @param preset
 *   an listmixer preset array.
 * @return
 *   a preset array.  In the case of a new preset, 'presetid' will be populated.
 */
function listmixer_preset_save($preset) {
  if (isset($preset['presetid']) && is_numeric($preset['presetid'])) {
    drupal_write_record('listmixer_preset', $preset, 'presetid');
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
  db_query('DELETE FROM {listmixer_preset} where presetid = %d', $preset['presetid']);
  listmixer_presets(TRUE);
  return TRUE;
}
