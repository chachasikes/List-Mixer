<?php
// $Id$

/**
 * @file listmixer_storage.nodes.inc
 * 
 *
 */
 





function listmixer_interaction_load_interactions($preset, $reset = FALSE) {
 static $interactions = array();

  // Clear  caches if $reset is TRUE;
  if ($reset) {
     $interactions = array();
    cache_clear_all('listmixer:interactions', 'cache');
  }
  // Return presets if the array is populated.
  if (!empty($interactions)) {
    return $interactions ;
  }

  if (($cache = cache_get('listmixer:interactions', 'cache')) && is_array($cache->data)) {
    $interactions = $cache->data;
  }
  else {
    $normal_interactions = array();
    cache_set('listmixer:interactions', $normal_interactions);
  }
  return $interactions;
}

function listmixer_interaction_load_block_ids() {

}
