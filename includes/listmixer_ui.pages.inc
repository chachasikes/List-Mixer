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

function listmixer_ui_preset_form($form_state, $preset = array()) {
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
      '#description' => t('The namespace is used in URL\'s. Please only use alphanumeric characters, underscores (_), and hyphens (-) for preset names.'),
      '#validate' => array('listmixer_element_preset_name_validate' => array()),
    );
  }

  $form['preset_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Preset Description'),
    '#default_value' => $preset['preset_description'],
    '#description' => t('Provide a description of this interaction preset.'),
    '#rows' => 3,
    '#weight' => 1,
  );

  $form['preset_method'] = array(
    '#type' => 'select',
    '#title' => t('Select the type of storage method for this interaction.'),
    '#default_value' => $preset['preset_method'],
    '#options' => listmixer_listmixer_storage_register_load(),
    '#description' => t('Choose the method of how list data should be stored.'),
    '#weight' => 2,
  );

  $form['interaction'] = listmixer_interaction_form($preset);
  
  $form['behavior'] = listmixer_behaviors_load_form($preset);

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
  /*
  // Populate the preset_id as needed for overrides
  if (isset($form_state['values']['actions'])) {
    foreach($form_state['values']['actions'] as $action) {
      if (empty($action['preset_id'])) {
        $action['preset_id'] = $preset['preset_id'];
      }
      listmixer_action_save($action);
    }
  }
  */
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

  if (isset($preset['preset_id'])) {
    unset($preset['preset_id']);
  }
  if (isset($preset['storage'])) {
    unset($preset['storage']);
  }
  /*foreach ($preset['actions'] as $id => $action) {
    unset($preset['actions'][$id]['actionid']);
    unset($preset['actions'][$id]['preset_id']);
  }*/
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
 *
 */
function listmixer_interaction_form($preset) {
  // Based on the type of interaction $preset['preset_method'] load data from the table to be used with the interaction form.  
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Interaction'),
    '#tree' => TRUE,
    '#weight' => 8,
   // '#theme' => 'listmixer_ui_preset_interaction',
  );
  
  // The preset method is stored as the module name for the storage method.
  if(!empty($preset['preset_method'])) {
    $form_load_function = $preset['preset_method'] . '_load_interaction_form';
    if(function_exists($form_load_function)) {
      $form['interaction'] = call_user_func($form_load_function, $preset);
    }
  }
  return $form;
}
