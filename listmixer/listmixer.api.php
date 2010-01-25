<?php
// $Id$


/**
 * @file
 * This file demonstrates available hooks
 */

/**
 * Register a storage method with listmixer.
 *
 * @return array;
 */
function hook_listmixer_storage_register() {
  return array(
    array(
    'name' => 'Name',
    'module' => 'listmixer_storage_module_name',
    'weight' => '-10', // optional
    ),
  );
}

/**
 * Implementation of hook_listmixer_default_preset
 * Generate a default listmixer preset setting.
 */
function hook_listmixer_listmixer_default_preset() {
  $preset = array (
  'preset_name' => 'sample name' . date("g_i_s_a"),
  'preset_description' => 'sample description',
  'preset_method' => 'listmixer_storage_default',
  'preset_enabled' => '0',
  'behaviors' => 
   array (
    'activate' => 'activate_load',
    'interact' => 'interact_input',
    'push' => 'push_text',
    'submit' => 'submit_button',
  ),
  'interactions' => 
    array (
      0 => 
      array (
        'id' => '8',
        'preset_id' => '8',
        'interactions_target_id' => 'div.view-id-to_do_list_current div.view-content h2 a',
        'interactions_region' => 'div.view-id-to_do_list_current',
        'interactions_inclusions' => 'form#listmixer-target-todo_list_add',
        'interactions_container' => 'div.view-id-to_do_list_current',
        'interactions_source_id' => '',
        'interactions_target_field' => 'field_item',
        'interactions_help' => 'Type your to do list item, then click \'Save.\'',
        'interactions_source_content_types' => '',
        'interactions_label' => 'Add a to do list item',
        'interactions_interact_label' => '',
        'interactions_push_label' => '',
        'interactions_submit_label' => '',
        'interactions_activate_label' => '',
        'interactions_source_id_attr' => '',
        'interactions_target_id_attr' => 'href',
        'interactions_target_id_element' => '',
      ),
    ),
  );
  return $preset;
}