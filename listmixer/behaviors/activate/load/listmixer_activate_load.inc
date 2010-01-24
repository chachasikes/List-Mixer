<?php
// $Id$

/**
 * @file
 */

function listmixer_behaviors_listmixer_activate_load($data) {
  $markup = '';
  $return = array(
    'message' => t('Load added.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_activate_load($data) {
  return t('Redirect from listmixer_activate_load.');
}