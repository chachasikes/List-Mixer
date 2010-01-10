// $Id$

/**
 * @file
 * This Javascript file is responsible for applying interactive behaviors and
 * elements to the appropriate html elements.
 *
 * 1. The interactive presets create an array on every Drupal page. listmixer.js 
 * looks for the html element that signals that a preset should be applies to
 * a page.
 * 
 * 2. If found, listmixer.js will proceed with applying elements. It will throw
 * errors to the user if they have defined incorrect markup.
 * 
 * The behaviors work as such:
 * 1. On load: most of the interactivity is set up, awaiting a trigger from user.
 * 2. Activate will apply the interactive elements to the page.
 * 3. Interact will collect an array of data that should be saved.
 * 4. Submit will trigger the data to be saved.
 * 5. Push triggers a callback function which sends the data to drupal.
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
          Drupal.behaviors.listmixer.listmixer_setup(preset);
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

Drupal.behaviors.listmixer.listmixer_setup = function(preset) {
    // *********** Set up target field (for node save function)
    // @TODO Add validation function if necessary
    preset.target_field = preset.interactions.interactions_target_field;
    // *********** Set up the target id
    // Make sure that the target id is a number  
    try {    
       preset.target_id = $(preset.interactions.interactions_target_id).html();
       preset.target_id.length > 0;
       $(preset.interactions.interactions_target_id).hide();
    }
    catch(err) {
      // @TODO If user has permissions to edit the preset, give them an error.
      alert(Drupal.t('ListMixer Interaction Preset Error: Target ID not a number or could not be found. Did you enter the right CSS Selector? Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      // @TODO Else, break out of this function  return false;
    }
    
    // *********** Set up target restrictions. 
    // Make sure it contains markup.  
    // If undefined, set to a default of 'html' (the whole page)      
    if (preset.interactions.interactions_restrictions === undefined) {
        preset.interactions.interactions_restrictions = 'body';
    }
    preset.interactions_restrictions = $(preset.interactions.interactions_restrictions).html();
    try {    
       preset.interactions_restrictions.length > 0;     
    }
    catch(err) {
      // @TODO If this is set to body, are there any other chances that this would be empty? This check maybe unnecessary for anything except debugging this JS file.
      alert(Drupal.t('ListMixer Error: Restricted selector not found. Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
    }
   
    // *********** Create interaction form and target classes
    preset.target_form_class = 'class="listmixer-target-form"';   
    preset.target_form_id = 'listmixer-target-'+ preset.preset_name;
    // @TODO Should form be a 'wrap()' function?
    preset.target_form = '<form id="' + preset.target_form_id + '" ' + preset.target_form_class + '></form>';
    preset.form = preset.target_form;
    preset.container = preset.interactions.interactions_container;
    
    // *********** Set up interactivity
    // This is restrictions here. If the user just wants a form field in block,
    // Then they need to set it to just the block. Default is 'body' so 
    // if nothing is entered, it will show up at the very bottom of the page.
            

    // Only one form is allowed, if the form should be applied to the restrictions container, but not
    // the container if the container is a child of the restrictions container.
    try {
      // Create the pointer to the container for where the form should be added.
      //var form_container;
      if (preset.interactions.interactions_container == preset.interactions.interactions_restrictions) {
        preset.form_container = preset.interactions.interactions_container;
      }
      else{
        preset.form_container = preset.interactions.interactions_restrictions + ':has(' + preset.interactions.interactions_container + ')';
      }

      // Make sure that the form container is valid.
      $(preset.form_container).length > 0;
      $(preset.form_container).prepend(preset.form);
      
      // If the interaction container matches the restriction container, make interactive elements live in the form. 
      // (looks better)
      
      
      // Set up selector for the source_id (for input values)
      preset.source_id_selector = preset.interactions.interactions_source_id;
      
      try {
        // Inclusions are the elements that will receive interactions.
        // Find all of the items that should act as a source of interaction.
        // EXAMPLE: div.views-field-field-photo-fid  a:regex(class, ^gallery-photo-)
        

        // Inclusions should be children of the restrictions.
        // The source selector needs to be a child of the element.
        // @TODO make the form into textfields and rearrange and rewrite the help.
                    
        $.each($(preset.interactions.interactions_restrictions + ' ' + preset.interactions.interactions_inclusions), function() {
          var Interact = new Drupal.behaviors.listmixer.Interact();
          Interact.init();
          var interactFunction = preset.behaviors.interact.settings.behavior_function;
          // @TODO check source_id is numeric
          // The selector might be empty if user enters nothing, if so, just use the default input.
          if(preset.source_id_selector != '') {
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
        alert(Drupal.t('ListMixer Error: Inclusion & input validation problem. Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      }      
    }
    catch(err) {
      alert(Drupal.t('ListMixer Error: Restrictions and Container conflict: admin/build/listmixer/' + preset.preset_id + ''));
    }
    // ********* Set up Submit button
    var Submit = new Drupal.behaviors.listmixer.Submit();
    Submit.init();
    var submitFunction = preset.behaviors.submit.settings.behavior_function;
    preset.submit = Submit.markup[submitFunction];         
    // Add button to form/containter
    $('form#' + preset.target_form_id).append(preset.submit);
    
    // *********** Handle help text
    preset.interactions_help = preset.interactions.interactions_help;
    // Append help text to interaction container.
    // *********** Handle interaction label
    preset.interactions_label = preset.interactions.interactions_label;
    $('form#' + preset.target_form_id).prepend('<div class="listmixer-interaction-help">' + preset.interactions_help + '</div>');
    $('form#' + preset.target_form_id).prepend('<div class="listmixer-interaction-label">' + preset.interactions_label + '</div>');
    // ********* Find the button (which might not be a button) and add a click function to it.
    
    // Set up data object on page load.
    preset.data = {
      'inputArray' : [],
      'input' : '',
      'target_id' : preset.target_id,
      'target_field' : preset.target_field
      // @TODO Collect other data here if necessary
    };
    // Activate push callback
    $('form#' + preset.target_form_id + ' div.listmixer-push-submit').children(".button").click(function() {
      Drupal.behaviors.listmixer.push(preset); 
    
      //@TODO make sure target_id is available to push function
      
      // If page stayed loaded, clear out the data array.
      preset.data = {
      'inputArray' : [],
      'input' : '',
      'target_id' : preset.target_id,
      'target_field' : preset.target_field
      }          
      // @TODO Change input val clearing.
      // $('form.listmixer-target-form div.listmixer-interact-input input').val('');
      
      // Do not reload page.
      // @TODO... actually the reloading can be nice. 
      // return false;
    });
}