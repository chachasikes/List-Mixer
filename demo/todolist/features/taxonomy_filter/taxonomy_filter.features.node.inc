<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _taxonomy_filter_node_info() {
  $items = array(
    'taxonomy_filter' => array(
      'name' => t('Taxonomy Filter'),
      'module' => 'features',
      'description' => t('A node containing a list of terms that should be allowed for a users filters.'),
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
