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
  $header = array(t('Interaction Preset'), t('Storage'), t('Actions'));
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
      '#validate' => array('listmixer_element_presetname_validate' => array()),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $preset['storage'] === LISTMIXER_STORAGE_DEFAULT ? t('Override Defaults') : t('Save Preset'),
    '#weight' => 9,
  );

  // For new presets don't show the preview or all actions to be added.
  if (empty($preset['presetid'])) {
    return $form;
  }
  /*
  $form['actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Actions'),
    '#tree' => TRUE,
    '#theme' => 'listmixer_ui_preset_actions',
  );

  foreach ($preset['actions'] as $i => $action) {
    // skip unknown actions...
    if (!$definition = listmixer_action_definition($action['action'])) {
      continue;
    }
    $action_form['name'] = array(
      '#value' => t($definition['name']),
    );

    $action_form['action'] = array(
      '#type' => 'value',
      '#value' => $action['action'],
    );
    $action_form['actionid'] = array(
      '#type' => 'value',
      '#value' => $action['actionid'],
    );
    $action_form['presetid'] = array(
      '#type' => 'value',
      '#value' => $action['presetid'],
    );

    $action_form['settings'] = array(
      '#theme' => $action['action'],
      '#value' => $action['data'],
    );
    $action_form['data'] = array(
      '#type' => 'value',
      '#value' => $action['data'],
    );
    $action_form['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $action['weight'],
      '#access' => $preset['storage'] !== LISTMIXER_STORAGE_DEFAULT,
    );
    $action_form['configure'] = array(
      '#value' => l(t('Configure'), 'admin/build/listmixer/'. $action['presetid'] .'/'. $action['actionid'] ),
      '#access' => $preset['storage'] !== LISTMIXER_STORAGE_DEFAULT,
    );
    $action_form['remove'] = array(
      '#value' => l(t('Delete'), 'admin/build/listmixer/'. $action['presetid'] .'/'. $action['actionid'] .'/delete'),
      '#access' => $preset['storage'] !== LISTMIXER_STORAGE_DEFAULT,
    );
    $form['actions'][$i] = $action_form;
  }

  $form['actions']['new'] = array(
    '#tree' => FALSE,
    '#type' => 'fieldset',
    '#title' => t('New Actions'),
    '#collapsible' => TRUE,
    '#collapsed' => count($preset['actions']) > 0,
    '#access' => $preset['storage'] !== LISTMIXER_STORAGE_DEFAULT,
  );
  foreach (listmixer_action_definitions() as $action => $definition) {
    $form['actions']['new'][] = array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#value' => l(t('Add !action', array('!action' => $definition['name'])),
                    'admin/build/listmixer/'.  $preset['presetid'] .'/add/'. $action) .
                    ' - '. $definition['description'],
    );
  }*/
  return $form;
}

function listmixer_ui_preset_form_validate($form, &$form_state) {
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
  /*
  // Populate the presetid as needed for overrides
  if (isset($form_state['values']['actions'])) {
    foreach($form_state['values']['actions'] as $action) {
      if (empty($action['presetid'])) {
        $action['presetid'] = $preset['presetid'];
      }
      listmixer_action_save($action);
    }
  }
  */
  // Push back to the preset form
  $form_state['redirect'] = 'admin/build/listmixer/'. $preset['presetid'];
}


function listmixer_ui_preset_delete_form($form_state, $preset = array()) {

  if (empty($preset)) {
    drupal_set_message(t('The specified preset was not found'), 'error');
    drupal_goto('admin/build/listmixer');
  }

  $form = array();
  $form['presetid'] = array('#type' => 'value', '#value' => $preset['presetid']);
  return confirm_form(
    $form,
    t('Are you sure you want to delete the preset %preset?',
      array('%preset' => $preset['presetname'])
    ),
    'admin/build/listmixer',
    t('This action cannot be undone.'),
    t('Delete'),  t('Cancel')
  );
}

function listmixer_ui_preset_delete_form_submit($form, &$form_state) {
  $preset = listmixer_preset($form_state['values']['presetid']);
  listmixer_preset_delete($preset);
  drupal_set_message(t('Preset %name (ID: @id) was deleted.', array('%name' => $preset['presetname'], '@id' => $preset['presetid'])));
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

  if (isset($preset['presetid'])) {
    unset($preset['presetid']);
  }
  if (isset($preset['storage'])) {
    unset($preset['storage']);
  }
  /*foreach ($preset['actions'] as $id => $action) {
    unset($preset['actions'][$id]['actionid']);
    unset($preset['actions'][$id]['presetid']);
  }*/
  $exported = '$presets = array();';
  $exported .= "\n";
  $exported .= '$presets[\''. $preset['presetname'] .'\'] = ';
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

function listmixer_ui_preset_export_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/listmixer';
}
