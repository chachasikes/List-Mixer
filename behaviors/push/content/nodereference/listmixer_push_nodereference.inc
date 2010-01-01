<?php
// $Id$

/*
 *******************************************************************************
 * @file listmixer_push_nodereference.module
 * 
 *******************************************************************************
 */
 
/**
 * Implementations of hook_listmixer_behavior_register

function listmixer_push_nodereference_listmixer_behavior_register() {
  return array(
    array(
    'name' => 'Nodereference', 
    'module' => 'listmixer_push_nodereference',
    'weight' => '-10', // optional
    ),
  );
}
  */  
 
/** 
 * Load javascript functions for this behavior
 */ 
function listmixer_push_nodereference_listmixer_behavior_load() {

}

function listmixer_push_nodereference_listmixer_behavior_save() {

}

/*
$data = array(
  0 => array(
    '#user' => 'uid',
    '#restrictions' => array(),
    '#inclusions' => array(),
    '#timestamp' => 'timestamp',
    '#path' => 'current/path',
    '#message' => 'watchdog message',
    '#settings' => array(
      '#target' => array(
        '#storage' => 'node',
        '#nid' => NULL,
        '#type' => 'content_type_name',
        '#permission' => array(),
        '#fieldname' => 'field_field_name',
        '#processor' => 'nodereference', // behavior processor, how the data will get converted
      ),
     ),
     '#value' => array(
      '#source' => 'raw content loaded from jquery', // Data gathered from javascript   
     ),
  ),
);


$processor = array(
  '#processor' => 'nodereference',
  '#callback' => 'functionname',
  '#processed' => array(), // Element returned here.
  '#source' => '',
  '#default_value' => array(), // Preloaded from node.
  '#data_processed' => array(), // This is the data that will be stored in the form.  
);


/*
Every time an interaction is submitted it will trigger a node save event.

Multiple pieces of data could be collected, and passed into a data object.

The data object is then processed on node save, running through each
piece of data, determining its storage type (node or taxonomy - which is 
just about how a list is created, so they are very different treatments)



*/


/**
 * hook_listmixer_load (might not be a real hook, just a function
 * naming convention.)
 *
 * 
 *
 */
function listmixer_push_nodereference_listmixer_load($data) {

  // @TODO Load element format if possible.

  if (isset($target_nid) && isset($link_value)) {
    $node = node_load($target_nid);
    // See if the value has already been set for the field.
    foreach ($node->{$field} as $key => $value) {
      $nid_exists = FALSE;
      // TODO: require link/nodereference modules
      if ($node->{$field}[$key]['nid'] == $link_value) {
        $nid_exists = TRUE;
        break; 
      }     
    }
    if (!$nid_exists) {
      // Add value to beginning of the array.
       array_unshift($node->{$field}, array( 'nid' => $link_value ));
       node_save($node);
       return 'Node saved.';
    }
    else{
      return 'Node not saved because value already exists.';
    }
  }
  else{
    return 'Nodereference value not stored due to an error.';
  }



/* deletion would be handled by javascript unsetting a value, then saving normally*/

/* probably an implementation of a special timestamp for field/taxonomy terms */
function listmixer_push_nodereference_listmixer_timestamp() {

}

/* probably unnecessary */
function listmixer_push_nodereference_listmixer_behavior_submit() {

}

function listmixer_push_nodereference_listmixer_behavior_validate() {

}

// @TODO: provide settings for the interaction about which field to target (load all the names of field of this type for content type)

/*

function drag_list_init() {
  // Add the javascript.
  $path = drupal_get_path('module', 'drag_list');
  // Set Drupal javascript value to the block ID stored in settings.
  drupal_add_js( array(
    'drag_list' => array(
      'dragListBlockId' => variable_get('drag_list_allowed_block', 'block-views-drag_list_blocks-block_1'), 
      ),
    ),
   'setting');
  // Add main javascript file.
  drupal_add_js($path .'/drag_list.js');
  // Add custom style sheet.
  drupal_add_css($path .'/drag_list.css');
}

function drag_list_ajax_store_value_nodereference($target_nid, $link_value, $field) {
  if (isset($target_nid) && isset($link_value)) {
    $node = node_load($target_nid);
    // See if the value has already been set for the field.
    foreach ($node->{$field} as $key => $value) {
      $nid_exists = FALSE;
      // TODO: require link/nodereference modules
      if ($node->{$field}[$key]['nid'] == $link_value) {
        $nid_exists = TRUE;
        break; 
      }     
    }
    if (!$nid_exists) {
      // Add value to beginning of the array.
       array_unshift($node->{$field}, array( 'nid' => $link_value ));
       node_save($node);
       return 'Node saved.';
    }
    else{
      return 'Node not saved because value already exists.';
    }
  }
  else{
    return 'Nodereference value not stored due to an error.';
  }
}

*/