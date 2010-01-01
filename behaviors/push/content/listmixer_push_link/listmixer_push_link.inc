<?php
// $Id$

/*
 *******************************************************************************
 * @file listmixer_push_link.module
 * 
 *******************************************************************************
 */
 
/**
 * Implementations of hook_listmixer_behavior_register
 
function listmixer_push_link_listmixer_behavior_register() {
  return array(
    array(
    'name' => 'Nodereference', 
    'module' => 'listmixer_push_link',
    ),
  );
}
  */ 
 
/** 
 * Load javascript functions for this behavior
 */ 
function listmixer_push_link_listmixer_behavior_load() {

}

/**
 * Pass in data from javascript (format as generic as possible)
 * 
 * It is possible that push would become a hook to, when it is called
 it gathers all the data from javascript, collects all the fields that
 should be updated, and then sets the node form before it would be saved.
 */
function listmixer_push_link_push(&$node, $data) {
  $element = array(
  
  );
// Generate the form element (possibly using existing rules/actions for field
}


/* deletion would be handled by javascript unsetting a value, then saving normally*/

/* probably an implementation of a special timestamp for field/taxonomy terms */
function listmixer_push_link_listmixer_timestamp() {

}

/* probably unnecessary */
function listmixer_push_link_listmixer_behavior_submit() {

}

function listmixer_push_link_listmixer_behavior_validate() {

}

/*
function drag_list_ajax_store_value_link($target_nid, $link_value, $field) {
  if (isset($target_nid) && isset($link_value)) {
    $node = node_load($target_nid);
    // See if the value has already been set for the field.
    foreach ($node->{$field} as $key => $value) {
      $nid_exists = FALSE;
      if ($node->{$field}[$key]['url'] == $link_value) {
        $nid_exists = TRUE;
        break; 
      }     
    }
    if (!$nid_exists) {
      // Add value to beginning of the array.
       array_unshift($node->{$field}, array(
        'url' => $link_value, 
        'title' => '', 
        'attributes' => array(
          'target' => '',
          'class' => '',
          'rel' => '',
        ),
        ));
        node_save($node);
        return 'Node saved.';
    }
    // TODO: What happens if invalid code is passed into the node?
    else{
      return 'Node not saved because value already exists.';
    }
  }
  else{
    return 'Nodereference value not stored due to an error.';
  }
}
*/