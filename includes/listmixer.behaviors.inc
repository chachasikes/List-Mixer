<?php
// $Id$

/**
 * @file listmixer_ui.behaviors.inc
 * Much of this module was based on the structure for creating presets in listmixer
 */
 
/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_behaviors_load_form($preset = NULL) {

  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Behaviors'),
    '#tree' => TRUE,
    '#weight' => 8,
   // '#theme' => 'listmixer_ui_preset_behaviors',
  );

  $form['activate'] = array(
    '#type' => 'select',
    '#title' => t('Activate'),
    '#default_value' => $preset['behaviors']['activate']['behaviorname'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'activate'),
    '#description' => t('Choose activate behaviors.'),
  );

  $form['interact'] = array(
    '#type' => 'select',
    '#title' => t('Interact'),
    '#default_value' => $preset['behaviors']['interact']['behaviorname'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'interact'),
    '#description' => t('Choose interact behaviors.'),
  );

  $form['push'] = array(
    '#type' => 'select',
    '#title' => t('Push'),
    '#default_value' => $preset['behaviors']['push']['behaviorname'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'push'),
    '#description' => t('Choose push behaviors.'),
  );
  
  /*  
  @TODO: Test that submit isn't a reserved word.
    $form['submit'] = array(
    '#type' => 'select',
    '#title' => t('Submit'),
    '#default_value' => $preset['behaviors']['submit']['behaviorname'],
    '#options' => listmixer_behaviors_load_form_options($preset, 'submit'),
    '#description' => t('Choose submit behaviors.'),
  );  
  */
  return $form;
} 
 
 
/**
 * Create options list of types of behaviors to select from.
 */
function listmixer_behaviors_load_form_options($preset = NULL, $type) {

  /**
   * Includes
   * 
   * @TODO: Read through behaviors directory and dynamically include any .inc files
   * OR - I think this is better:
   * @TODO: Create a registry array that looks for a module name, function enabled and if it exists and settings set, make the behavior available.
   *
   * For now, just including the few include files that will actually do anything.
   */ 
   
  
  // @TODO: Load admin setting for each type of module.
  // @TODO: The registry will probably need to be a table then.
  // @TODO: It will need to be rebuilt when modules page is updated and when admin settings are changed. And if people add new behaviors.
  
  
  // @TODO: Add this to the listmixer install database schema
  $admin_setting = TRUE;
  $listmixer_behaviors_registry = array();
  
  $listmixer_behaviors_registry[] = array(
      'behaviorname' => 'nodereference',
      'name' => t('Content: Nodereference'),
      'enabled' => $admin_setting, 
      'type' => 'push',
      'include' => 'behaviors/push/content/nodereference/listmixer_push_nodereference.inc',
  );
  $listmixer_behaviors_registry[] = array(
      'behaviorname' => 'link',
      'name' => t('Content: Link'),
      'enabled' => $admin_setting, 
      'type' => 'push',
      'include' => 'behaviors/push/content/link/listmixer_push_link.inc',
  );    
  $listmixer_behaviors_registry[] = array(
      'behaviorname' => 'button',
      'name' => t('Button'),
      'enabled' => $admin_setting, 
      'type' => 'activate',
      'include' => 'behaviors/activate/button/listmixer_activate_button.inc',
  );    
  $listmixer_behaviors_registry[] = array(
      'behaviorname' => 'click',
      'name' => t('Click Links'),
      'enabled' => $admin_setting, 
      'type' => 'interact',
      'include' => 'behaviors/interact/click/listmixer_interact_click.inc',
  ); 


  // @TODO: Load behaviors from the behavior registry table
  // @TODO: Add enable/disable options to admin page for listmixer
  // @TODO: Return list of selectable functions as options
  
  // @TODO: Remove this array when registry is set up.
  $listmixer_active_behaviors = $listmixer_behaviors_registry;
  
  $behaviors_options = array();
  
  foreach ($listmixer_active_behaviors as $behavior) {
    // Push behavior information into array
    if($type == $behavior['type']) {
      //$option = array($behavior['behaviorname'] => $behavior['name']);
      $behaviors_options[$behavior['behaviorname']] =  $behavior['name'];
    }
  }
  return $behaviors_options;
}
 
 
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



 