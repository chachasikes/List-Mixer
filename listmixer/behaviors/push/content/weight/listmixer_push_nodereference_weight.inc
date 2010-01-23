<?php
// $Id$

/**
 * @file
 */

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */

function listmixer_behaviors_listmixer_push_nodereference_weight($data) {
  // If POST data has been set, save the node

  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $node = listmixer_utilities_load_target_node($_POST['target_id']);

    foreach ($node->{$_POST['target_field']} as $key => $value) {
       $node->{$_POST['target_field']}[$key] = '';
    }

    foreach (split(',', $_POST['input']) as $key => $value) {
     // $value = '[nid: ' . listmixer_utilities_convert_url_to_nid($value) . ']';
      $value = listmixer_utilities_convert_url_to_nid($value);
      $node->{$_POST['target_field']}[$key] = array('nid' => $value);
    }

    node_save($node);
  }

  $markup = '';
  $return = array(
    'message' => t('Weight saved'),
    'markup' => $markup,
    );
   return $return;
}

function listmixer_behaviors_redirect_listmixer_push_nodereference_weight($data) {
  return t('Redirect from listmixer_push_weight.');
}
