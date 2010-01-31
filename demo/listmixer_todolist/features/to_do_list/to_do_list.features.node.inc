<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _to_do_list_node_info() {
  $items = array(
    'to_do_list' => array(
      'name' => t('To Do List'),
      'module' => 'features',
      'description' => t('A to-do list.'),
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
