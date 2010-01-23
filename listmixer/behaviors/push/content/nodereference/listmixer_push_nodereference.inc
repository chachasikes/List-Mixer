<?php
// $Id$

/**
 * @file
 */

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */

function listmixer_behaviors_listmixer_push_nodereference($data) {
  // If POST data has been set, save the node
  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $node = listmixer_utilities_load_target_node($_POST['target_id']);

    foreach (split(',', $_POST['input']) as $value) {
      $is_duplicate = FALSE;
      foreach ($node->{$_POST['target_field']} as $key) {
        if ($key['nid'] == $value) {
          $is_duplicate = TRUE;
        }
        // Clear out nodereferences
        //$node->{$_POST['target_field']}[$key1]['nid'] = '';
      }

      if (!$is_duplicate) {
        $node->{$_POST['target_field']}[] = array('nid' => $value);
      }
    }

    node_save($node);
  }

  $markup = '';
  $return = array(
    'message' => t('Nodereference saved.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_push_nodereference($data) {
  return t('Redirect from listmixer_push_nodereference.');
}
