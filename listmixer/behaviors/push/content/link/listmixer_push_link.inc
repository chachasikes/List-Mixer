<?php
// $Id$

/**
 * @file
 */

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */

function listmixer_behaviors_listmixer_push_link($data) {
  // If POST data has been set, save the node
  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $node = node_load($_POST['target_id']);
    foreach (split(',', $_POST['input']) as $value) {
      // Convert URL to nid (if field type is nodereference)
      // $value = listmixer_utilities_convert_url_to_nid($value);
      $node->{$_POST['target_field']}[] = array('url' => listmixer_utilities_convert_url_to_path($value));
    }
    node_save($node);
  }

  $markup = '';
  $return = array(
    'message' => t('Link saved.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_push_link($data) {
  return t('Redirect from listmixer_push_link.');
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