<?php
// $Id$

/**
 * @file
 * File for List Mixer Administrative settings
 */

/**
 * List Mixer Administrative settings (Drupal Form)
 */
function listmixer_admin_settings() {
  $form = array();
  // Setting for internal link nodererence field
  $form['listmixer_debugging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show debugging messages to the user'),
    '#description' => t('True or false.'),
    '#default_value' => variable_get('listmixer_debugging', '0'),
  );
  // Make system settings form
  return system_settings_form($form);
}

// @TODO: get list of allowed behaviors, all selected by default, able to turn unwanted ones off
