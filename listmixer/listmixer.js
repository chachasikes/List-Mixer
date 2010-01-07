// $Id$
// @file
/**
 *
 @TODO Rewrite this outline of the code.
 */
// Connect behaviors

// on load: set up everything needed
// on activate, allow interact
// on interact, allow submit
// on submit, do push
// on push feedback, update markup

//if activate is set to none, allow interact
//if interact is set to none, ?? then what?
//if submit is set to none, ?? there needs to be some sort of default
// if push is set to none, ?? 

// rules
// there is always an activate button. it is off by default always.
// make a type of activate which is 'onmouseclick' of whatever the interact button is
// otherwise, allow for an actual button to be set.

// interact - there is always something. the default will be tied to the push type?
// interact ties an interaction method to a push type. so, given a class of something, it reads it and scrapes the data to prep it for push

// push - there's no use to having push except for testing.
// push takes data from interact and stores it in the right format
// to store a nid - you could select it ('123') you could add checkboxes next to all available nids on a page, you could enter the number, you could click a link

// in the settings for the preset - make fields that will contain the jquery that will say where everything should go

// for example: 

/**
 * Order of execution
 * 
 * The page loads.
 * For each preset, behavior libraries are loaded.
 * Using a callback for each preset behavior, load and render markup (buildCallback)
 * When an action is taken, send data to be processed, and return new markup (submitCallback)
 *
 */

var pageLoaded = 0;

Drupal.behaviors.listmixer = function() {
  if (pageLoaded == 0) {
    // Read through each preset and set up the first time the page is loaded.
    $.each(Drupal.settings.listmixer, function() {
      // If interaction involves saving content to target nodes.
      if (this.preset_method == 'listmixer_storage_nodes') {
        var preset = this;
        // *********** @TODO: Clear data on all page loads
        // *********** Set up behaviors.
        Drupal.behaviors.listmixer.interact(this);
        Drupal.behaviors.listmixer.activate(this);     
        Drupal.behaviors.listmixer.submit(this);  
        // ************ Use variables Set by user
        // Make sure that a container is found. 
        // This should be done first, as nothing else will happen if there is no container on the page.
        var interactions_container = $.find(this.interactions.interactions_container);
        // Interaction container not found, do nothing, other wise, proceed.
        if (interactions_container == '') {
          // No container found, do nothing. Go find the next preset.
          // @TODO return false was escaping the each() loop completely.
        }
        else {
          // *********** Set up target field (for node save function)
          // @TODO Add validation function if necessary
          var target_field = this.interactions.interactions_target_field;
          // *********** Set up the target id
          // Make sure that the target id is a number  
          try {    
             var target_id = $(this.interactions.interactions_target_id).html();
             target_id.length > 0;
             $(this.interactions.interactions_target_id).hide();
          }
          catch(err) {
            alert(Drupal.t('ListMixer Error: Target ID not a number or could not be found. Edit preset: admin/build/listmixer/' + this.preset_id + ''));
          }
          
          // *********** Set up target restrictions. 
          // Make sure it contains markup.  
          // If undefined, set to a default of 'html' (the whole page)      
          if (this.interactions.interactions_restrictions === undefined) {
              this.interactions.interactions_restrictions = 'body';
          }
          var interactions_restrictions = $(this.interactions.interactions_restrictions).html();
          try {    
             interactions_restrictions.length > 0;     
          }
          catch(err) {
            alert(Drupal.t('ListMixer Error: Restrictions Edit preset: admin/build/listmixer/' + this.preset_id + ''));
          }
         
          // *********** Create interaction form and target classes
          this.target_form_class = 'class="listmixer-target-form"';   
          this.target_form_id = 'listmixer-target-'+ this.preset_name;
          // @TODO Should form be a 'wrap()' function?
          this.target_form = '<form id="' + this.target_form_id + '" ' + this.target_form_class + '></form>';
          var form = this.target_form;
          var container = this.interactions.interactions_container;
          
          // *********** Set up interactivity
          // This is restrictions here. If the user just wants a form field in block,
          // Then they need to set it to just the block. Default is 'body' so 
          // if nothing is entered, it will show up at the very bottom of the page.
                  
  
          // Only one form is allowed, if the form should be applied to the restrictions container, but not
          // the container if the container is a child of the restrictions container.
          try {
            // Create the pointer to the container for where the form should be added.
            var form_container;
            if (this.interactions.interactions_container == this.interactions.interactions_restrictions) {
              form_container = this.interactions.interactions_container;
            }
            else{
              form_container = this.interactions.interactions_restrictions + ':has(' + this.interactions.interactions_container + ')';
            }
  
            // Make sure that the form container is valid.
            $(form_container).length > 0;
            $(form_container).prepend(form);
            
            // If the interaction container matches the restriction container, make interactive elements live in the form. 
            // (looks better)
            
            
            // Set up selector for the source_id (for input values)
            var source_id_selector = this.interactions.interactions_source_id;
            
            try {
              // Inclusions are the elements that will receive interactions.
              // Find all of the items that should act as a source of interaction.
              // EXAMPLE: div.views-field-field-photo-fid  a:regex(class, ^gallery-photo-)
              
  
              // Inclusions should be children of the restrictions.
              // The source selector needs to be a child of the element.
              // @TODO make the form into textfields and rearrange and rewrite the help.
                          
              $.each($(this.interactions.interactions_restrictions + ' ' + this.interactions.interactions_inclusions), function() {
                var Interact = new Drupal.behaviors.listmixer.Interact();
                Interact.init();
                var interactFunction = preset.behaviors.interact.settings.behavior_function;
                // @TODO check source_id is numeric
                // The selector might be empty if user enters nothing, if so, just use the default input.
                if(source_id_selector != '') {
                  // Get each source id
                  var source_id = $(this).find(source_id_selector).html();
                  // Hide the source selector. (@TODO, make this an option)
                  $(this).find(source_id_selector).hide();
                  if(source_id != null) {
                    // Only add interactive elements if a valid value is present.
                    $(this).prepend(Interact.markup[interactFunction]);
                  }
                }
                else{
                  $(this).prepend(Interact.markup[interactFunction]);
                }  
                // Add value to input field after input is created
                $(this).find('input').val(source_id);       
              });
            }
            catch(err) {
              alert(Drupal.t('ListMixer Error: Inclusion & input validation problem. Edit preset: admin/build/listmixer/' + this.preset_id + ''));
            }      
          }
          catch(err) {
            alert(Drupal.t('ListMixer Error: Restrictions and Container conflict: admin/build/listmixer/' + this.preset_id + ''));
          }
          // ********* Set up Submit button
          var Submit = new Drupal.behaviors.listmixer.Submit();
          Submit.init();
          var submitFunction = preset.behaviors.submit.settings.behavior_function;
          this.submit = Submit.markup[submitFunction];         
          // Add button to form/containter
          $('form#' + this.target_form_id).append(this.submit);
          
          // *********** Handle help text
          var interactions_help = this.interactions.interactions_help;
          // Append help text to interaction container.
          // *********** Handle interaction label
          var interactions_label = this.interactions.interactions_label;
          $('form#' + this.target_form_id).prepend('<div class="listmixer-interaction-help">' + interactions_help + '</div>');
          $('form#' + this.target_form_id).prepend('<div class="listmixer-interaction-label">' + interactions_label + '</div>');
          // ********* Find the button (which might not be a button) and add a click function to it.
          
          // Set up data object on page load.
          this.data = {
            'inputArray' : [],
            'input' : '',
            'target_id' : target_id,
            'target_field' : target_field
            // @TODO Collect other data here if necessary
          };
          // Activate push callback
          $('form#' + this.target_form_id + ' div.listmixer-push-submit').children(".button").click(function() {
            Drupal.behaviors.listmixer.push(preset); 
          
            //@TODO make sure target_id is available to push function
            
            // If page stayed loaded, clear out the data array.
            preset.data = {
            'inputArray' : [],
            'input' : '',
            'target_id' : target_id,
            'target_field' : target_field
            }          
            // @TODO Change input val clearing.
            // $('form.listmixer-target-form div.listmixer-interact-input input').val('');
            
            // Do not reload page.
            // @TODO... actually the reloading can be nice. 
            // return false;
          });
        } // else
      }
    });
  }
  // Increment the pageLoaded variable everytime this function is called (usually on page load)
  pageLoaded++;
}
// ******* Build functions that load the behaviors.
// Load javascript behavior libraries.
// Interact is called when elements are being applied to a container.
Drupal.behaviors.listmixer.interact = function(preset) {    
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'interact');      
}
// @TODO Set up activate buttons, only Mousedown works at the moment.
Drupal.behaviors.listmixer.activate = function(preset) {    
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'activate');
  var Activate = new Drupal.behaviors.listmixer.Activate();
  Activate.init();         
}
// Submit called when form is created and added to container.
Drupal.behaviors.listmixer.submit = function(preset) {    
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'submit');
}
// Push is called when user interacts with submit button
Drupal.behaviors.listmixer.push = function(preset) { 
  var Push = new Drupal.behaviors.listmixer.Push();
  Push.init(); 
  // Load data for interact button validation  
  var Interact = new Drupal.behaviors.listmixer.Interact();
  Interact.init();
  var interactFunction = preset.behaviors.interact.settings.behavior_function;  
 
  // Get value from interact element 
  // @TODO Add validators :checked, not empty... what else?
  $.each($(preset.interactions.interactions_restrictions + ' ' + Interact.validation[interactFunction]), function(){
    // Collect the value from each of the interactive elements.
    // Store values in data object in preset.
    preset.data.inputArray.push($(this).val());
  });  
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'push'); 

  // @TODO Check that the callback isn't reloading the page. 
  return false;  
}
// ******* Load javascript includes, set up the callbacks for all behaviors.
Drupal.behaviors.listmixer.behaviorBuildCallback = function(preset, type) {
  var preset = preset;
  var type = type;
  var preset_id = preset.preset_id;
  var callback;
  var behavior_name;
  var behavior_function;
  // Create an array of the settings for the current behavior.
  var behavior = preset.behaviors[type];
  if (behavior.settings != null) {
    callback = behavior.settings.behavior_callback;
    behavior_function = behavior.settings.behavior_function;
    behavior_name =  behavior.settings.behavior_name;

    // Load data from settings array contained in each behavior.
    // @TODO a callback is called. a menu item figures out who the callback is for, looks up the registry and calls the appropriate function.
    // Grab data from somewhere that's stored somewhere else.
    // The data might need to be cleaned up if the funciton is used several times before submitting  
    // Ajax call to callback for this behavior.
    // @TODO currently this runs automatically, make push happen after submit behavior is activated.
    if (callback != null) {
      if (type == 'push') {
        if (preset.data.inputArray.length > 0) {
          preset.data.input = preset.data.inputArray.toString();
        }
      }
      $.ajax({
        type: "POST",
        url: callback,
        data: preset.data,
        complete: Drupal.behaviors.listmixer.redirect(preset, preset.data),
      });
      return false;
    }
  }
  return false;
}
// Load javascript includes, set up the callbacks for all behaviors.
Drupal.behaviors.listmixer.behaviorSubmitCallback = function(preset, type) {
  var preset = preset;
  var type = type;
  var preset_id = preset.preset_id;
  var callback;
  var behavior_name;
  var behavior_function;
  // Create an array of the settings for the current behavior.
  var behavior = preset.behaviors[type];
  if (behavior.settings != null) {
    // @TODO rename _redirect to _submit_callback, and _callback to _build_callback
    callback = behavior.settings.behavior_redirect;
    behavior_name =  behavior.settings.behavior_name;

    // Load data from settings array contained in each behavior.
    // @TODO a callback is called. a menu item figures out who the callback is for, looks up the registry and calls the appropriate function.
    // Grab data from somewhere that's stored somewhere else.
    // The data might need to be cleaned up if the funciton is used several times before submitting  
    //var data_label = 'data_' + behavior_name;
    //$(this).attr('drag_list_value')
    var data = {data_label : 'test data content'};
       
    // Ajax call to callback for this behavior.
    // @TODO currently this runs automatically, make push happen after submit behavior is activated.
    if (callback != null) {
      $.post(callback, data, Drupal.behaviors.listmixer.redirect(preset, preset.data));
    }
  }
  return false; 
}    
Drupal.behaviors.listmixer.Behavior = function() { 
  // Create new object stored in include file.
  var Behavior = new Behavior();
  //Behavior.init();
  //return Behavior;
  return false;
}
Drupal.behaviors.listmixer.redirect = function(preset, data) {
  var preset = preset;
  var data = data;  
  // Get the returned javascript from the function and apply it wherever it is supposed to go
  // @TODO: maybe - Calling the redirect function, which returns $output?

  return false;  
}
// ******* Make jQuery regex expression available 
// http://james.padolsey.com/javascript/regex-selector-for-jquery/
jQuery.expr[':'].regex = function(elem, index, match) {
    var matchParams = match[3].split(','),
        validLabels = /^(data|css):/,
        attr = {
            method: matchParams[0].match(validLabels) ? 
                        matchParams[0].split(':')[0] : 'attr',
            property: matchParams.shift().replace(validLabels,'')
        },
        regexFlags = 'ig',
        regex = new RegExp(matchParams.join('').replace(/^\s+|\s+$/g,''), regexFlags);
    return regex.test(jQuery(elem)[attr.method](attr.property));
}