<?php
// $Id$

/**
 * @file listmixer_ui.presets.inc
 */
 
/**
 * Create overview
 */ 
function listmixer_ui_overview() {
  $header = array(t('Preset Name'), t('Storage'), t('Actions'));
  $rows = array();
  // Always clear the preset cache on this display.
 /* foreach (imagecache_presets(TRUE) as $preset) {
    $row = array();
    $row[] = l($preset['presetname'], 'admin/build/imagecache/'. $preset['presetid']);
    $links = array();
    switch ($preset['storage']) {
      case IMAGECACHE_STORAGE_DEFAULT:
        $row[] = t('Default');
        $links[] = l(t('View'), 'admin/build/imagecache/'. $preset['presetid']);
        $links[] = l(t('Flush'), 'admin/build/imagecache/'. $preset['presetid'] .'/flush' );
        break;
      case IMAGECACHE_STORAGE_OVERRIDE:
        $row[] = t('Override');
        $links[] = l(t('Edit'), 'admin/build/imagecache/'. $preset['presetid']);
        $links[] = l(t('Revert'), 'admin/build/imagecache/'. $preset['presetid'] .'/delete');
        $links[] = l(t('Flush'), 'admin/build/imagecache/'. $preset['presetid'] .'/flush' );
        $links[] = l(t('Export'), 'admin/build/imagecache/'. $preset['presetid'] .'/export' );
        break;
      case IMAGECACHE_STORAGE_NORMAL:
        $row[] = t('Normal');
        $links[] = l(t('Edit'), 'admin/build/imagecache/'. $preset['presetid']);
        $links[] = l(t('Delete'), 'admin/build/imagecache/'. $preset['presetid'] .'/delete');
        $links[] = l(t('Flush'), 'admin/build/imagecache/'. $preset['presetid'] .'/flush' );
        $links[] = l(t('Export'), 'admin/build/imagecache/'. $preset['presetid'] .'/export' );
        break;
    }
    $row[] = implode('&nbsp;&nbsp;&nbsp;&nbsp;', $links);
    $rows[] = $row;
  }*/
  $output = theme('table', $header, $rows);
  return $output;
}

/**
 * Add preset
 */
function listmaker_ui_preset_add() {
}

/**
 * Edit preset
 */
function listmaker_ui_preset_edit() {
}

/**
 * Delete preset
 */
function listmaker_ui_preset_delete() {
}

/**
 * Export preset
 */
function listmaker_ui_preset_export() {
}

/**
 * Override preset
 */
function listmaker_ui_preset_override() {
}
