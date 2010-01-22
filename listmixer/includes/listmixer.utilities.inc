<?php
// $Id$

/*
 * @file
 */

// load element by name

// make node from nid

// save node (includes calling push functions)


/**
 * Pass a URL as a $value. 
 * If the value is relative to Drupal, convert the url to nid for the path.
 */
function listmixer_utilities_convert_url_to_nid($value) {
   // Convert link to value
   // The value is set in the javascript.
   $is_relative_link = strpos($value, '/');
   $is_absolute_link = strpos($value, 'http://');
   $is_local_link = strpos($value, base_path());

   // If a link is a relative link to something in the drupal system, strip off the drupal path and replace it with absolute path.
   if (empty($is_absolute_link)) {
     if ($is_local_link == 0) {
      // Remove drupal path from the link
      $value = str_replace(base_path(), '', $value);
      // Get the node id by looking up the path alias.
      // This will try to store the node id in the nodereference field. 
      // The nodereference field will be validated, and ignored if necessary during the node_save() function.
      $path = drupal_get_normal_path($value);
      // If the path points to a node, get the nid value
      if (strpos($path, 'node/') >= 0) {
        $nid = str_replace('node/', '', $path);
        // Return the node id if is exists
        return $nid;
      }
    }
  }
}


/**
 * Pass a URL as a $value. 
 * If the value is relative to Drupal, convert the url to nid for the path.
 */
function listmixer_utilities_convert_url_to_path($value) {
   // Convert link to value
   // The value is set in the javascript.
   $is_relative_link = strpos($value, '/');
   $is_absolute_link = strpos($value, 'http://');
   $is_local_link = strpos($value, base_path());

   // If a link is a relative link to something in the drupal system, strip off the drupal path and replace it with absolute path.
   if (empty($is_absolute_link)) {
      // @BUG Check how this validates, it is probably wrong
     if ($is_local_link == 0) {
      // Remove drupal path from the link
      $value = str_replace(base_path(), '', $value);
      // Get the node id by looking up the path alias.
      // This will try to store the node id in the nodereference field. 
      // The nodereference field will be validated, and ignored if necessary during the node_save() function.
      $path = drupal_get_normal_path($value);
      // Only return the path if it is valid
      if(!empty($path)) {
        return $path;
      }
    }
  }
  return $value;
}


/**
 * Load a target node, if given nid or path
 */
function listmixer_utilities_load_target_node($target_id) {
  $target_id = listmixer_utilities_convert_url_to_nid($target_id);
  $node = node_load($target_id);
  return $node;
}



function listmixer_behaviors_check_duplicate($field, $field_target, $input, $data) {
  $return = TRUE;

  return $return;
}