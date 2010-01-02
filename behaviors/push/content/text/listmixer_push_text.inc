<?php
// $ Id$

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */
 
function listmixer_behaviors_listmixer_push_text($data) {
  // Do something with the data
  
  // target node id
  $target_node_id = '1'; // @TODO Remove after done testing
  $target_field_name = 'field_text_babble'; // @TODO Remove after done testing
  $user = '1'; // @TODO Remove after done testing
  // timestamp
  dpm('data' . $data);
  
  // @TODO Remove after done testing
  $path = drupal_get_path('module', 'listmixer');
  // Add main javascript file.
  drupal_add_js($path .'/behaviors/push/content/text/listmixer_push.text.inc.js', 'footer');
  
  dpm('push_text_function_called');
  return 'listmixer_push_text_function return';
} 

function listmixer_behaviors_redirect_listmixer_push_text($data) {
  return 'redirect from listmixer_push_text';
} 