<?php
// $ Id$
 
function listmixer_behaviors_listmixer_submit_button($data) {
  $markup = '';
  $return = array(
    'message' => t('Submit button added.'), 
    'markup' => $markup,
    );
  return $return;
} 

function listmixer_behaviors_redirect_listmixer_submit_button($data) {
  return t('Redirect from listmixer_submit_button.');
} 