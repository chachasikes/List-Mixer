<?php
// $Id$

/**
 * @file
 */

function listmixer_behaviors_listmixer_activate_button($data) {
  $markup = '';
  $return = array(
    'message' => t('Activate button added.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_activate_button($data) {
  return t('Redirect from listmixer_activate_button.');
}