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
  // Test data
  // @TODO Move into actual tests.
  // $data->name = "test";
  $callback = "admin/ajax/listmixer/behavior/push/listmixer_push_nodereference/push_nodereference";
  if ($data->name == "test") {
    // If POST data has been set, save the node
    $_POST['target_id'] = '3';
    $_POST['input'] = '6,2,4,5';
    $_POST['target_field'] = 'field_reference_photo';
  }

  // If POST data has been set, save the node
  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $nodes = listmixer_utilities_load_target_node($_POST['target_id']);
    foreach ($nodes as $node) {
      // If we are sorting, deleting all existing node reference values.
      if ($_POST['interact_function'] == 'sortInteract') {
        foreach ($node->{$_POST['target_field']} as $key => $value) {
          $node->{$_POST['target_field']}[$key] = '';
        }
      }
      // Save values to field.
      foreach (split(',', $_POST['input']) as $value) {
        // Prevent storing duplicates.
        // @TODO Future verions of Drupal may allow this to be controlled.
        $is_duplicate = FALSE;
        foreach ($node->{$_POST['target_field']} as $key) {
          if ($key['nid'] == $value) {
            $is_duplicate = TRUE;
          }
        }
        if (!$is_duplicate) {
          $value = listmixer_utilities_convert_url_to_nid($value);
          $node->{$_POST['target_field']}[] = array('nid' => $value);
        }
      }
      listmixer_utilities_save_target_node($node);
    }
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
