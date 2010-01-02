// $Id$
Drupal.behaviors.listmixer = function() {
  // Read through each preset
  $.each(Drupal.settings.listmixer, function(){
    // If page contains a target block
    if(this.preset_method == 'listmixer_storage_nodes') {
      // Node target finding mechanism #1, The First
      // The view must contain .views-field-nid (generated by adding a field)
      // @TODO add a setting so user can specify the class/field that contains the node data. then they can put it whereever. let it be a full jQuery command.

      // Find the contents of an nid field, store it, and then hide it.
      $('#' + this.interactions.interactions_target_id).find('div.views-field-nid span.field-content').each(function(){
        this.target_nid = $(this).html();
      }).hide();      
      
      
      
      // @TODO: Look up with behaviors to apply to the page
      
      
      // @TODO: Look up which behaviors to load/apply to the target
      
      // @TODO: So the idea will be to build a library of buttons and things, and then load them based on the behavior settings.
      
      this.target_form_class = 'class="listmixer-target-form"';   
      this.target_form_id = 'listmixer-target-'+ this.preset_name;
      this.target_form = '<form id="' + this.target_form_id + '" ' + this.target_form_class + '></form>';
      this.interact = '<input></input>';
      this.submit = '<button>Save</button>';
      
      Drupal.behaviors.listmixer.push(this);
      
     // Add callbacks
      
      $('#' + this.interactions.interactions_target_id).append(this.target_form);

      $('#' + this.target_form_id).append(this.interact);
      
      // Add interact button (load js from interact button function)
      $('#' + this.target_form_id).append(this.submit);
      
      // @TODO: connect submit function to push callback and data
      
      // @TODO: add field spec to settings for behaviors
      
      
      
      // options:
      // if view content contains 'nid'...
      // http://11heavens.com/theming-Drupal-6-from-the-module-layer
      
      // semantic view
      // make user add markup with node id -- this ensure they have ultimate control * (definite option)
      // theme preprocess function all nodes add class listmixer-node-#nid
    }
  });
}
// Build functions that load the behaviors.
Drupal.behaviors.listmixer.activate = function(preset) {    
  Drupal.behaviors.listmixer.behaviorCreate(preset, 'activate');        
}

Drupal.behaviors.listmixer.interact = function(preset) {    
  Drupal.behaviors.listmixer.behaviorCreate(preset, 'interact');        
}

Drupal.behaviors.listmixer.push = function(preset) {    
  Drupal.behaviors.listmixer.behaviorCreate(preset, 'push');        
}

Drupal.behaviors.listmixer.submit = function(preset) {    
  Drupal.behaviors.listmixer.behaviorCreate(preset, 'submit');        
}
// Load javascript includes, set up the callbacks for all behaviors.
Drupal.behaviors.listmixer.behaviorCreate = function(preset, type) {
  var preset = preset;
  var type = type;
  var preset_id = preset.preset_id;
  var callback;
  var javascript_include;
  var behavior_name;
  // Create an array of the settings for the current behavior.
  var behavior = preset.behaviors[type];
  callback = Drupal.settings.basePath + behavior.settings.behavior_callback;
  javascript_include = behavior.settings.behavior_javascript;
  behavior_name =  behavior.settings.behavior_name;

  // Load data from settings array contained in each behavior.
  // @TODO a callback is called. a menu item figures out who the callback is for, looks up the registry and calls the appropriate function.
  // Grab data from somewhere that's stored somewhere else.
  // The data might need to be cleaned up if the funciton is used several times before submitting
  
  var data_label = 'data_' + behavior_name;
  //$(this).attr('drag_list_value')
  //var data = {data_label : 'test data content'};
  var data = { name: "John", time: "2pm" };
  
  // Load javascript include for this behavior.
  if(!empty(javascript_include)) {
    $.getScript(javascript_include);
  }
  // Ajax call to callback for this behavior.
  // @TODO currently this runs automatically, make push happen after submit behavior is activated.

  if(!empty(callback)) {
    $.post(callback, data, Drupal.behaviors.listmixer.redirect(preset, data));
  }
  return false; 
}

Drupal.behaviors.listmixer.redirect = function(preset, data) {
  var preset = preset;
  var data = data;  
  return false;  
}