<?php
// $Id$

/**
 * @file
 */

/**
 * This function is called from an ajax menu item (based on arguments)
 * POST data is passed into the function
 */

function listmixer_behaviors_listmixer_interact_checkbox($data) {
  $markup = '';
  $interact_return = $markup;
  $return = array(
    'message' => t('Input Field created.'),
    'markup' => $markup,
    );
  return $return;
}