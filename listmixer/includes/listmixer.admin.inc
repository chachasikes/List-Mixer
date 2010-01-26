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
  $form['listmixer_hide_target'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide target values used by target value selectors'),
    '#description' => t('True or false.'),
    '#default_value' => variable_get('listmixer_hide_target', '1'),
  );
  $form['listmixer_hide_source'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide source values used by source value selectors'),
    '#description' => t('True or false.'),
    '#default_value' => variable_get('listmixer_hide_source', '1'),
  );
  // Make system settings form
  return system_settings_form($form);
}