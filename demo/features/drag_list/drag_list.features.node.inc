<?php
// $Id$

/**
 * @file
 * Helper to implementation of hook_node_info().
 */
function _drag_list_node_info() {
  $items = array(
    'drag_list' => array(
      'name' => t('Drag List'),
      'module' => 'features',
      'description' => t('A content type that works with the Drag List module. This conent type contains a multiple nodereference field, and also a url link field.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
