<?php
// $Id$

/**
 * @file
 * File for Drag List Administrative settings
 */
 
/**
 * Drag List Administrative settings (Drupal Form)
 */ 
function drag_list_admin_settings() {
  $form = array();
  // Content types that allow file extraction

  // Setting for internal link nodererence field
  $form['drag_list_allowed_link_internal'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of nodereference field, internal links'),
    '#description' => t('Select which field should be used for the nodereference field. Defaults is field_link_internal'),
    '#default_value' => variable_get('drag_list_allowed_link_internal', 'field_link_internal'),
  );
  // Setting for textfield to be used by code extract.
  $form['drag_list_allowed_link_external'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of link field, external links'),
    '#description' => t('Select which field should be used for the link field. Defaults is field_link_external'),
    '#default_value' => variable_get('drag_list_allowed_link_external', 'field_link_external'),
  );     
  // Names of Drag List block
  $form['drag_list_allowed_block'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the Drag List enabled block'),
    '#description' => t('Only one block is allowed to be the views block that allows users to store links to a particular node.'),
    '#default_value' => variable_get('drag_list_allowed_block', 'block-views-drag_list_blocks-block_1'),
  );        
  // Content type for Drag List
  // @TODO: This may be unnecessary.
  $all_nodetypes = node_get_types();
  $all_nt = array();
  foreach ($all_nodetypes as $item) {
    $all_nt[$item->type] = $item->name;
  }
  $form['drag_list_content_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content Types'),
    '#description' => t('Allow these content types to work with Drag List javascript. Note, the drag_list view must also use these content types.'),
    '#options' => $all_nt,
    '#default_value' => variable_get('drag_list_content_types', array('drag_list')),
  );  
  // Make system settings form
  return system_settings_form($form);
}