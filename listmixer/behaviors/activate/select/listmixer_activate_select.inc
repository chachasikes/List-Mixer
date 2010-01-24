<?php
// $Id$

/**
 * @file
 */

function listmixer_behaviors_listmixer_activate_select($data) {
  $markup = '';
  $return = array(
    'message' => t('Select added.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_activate_select($data) {
  return t('Redirect from listmixer_activate_select.');
}