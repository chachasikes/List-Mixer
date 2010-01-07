<?php
// $Id$

/**
 * @file
 */

function listmixer_behaviors_listmixer_activate_mousedown($data) {
  $markup = '';
  $return = array(
    'message' => t('Mousedown added.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_activate_mousedown($data) {
  return t('Redirect from listmixer_activate_mousedown.');
}