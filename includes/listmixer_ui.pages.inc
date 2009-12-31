<?php
// $Id$

/**
 * @file listmixer_ui.presets.inc
 * Much of this module was based on the structure for creating presets in imagecache
 */
 
/**
 * Create overview
 */ 
function listmixer_ui_overview() {
  $header = array(t('Preset Name'), t('Storage'));
  $rows = array();
  // Always clear the preset cache on this display.
  foreach (listmixer_presets(TRUE) as $preset) {
    $row = array();
    $row[] = l($preset['presetname'], 'admin/build/listmixer/'. $preset['presetid']);
    $links = array();
    switch ($preset['storage']) {
      case LISTMIXER_STORAGE_DEFAULT:
        $row[] = t('Default');
        $links[] = l(t('View'), 'admin/build/listmixer/'. $preset['presetid']);
        break;
      case LISTMIXER_STORAGE_OVERRIDE:
        $row[] = t('Override');
        $links[] = l(t('Edit'), 'admin/build/listmixer/'. $preset['presetid']);
        $links[] = l(t('Revert'), 'admin/build/listmixer/'. $preset['presetid'] .'/delete');
        $links[] = l(t('Export'), 'admin/build/listmixer/'. $preset['presetid'] .'/export' );
        break;
      case LISTMIXER_STORAGE_NORMAL:
        $row[] = t('Normal');
        $links[] = l(t('Edit'), 'admin/build/listmixer/'. $preset['presetid']);
        $links[] = l(t('Delete'), 'admin/build/listmixer/'. $preset['presetid'] .'/delete');
        $links[] = l(t('Export'), 'admin/build/listmixer/'. $preset['presetid'] .'/export' );
        break;
    }
    $row[] = implode('&nbsp;&nbsp;&nbsp;&nbsp;', $links);
    $rows[] = $row;
  }
  $output = theme('table', $header, $rows);
  return $output;
}

/**
 * Add preset
 */
function listmixer_ui_preset_form($form_state, $preset = array()) {
  $form = array();

  $form['presetid'] = array(
    '#type' => 'value',
    '#value' => $preset['presetid'],
  );
  
  // Browsers don't submit disabled form values so we've got to put two copies
  // of the name on the form: one for the submit handler and one for the user.

  if ($preset['storage'] === LISTMIXER_STORAGE_DEFAULT) {
    $form['presetname'] = array(
      '#type' => 'value',
      '#value' => $preset['presetname'],
    );
    $form['presetname_display'] = array(
      '#type' => 'textfield',
      '#size' => '64',
      '#title' => t('Preset Namespace'),
      '#default_value' => $preset['presetname'],
      '#disabled' => TRUE,
    );
  }
  else {
    $form['presetname'] = array(
      '#type' => 'textfield',
      '#size' => '64',
      '#title' => t('Preset Namespace'),
      '#default_value' => $preset['presetname'],
      '#description' => t('The namespace is used in URL\'s. Please only use alphanumeric characters, underscores (_), and hyphens (-) for preset names.'),
      '#validate' => array('listmixer_preset_form_validate' => array()),
    );
  }

  $form['presetname'] = array(
    '#type' => 'value',
    '#value' => $preset['presetname'],
  );
  $form['presetname_display'] = array(
    '#type' => 'textfield',
    '#size' => '64',
    '#title' => t('Preset Namespace'),
    '#default_value' => $preset['presetname'],
   // '#disabled' => TRUE, // TODO: What's up with disabled?
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $preset['storage'] === LISTMIXER_STORAGE_DEFAULT ? t('Override Defaults') : t('Save Preset'),
    '#weight' => 9,
  );
  
   // For new presets don't show the preview or all actions to be added.
  if (empty($preset['presetid'])) {
    return $form;
  } 
  
  return $form;
}

function listmixer_preset_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  // Check for duplicates
  foreach (listmixer_presets() as $preset) {
    if ($values['presetname'] == $preset['presetname'] && $values['presetid'] != $preset['presetid']) {
      form_set_error('presetname', t('The preset name you have chosen is already in use.'));
      break;
    }
  }

  // Check for illegal characters in preset names
  if (preg_match('/[^0-9a-zA-Z_\-]/', $values['presetname'])) {
    form_set_error('presetname', t('Please only use alphanumeric characters, underscores (_), and hyphens (-) for preset names.'));
  }
}

function listmixer_ui_preset_form_submit($form, &$form_state) {
  // Save the preset first to retrieve the presetid when overriding
  $preset = listmixer_preset_save($form_state['values']);

  // Push back to the preset form
  $form_state['redirect'] = 'admin/build/listmixer/'. $preset['presetid'];
}

/**
 * Edit preset
 */
function listmixer_ui_preset_edit_form() {
}

/**
 * Delete preset
 */
function listmixer_ui_preset_delete_form() {
}

/**
 * Export preset
 */
function listmixer_ui_preset_export_form() {
}

/**
 * Override preset
 */
function listmixer_ui_preset_override_form() {
}
