<?php
// $Id$

/*
 *******************************************************************************
 * @file listmixer.hooks.inc
 * Hook implementations used by other modules
 *******************************************************************************
 */

/**
 * When a module contains a hook_listmixer_storage_register
 */
function listmixer_listmixer_storage_register_load() {
 $storage_methods = module_invoke_all('listmixer_storage_register');
 return $storage_methods;
}