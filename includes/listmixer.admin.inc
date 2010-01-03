<?php
// $Id$

/**
 * @file listmixer.admin.inc
 * File for List Mixer Administrative settings
 */
 
/**
 * List Mixer Administrative settings (Drupal Form)
 */ 
function listmixer_admin_settings() {
  $form = array();
  /*
  // Setting for internal link nodererence field
  $form['listmixer_allowed_link_internal'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of nodereference field, internal links'),
    '#description' => t('Select which field should be used for the nodereference field. Defaults is field_link_internal'),
    '#default_value' => variable_get('listmixer_allowed_link_internal', 'field_link_internal'),
  );
  */
  // Make system settings form
  return system_settings_form($form);
}



// @TODO: get list of allowed behaviors, all selected by default, able to turn unwanted ones off

// @TODO: add controls to show hide debugging messages