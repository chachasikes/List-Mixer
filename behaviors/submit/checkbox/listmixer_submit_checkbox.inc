<?php
// $Id$

/**
 * @file
 */
 
function listmixer_behaviors_listmixer_submit_checkbox($data) {
  $markup = '';
  $return = array(
    'message' => t('Submit checkbox added.'), 
    'markup' => $markup,
    );
  return $return;
} 

function listmixer_behaviors_redirect_listmixer_submit_checkbox($data) {
  return t('Redirect from listmixer_submit_checkbox.');
} 