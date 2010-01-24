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
    $node = listmixer_utilities_load_target_node($_POST['target_id']);
    // If we are sorting, deleting all text values.
    if ($_POST['interact_function'] == 'sortInteract') {
      foreach ($node->{$_POST['target_field']} as $key => $value) {
        $node->{$_POST['target_field']}[$key] = '';
      }
    }
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
