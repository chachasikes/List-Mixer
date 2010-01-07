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
  // If POST data has been set, save the node
  // dpm($_POST);
  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $node = node_load($_POST['target_id']);
    // dpm($_POST['input']);
    $node->{$_POST['target_field']}[] = array('value' => $_POST['input']);
    node_save($node);
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