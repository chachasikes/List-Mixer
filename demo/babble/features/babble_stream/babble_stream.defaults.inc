<?php
// $Id$

/**
 * @file
 */

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _babble_stream_content_default_fields() {
  $fields = array();

  // Exported field: field_text_babble
  $fields[] = array(
    'field_name' => 'field_text_babble',
    'type_name' => 'babble_stream',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '5',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_text_babble][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Babble',
      'weight' => '31',
      'description' => 'Enter content.',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Translatables
  array(
    t('Babble'),
  );

  return $fields;
}
