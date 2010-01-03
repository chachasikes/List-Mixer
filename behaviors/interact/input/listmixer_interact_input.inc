<?php
// $ Id$

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 *  // Push just stores stuff.
 */
 
function listmixer_behaviors_listmixer_interact_input($data) {
  $markup = '<input></input>';
  $interact_return = $markup;
  $return = array(
    'message' => t('Input Field created.'), 
    'markup' => $markup,
    );
  return $return;
} 

function listmixer_behaviors_redirect_listmixer_interact_input($data) {
  // Take data from this function and tell it how to update.
  // @TODO Actually, the only thing we might want to return would be a messags.
  // The redirect behaviors should do things like say 'reload the uncached view block'
  // @TODO: redirect should move somewhere else.

  // @TODO Remove after done testing
  // $path = drupal_get_path('module', 'listmixer');
  // $data_rendered = drupal_add_js('Drupal.behaviors.listmixer.behaviors.return("listmixer_push_text");', 'inline');  
  return t('Redirect from listmixer_interact_input.');
} 