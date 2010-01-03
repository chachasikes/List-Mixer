<?php
// $Id$

/**
 * @file
 */

/**
 * Helper to implementation of hook_node_info().
 */
function _babble_stream_node_info() {
  $items = array(
    'babble_stream' => array(
      'name' => t('BabbleStream'),
      'module' => 'features',
      'description' => t('This is a node with a text field.'),
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
