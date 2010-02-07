<?php
// $Id$

/**
 * @file
 */

function listmixer_behaviors_listmixer_submit_button_refresh($data) {
  $markup = '';
  $return = array(
    'message' => t('Submit & Refresh button added.'),
    'markup' => $markup,
    );
  return $return;
}

function listmixer_behaviors_redirect_listmixer_submit_button_refresh($data) {
  return t('Redirect from listmixer_submit_button_refresh.');
}