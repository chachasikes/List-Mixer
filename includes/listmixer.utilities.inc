<?php
// $Id$

/*
 *******************************************************************************
 * @file listmixer.utilities.inc
 *******************************************************************************
 */
 
 
// load element by name

// make node from nid

// save node (includes calling push functions)


/*
 function drag_list_ajax_store($target_nid = NULL) {
 // The value is set in the javascript.
 $link_value = $_POST['drag_list_value'];
 $is_relative_link = strpos($link_value, '/');
 $is_absolute_link = strpos($link_value, 'http://');
 $is_local_link = strpos($link_value, base_path());

 // If a link is a relative link to something in the drupal system, strip off the drupal path and replace it with absolute path.
 if (empty($is_absolute_link)) {
  if ($is_local_link == 0) {
     // Remove drupal path from the link
     $link_value = str_replace(base_path(), '', $link_value);
    // Get the node id by looking up the path alias.
    // This will try to store the node id in the node reference field. That field has user determined validators, so only certain links will be stored. 
    $path = drupal_get_normal_path($link_value);
    // If the path points to a node, get the nid value
    if (strpos($path, 'node/') >= 0) {
      $nid = str_replace('node/', '', $path);
      // Store the nodereference value in the nodereference field.
      drag_list_ajax_store_value_nodereference($target_nid, $nid, variable_get('drag_list_allowed_link_internal', 'field_link_internal'));
    }
    
  }
 }
 else{
   // Store an absolute link as a link
   drag_list_ajax_store_value_link($target_nid, $link_value, variable_get('drag_list_allowed_link_external', 'field_link_external')); 
 }
return 'Drag List value stored.';
}
*/