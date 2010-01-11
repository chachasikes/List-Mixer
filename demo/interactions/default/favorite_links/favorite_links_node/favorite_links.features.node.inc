<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _favorite_links_node_info() {
  $items = array(
    'favorite_links' => array(
      'name' => t('Favorite Links'),
      'module' => 'features',
      'description' => t('My list of favorite links.'),
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
