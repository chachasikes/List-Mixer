<?php
// $Id$

/**
 * @file listmixer_ui.behaviors.inc
 * Much of this module was based on the structure for creating presets in listmixer
 */
 
 
 
/*

for each allowed behavior (admin/settings/listmixer)
if module exists, load include for push behavior
create callback for the push behavior
inc adds js for the behavior
javascript contains transformation from data to form

add utlities for behaviors (php,js)


*/

/**
 * When a module contains a hook_listmixer_behavior_register
 *(for storing which behavior should be used.)
 */
function listmixer_behavior_register_load() {
 /*$methods = module_invoke_all('listmixer_behavior_register');
 $behaviors = array();
 foreach ($methods as $method) {
   $behaviors[$method['module']] = $method['name'];
 }
 return $behaviors;*/
}

/**
  
  push all data to node form

 */
function listmixer_behavior_push_load($data) {
/* $methods = module_invoke_all('listmixer_push');
 $behaviors = array();
 foreach ($methods as $method) {
   $behaviors[$method['module']] = $method['name'];
 }
 return $behaviors;*/
}

/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_behaviors_load($preset = NULL) {

}

 