<?php
// $Id$

/**
 * @file
 */

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */

function listmixer_behaviors_listmixer_push_text($data) {
  // Test data
  // @TODO Move into actual tests.
  // $data->name = "test";
  $callback = "admin/ajax/listmixer/behavior/push/listmixer_push_text/push_text";
  if ($data->name == "test") {
    // If POST data has been set, save the node
    $_POST['target_id'] = '1';
    $_POST['input'] = 'Test content generated at: ' . date("F j, Y, g:i:s a");
    $_POST['target_field'] = 'field_text_babble';
  }

  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $nodes = listmixer_utilities_load_target_node($_POST['target_id']);
    foreach ($nodes as $node) {
      // If we are sorting, deleting all text values.
      if ($_POST['interact_function'] == 'sortInteract') {
        foreach ($node->{$_POST['target_field']} as $key => $value) {
          $node->{$_POST['target_field']}[$key] = '';
        }
      }
      //node->{$_POST['target_field']}[] = array('value' => $_POST['input']);
      // Save values to field.
      foreach (split(',', $_POST['input']) as $value) {
        // Prevent storing duplicates.
        // @TODO Future verions of Drupal may allow this to be controlled.
        $is_duplicate = FALSE;
        foreach ($node->{$_POST['target_field']} as $key) {
          if ($key['nid'] == $value) {
            $is_duplicate = TRUE; // Turn off duplicate check for text fields
          }
        }
        if (!$is_duplicate) {
          $node->{$_POST['target_field']}[] = array('value' => $value);
        }
      }
      listmixer_utilities_save_target_node($node);
    }
  }

  $markup = '';
  $return = array(
    'message' => t('Text saved.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_push_text($data) {
  // Take data from this function and tell it how to update.
  // @TODO Actually, the only thing we might want to return would be a messags.
  // The redirect behaviors should do things like say 'reload the uncached view block'
  // @TODO: redirect should move somewhere else.

  // @TODO Remove after done testing
  // $path = drupal_get_path('module', 'listmixer');
  // $data_rendered = drupal_add_js('Drupal.behaviors.listmixer.behaviors.return("listmixer_push_text");', 'inline');
  return t('Redirect from listmixer_push_text.');
}