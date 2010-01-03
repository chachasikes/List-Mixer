<?php
// $Id$

/**
 * @file
 */

/**
 * Helper to implementation of hook_node_info().
 */
function _photo_set_node_info() {
  $items = array(
    'photo_set' => array(
      'name' => t('Photo Set'),
      'module' => 'features',
      'description' => t('This is a list content type, it lists nodereferences to photos.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
