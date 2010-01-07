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
  // dpm($_POST);
  if (isset($_POST['target_id']) && isset($_POST['input']) && isset($_POST['target_field'])) {
    $node = node_load($_POST['target_id']);

    foreach (split(',', $_POST['input']) as $value) {
      $node->{$_POST['target_field']}[] = array('nid' => $value);
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

function listmixer_behaviors_redirect_listmixer_push_link_convert($value) {
  // Convert link to value
}