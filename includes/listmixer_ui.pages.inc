<?php
// $Id$

/**
 * @file listmixer_ui.presets.inc
 * Much of this module was based on the structure for creating presets in listmixer
 */
 
/**
 * Create overview
 */ 
function listmixer_ui_overview() {
  $header = array(t('Interaction Preset'), t('Storage'), t('Actions'), t('Description'));
  $rows = array();
  // Always clear the preset cache on this display.
  foreach (listmixer_presets(TRUE) as $preset) {
    $row = array();
    $row[] = l($preset['preset_name'], 'admin/build/listmixer/'. $preset['preset_id']);
    $links = array();
    switch ($preset['storage']) {
      case LISTMIXER_STORAGE_DEFAULT:
        $row[] = t('Default');
        $links[] = l(t('View'), 'admin/build/listmixer/'. $preset['preset_id']);
        break;
      case LISTMIXER_STORAGE_OVERRIDE:
        $row[] = t('Override');
        $links[] = l(t('Edit'), 'admin/build/listmixer/'. $preset['preset_id']);
        $links[] = l(t('Revert'), 'admin/build/listmixer/'. $preset['preset_id'] .'/delete');
        $links[] = l(t('Export'), 'admin/build/listmixer/'. $preset['preset_id'] .'/export' );
        break;
      case LISTMIXER_STORAGE_NORMAL:
        $row[] = t('Normal');
        $links[] = l(t('Edit'), 'admin/build/listmixer/'. $preset['preset_id']);
        $links[] = l(t('Delete'), 'admin/build/listmixer/'. $preset['preset_id'] .'/delete');
        $links[] = l(t('Export'), 'admin/build/listmixer/'. $preset['preset_id'] .'/export' );
        break;
    }
    $row[] = implode('&nbsp;&nbsp;&nbsp;&nbsp;', $links);
    $row[] = $preset['preset_description'];
    $rows[] = $row;
  }
  $output = theme('table', $header, $rows);
  return $output;
}
