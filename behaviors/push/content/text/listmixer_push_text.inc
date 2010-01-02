<?php
// $ Id$

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */
function listmixer_behaviors_listmixer_push_text($data) {
  // Do something with the data
  
  // target node id
  // field target
  // user
  // timestamp
  // raw data from javascript
  
  dpm('push_text_function_called');
  return 'listmixer_push_text_function return';
} 