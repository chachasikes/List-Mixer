<?php
// $Id$

/*
 * @file
 * Hook implementations used by other modules
 */

/**
 * When a module contains a hook_listmixer_storage_register
 */
function listmixer_listmixer_storage_register_load() {
  $methods = module_invoke_all('listmixer_storage_register');
  $storage_methods = array();
  foreach ($methods as $method) {
    $storage_methods[$method['module']] = $method['name'];
  }
  return $storage_methods;
}

/**
 * Load presets from modules
 */
function listmixer_default_presets_load() {
  $methods = module_invoke_all('listmixer_default_preset');

  $presets = array();
  foreach ($methods as $method) {
    $presets[$method['preset_name']] = $method;
  }
  return $presets;
}