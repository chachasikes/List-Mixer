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
    $node = node_load($_POST['target_id']);
    $weight_validate = listmixer_behaviors_check_weights($_POST['target_field'], 'nid', $_POST['input'], $data);

    
    /*
      pull out the whole existing field
      only apply this to multiple fields that show all the fields
      input brings the complete new order
      wipe the old field
      input a new one
      check that the number of values matches the number of values in input
      check that the values in input are all the same
      build individual weight handlers for all field types
      but - make a function that does all the checking of input values
      foreach (split(',', $_POST['input']) as $key => $value) {
        $node->{$_POST['target_field']}[$key] = array('nid' => $value);
      }
    */
    foreach($node->{$_POST['target_field']} as $key => $value) {
       $node->{$_POST['target_field']}[$key] = '';
    }

    foreach (split(',', $_POST['input']) as $key => $value) {
      $node->{$_POST['target_field']}[$key] = array('nid' => $value);
    }

    node_save($node);
  }

  $markup = '';
  $return = array(
//$weight_validate
'message' => t('Weight saved'),
  //  'message' => t('Nodereference Weight saved.' . var_dump('<pre>' . $data . $input . '</pre>')),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_push_nodereference_weight($data) {
  return t('Redirect from listmixer_push_weight.');
}


function listmixer_behaviors_check_weights($field, $field_target, $input, $data) {
  $return = TRUE;
  $length_field = count($field);
  $length_input = count($input);
  if($length_field == $length_input) {
    foreach($input as $key => $value) {
      dpm(($field[$field_target][$key]));
      dpm($input);
      if(in_array($field[$field_target][$key], array_values($input))) {
      }
    }
  }
  else{
    $return = FALSE;
  }
  return $return;
}