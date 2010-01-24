<?php
// $Id$

/**
 * @file
 */

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */

function listmixer_behaviors_listmixer_push_taxonomy_term($data) {
  // If POST data has been set, save the node
  // $_POST['input'] = 'Bananas,Goats,Monkeys';
  // $_POST['target_id'] = '/6x/node/6,/6x/node/7,/6x/node/8,/6x/node/30';
  if (isset($_POST['target_id']) && isset($_POST['input'])) {
    $nodes = listmixer_utilities_load_target_node($_POST['target_id']);
      // @TODO if content taxonomy? (or D7)
      // if  (isset($_POST['target_field'])) {
      //   $node->{$_POST['target_field']}[] = array('value' => $_POST['input']);
      // }
      // If terms are not already in system, do not add them to node
      foreach ($nodes as $node) {
        $terms = array();
        $tags = array();
        foreach (split(',', $_POST['input']) as $name) {
          $term = taxonomy_get_term_by_name($name);
          if (empty($node->taxonomy[$term[0]->tid])) {
            // $node->taxonomy[$term[0]->tid] = $term;
            $tags[] = $term[0]->name;
          }
        }
        $tags = implode(',', $tags);
        $node->taxonomy['tags'][1] = $tags;
        node_save($node);
      }
  }

  $markup = '';
  $return = array(
    'message' => t('Text saved.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_push_taxonomy_term($data) {
  // Take data from this function and tell it how to update.
  // @TODO Actually, the only thing we might want to return would be a messags.
  // The redirect behaviors should do things like say 'reload the uncached view block'
  // @TODO: redirect should move somewhere else.

  // @TODO Remove after done testing
  // $path = drupal_get_path('module', 'listmixer');
  // $data_rendered = drupal_add_js('Drupal.behaviors.listmixer.behaviors.return("listmixer_push_text");', 'inline');
  return t('Redirect from listmixer_push_taxonomy_term.');
}