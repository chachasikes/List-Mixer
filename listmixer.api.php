<?php
// $Id$


/**
 * @file This file demonstrates available hooks
 */

/**
 * Register a storage method with listmixer.
 *
 * @return array;
 */
function hook_listmixer_storage_register() {
  return array(
    t('Storage type name'), 
    'listmixer_storage_module_name',
  );
}