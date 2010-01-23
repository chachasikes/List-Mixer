// $Id$

/**
 * @file
 * This Javascript file is responsible for applying interactive behaviors and
 * elements to the appropriate html elements.
 *
 * 1. The interactive presets create an array on every Drupal page. listmixer.js 
 * looks for the html element that signals that a preset should be applied to
 * a page.
 * 
 * 2. If found, listmixer.js will proceed with applying elements. It will throw
 * errors to the user if they have defined incorrect markup.
 * @TODO Make the errors only display to users with privileges 
 * to create presets.
 * 
 * The behaviors work as such:
 * 1. On load: most of the interactivity is set up, awaiting 
 * a trigger from user.
 * 2. Activate will apply the interactive elements to the page.
 * 3. Interact will collect an array of data that should be saved.
 * 4. Submit will trigger the data to be saved.
 * 5. Push triggers a callback function which sends the data to Drupal.
 * 
 * @TODO: Make this file camelCase: http://drupal.org/node/172169
 * This will be a little tricky because of all the stuff that comes from PHP
  
  "Variables added through drupal_add_js() should also be lowerCamelCased, 
  so that they can be consistent with other variables once they are used in JavaScript."


 * please tell me.
 * @TODO: Clear data on all page loads
 * @TODO: Make themeable output exist in Drupal.theme

    DEFINE IT:
    Drupal.theme.prototype.powered = function(color, height, width) {
      return '<img src="/misc/powered-'+ color +'-'+ height +'x'+ width +'.png" />";
    }

    CALL IT:
    $('.footer').append(Drupal.theme('powered', 'black', 135, 42));

    OVERRIDE IT:
    Drupal.theme.prototype.powered = function(color, height, width) {
      return '<img src="/sites/all/themes/powered_images/powered-'+ color +'-'+ height +'x'+ width

    +'.png" />";
    }
 */

var pageLoaded = 0;
/**
 * Set up listmixer if main interaction container is on the rendered page.
 */
Drupal.behaviors.listmixer = function() {
  if (pageLoaded === 0) {
    // Read through each preset and set up the first time the page is loaded.
    $.each(Drupal.settings.listmixer, function() {
      // If interaction involves saving content to target nodes.
      if (this.preset_method == 'listmixer_storage_nodes') {
        var preset = this;
        // *********** Set up behaviors.
        Drupal.behaviors.listmixer.interact(this);
        Drupal.behaviors.listmixer.activate(this);
        Drupal.behaviors.listmixer.submit(this);
        // ************ Use variables set by user.
        // Make sure that a container is found. 
        // This should be done first, as nothing else will happen if there is no container on the page.
        var interactionsContainerExists = $.find(this.interactions.interactions_container);
        // Interaction container not found, do nothing, other wise, proceed.
        if (interactionsContainerExists == '') {
          // No container found, do nothing. Go find the next preset.
          // @TODO return false was escaping the each() loop completely.
        }
        else {
          Drupal.behaviors.listmixer.listmixerSetup(preset);
        }
      }
    });
  }
  // Increment the pageLoaded variable everytime this function is 
  // called (usually on page load.)
  pageLoaded++;
};
// ******* Build functions that load the behaviors.
// Load javascript behavior libraries.
/**
 * Interact is called when elements are being applied to a container.
 */
Drupal.behaviors.listmixer.interact = function(preset) {
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'interact');
};
/**
 * Activate is called from the setup function.
 */
Drupal.behaviors.listmixer.activate = function(preset) {
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'activate');
  var Activate = new Drupal.behaviors.listmixer.activateBehavior();
  Activate.init();
};
/**
 * Submit called when form is created and added to container.
 */
Drupal.behaviors.listmixer.submit = function(preset) {
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'submit');
};
/**
 * Push is called when user interacts with submit button.
 */
Drupal.behaviors.listmixer.push = function(preset) {
  var Push = new Drupal.behaviors.listmixer.pushBehavior();
  Push.init();
  // Load data for interact button validation.
  var Interact = new Drupal.behaviors.listmixer.interactBehavior();
  Interact.init();
  preset.interactFunction = preset.behaviors.interact.settings.behavior_function; 
  // Get value from interact element.
console.log(Interact.validation[preset.interactFunction]);
  $.each($(preset.interactions.interactions_region + ' ' + Interact.validation[preset.interactFunction]), function(){
    // Collect the value from each of the interactive elements.
    // Store values in data object in preset.
    preset.data.inputArray.push($(this).val());
    console.log(preset.data);
  });
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'push');
  // @TODO Check that the callback isn't reloading the page. 
  return false;
};
/**
 * Load javascript includes, set up the callbacks for all behaviors.
 */
Drupal.behaviors.listmixer.behaviorBuildCallback = function(preset, type) {
  var presetId = preset.preset_id;
  var callback;
  var behaviorName;
  var behaviorFunction;
  // Create an array of the settings for the current behavior.
  var behavior = preset.behaviors[type];
  if (behavior.settings !== null) {
    callback = behavior.settings.behavior_callback;
    behaviorFunction = behavior.settings.behavior_function;
    behaviorName =  behavior.settings.behavior_name;

    // Load data from settings array contained in each behavior.
    // @TODO a callback is called. a menu item figures out who the callback is for, looks up the registry and calls the appropriate function.
    // Grab data from somewhere that's stored somewhere else.
    // The data might need to be cleaned up if the funciton is used several times before submitting  
    // Ajax call to callback for this behavior.
    // @TODO currently this runs automatically, make push happen after submit behavior is activated.
    if (callback !== null) {
      if (type == 'push') {
        if (preset.data.inputArray.length > 0) {
          preset.data.input = preset.data.inputArray.toString();
        }
      }
      $.ajax({
        type: "POST",
        url: callback,
        data: preset.data,
        complete: Drupal.behaviors.listmixer.redirect(preset, preset.data)
      });
      return false;
    }
  }
  return false;
};
/**
 * Load javascript includes, set up the callbacks for all behaviors.
 */
Drupal.behaviors.listmixer.behaviorSubmitCallback = function(preset, type) {
  var presetId = preset.preset_id;
  var callback;
  var behaviorName;
  var behaviorFunction;
  // Create an array of the settings for the current behavior.
  var behavior = preset.behaviors[type];
  if (behavior.settings !== null) {
    // @TODO rename _redirect to _submit_callback, and _callback to _build_callback
    callback = behavior.settings.behavior_redirect;
    behaviorName =  behavior.settings.behavior_name;

    // Load data from settings array contained in each behavior.
    // @TODO a callback is called. a menu item figures out who the callback is for, looks up the registry and calls the appropriate function.
    // Grab data from somewhere that's stored somewhere else.
    // The data might need to be cleaned up if the funciton is used several times before submitting
    //var data_label = 'data_' + behavior_name;
    //$(this).attr('drag_list_value')
    var data = {data_label : 'test data content'};
       
    // Ajax call to callback for this behavior.
    // @TODO currently this runs automatically, make push happen after submit behavior is activated.
    if (callback !== null) {
      $.post(callback, data, Drupal.behaviors.listmixer.redirect(preset, preset.data));
    }
  }
  return false;
};
/**
 * Do something on redirect (placeholder)
 */
Drupal.behaviors.listmixer.redirect = function(preset, data) {
  return false;
};
/**
 * Set up listmixer interactivity based on presets created by user.
 * 1. Set up target field (for node save function.)
 * 2. Set up target region.
 * 3. Set up interactivity.
 *
 * @TODO Add validation function if necessary
 * @TODO Break this script into smaller functions.
 */
Drupal.behaviors.listmixer.listmixerSetup = function(preset) {
    // Set up target field (for node save function.)
    preset.targetField = preset.interactions.interactions_target_field;
    // Set up the target value
    preset.targetValueAttribute = preset.interactions.interactions_target_id_attr;
    try {
      // If an attribute has been set by user, get the value.
      if(preset.targetValueAttribute !== '') {
         preset.targetId = $(preset.interactions.interactions_target_id).attr(preset.targetValueAttribute);
      }
      else {
         preset.targetId = $(preset.interactions.interactions_target_id).html();
         $(preset.interactions.interactions_target_id).hide();
      }
      // Make sure that the target id has a value
      if(preset.targetId.length > 0) {
      }
      else {
        throw 'error';
      }
    }
    catch(err) {
      // @TODO If user has permissions to edit the preset, give them an error.
      alert(Drupal.t('ListMixer Interaction Preset Error: Target Value could not be found. Did you enter the right CSS Selector for "' + preset.preset_name + '"? Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      // @TODO Else, break out of this function  return false;
    }

    // Set up target region.
    // Make sure it contains markup.
    // If undefined, set to a default of 'body.'
    if (preset.interactions.interactions_region === undefined) {
        preset.interactions.interactions_region = 'body';
    }
    preset.interactionsRegion = $(preset.interactions.interactions_region).html();
    try {
      // if(preset.interactionsRegion.length > 0;
      if(preset.interactionsRegion.length > 0) {
      }
      else {
        throw 'error';
      }
    }
    catch(err1) {
      // @TODO If this is set to body, are there any other chances that this would be empty? This check maybe unnecessary for anything except debugging this JS file.
      alert(Drupal.t('ListMixer Error: Interactive region not found. Did you enter the right CSS Selector for "' + preset.preset_name + '"? Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
    }

    // *********** Create interaction form and target classes
    preset.targetFormClass = 'class="listmixer-target-form"';
    preset.targetFormId = 'listmixer-target-'+ preset.preset_name;
    // @TODO Should form be a 'wrap()' function?
    // @TODO Should this be available to Drupal theme? It's pretty important and shouldn't be messed with.
    preset.targetForm = '<form id="' + preset.targetFormId + '" ' + preset.targetFormClass + '></form>';
    preset.form = preset.targetForm;
    preset.container = preset.interactions.interactions_container;

    // Set up interactivity.
    // This is region here. If the user just wants a form field in block,
    // Then they need to set it to just the block. Default is 'body' so 
    // If nothing is entered, it will show up at the top of the page.
    // Only one form is allowed, if the form should be applied to the 
    // region container, but not the container if the container is a 
    // child of the region container.
    // console.log('target container: ' + preset.interactions.interactions_container);
    try {
      // Create the pointer to the container for where the form should be added.
      // If the main container is the same as the interactive region, apply the form to the main container.
      if (preset.interactions.interactions_container === preset.interactions.interactions_region) {
        preset.formContainer = preset.interactions.interactions_container;
      }
      // There is some trickiness to how the form container is determined.
      // Currently, the form container is attached to the most external element, if it has the region.
      else{
        preset.formContainer = preset.interactions.interactions_container + ':has(' + preset.interactions.interactions_region + ')';       
      }
      // Make sure that the form container is valid.
      $(preset.formContainer).length > 0;
      // Set up form.
      Drupal.behaviors.listmixer.setupForm(preset);
      // Create activate behavior, or load straightaway if set to onLoad
      // @TODO Change 'loadActivate' to 'onLoad' 
      if (preset.behaviors.activate.settings.behavior_function == 'loadActivate') {
        preset.activation = true;
        Drupal.behaviors.listmixer.listmixerActivate(preset);
      }
      else {
        // Add activate widget.
        //Drupal.behaviors.listmixer.listmixerActivate(preset, true);
        preset.activation = false;
        Drupal.behaviors.listmixer.setupActivateWidget(preset);
      }
    }
    catch(err3) {
      alert(Drupal.t('ListMixer Error: Interactive region and main container conflict: admin/build/listmixer/' + preset.preset_id + ''));
    }
};
/**
 * Set up interaction form.
 */
Drupal.behaviors.listmixer.setupForm = function(preset) {
  $(preset.formContainer).prepend(preset.form);
  // *********** Handle help text
  preset.interactionsHelp = preset.interactions.interactions_help;
  // Append help text to interaction container.
  // *********** Handle interaction label
  preset.interactionsLabel = preset.interactions.interactions_label;
  $('form#' + preset.targetFormId).prepend('<div class="listmixer-interaction-help">' + preset.interactionsHelp + '</div>');
  $('form#' + preset.targetFormId).prepend('<div class="listmixer-interaction-label">' + preset.interactionsLabel + '</div>');
};
/**
 * Add activate widget.
 */
Drupal.behaviors.listmixer.setupActivateWidget = function(preset) {
  // @TODO Work on declaring decactivated, can't use === operator as is
  // On activate widget click, set up the interaction.
  var Activate = new Drupal.behaviors.listmixer.activateBehavior();
  Activate.init();
  var activateFunction = preset.behaviors.activate.settings.behavior_function;
  preset.activate = Activate.markup[activateFunction];
  // Add activate button to form.
  $('form#' + preset.targetFormId).append(Activate.markup[activateFunction]);
  // Hide deactivate button.
  $('form#' + preset.targetFormId + ' div.listmixer-deactivate-button').hide();
  $('form#' + preset.targetFormId + ' div.listmixer-activate-button').children(".button").click(function() {
    if(preset.activated == null) {
      preset.activation = true;
      Drupal.behaviors.listmixer.listmixerActivate(preset);
      preset.activated = true;
      preset.deactivated = null;
      $('form#' + preset.targetFormId + ' div.listmixer-deactivate-button').show();
      $('form#' + preset.targetFormId + ' div.listmixer-activate-button').hide();
    }
    return false;
  });
  // Set up deactivate button.
  $('form#' + preset.targetFormId + ' div.listmixer-deactivate-button').children(".button").click(function() {
    if(preset.deactivated == null) {
      preset.activation = false;
      Drupal.behaviors.listmixer.listmixerDeactivate(preset);
      preset.deactivated = true;
      preset.activated = null;
      $('form#' + preset.targetFormId + ' div.listmixer-deactivate-button').hide();
      $('form#' + preset.targetFormId + ' div.listmixer-activate-button').show();
      return false;
    }
  });
  // Set deactivate on initial load.
 $('form#' + preset.targetFormId + ' div.listmixer-deactivate-button').children(".button").trigger('click');
};
/**
 * Deactivate function.
 */
Drupal.behaviors.listmixer.listmixerDeactivate = function(preset) {
  preset.activation = false;
  Drupal.behaviors.listmixer.listmixerActivate(preset);
};
/**
 *
 */
Drupal.behaviors.listmixer.listmixerActivate = function(preset) {
  // If the interaction container matches the restriction container, make interactive elements live in the form. 
  var hideSourceValue = false;
  // Set up selector for the sourceValue (for input values)
  preset.sourceValueSelector = preset.interactions.interactions_source_id;
  preset.sourceValueAttribute = preset.interactions.interactions_source_id_attr;
  try {
    // Inclusions are the elements that will receive interactions.
    // Find all of the items that should act as a source of interaction.
    // EXAMPLE: div.views-field-field-photo-fid  a:regex(class, ^gallery-photo-)
    // Inclusions should be children of the region.
    // The source selector needs to be a child of the element.
    // @TODO make the form into textfields and rearrange and rewrite the help.

    var Interact = new Drupal.behaviors.listmixer.interactBehavior();
    Interact.init();
    preset.interactFunction = preset.behaviors.interact.settings.behavior_function;
    // @TODO See if there is any possible way to get this function to load.
    // Otherwise, maybe store the function in the php??
    if (preset.interactFunction == 'sortInteract') {
      Interact.sortInteract(preset);
    }

    $.each($(preset.interactions.interactions_region + ' ' + preset.interactions.interactions_inclusions), function() {
      var sourceValue = null;
      var sourceElement = null;
      var Interact = new Drupal.behaviors.listmixer.interactBehavior();
      Interact.init();
      var sourceValueMarkup = 'div.listmixer-source-value';
      var sourceValueMarkupProcessed = 'processed-value-' + preset.preset_name;
      preset.interactFunction = preset.behaviors.interact.settings.behavior_function;

      // @TODO check sourceValue is numeric
      // The selector might be empty if user enters nothing, if so, just use the default input.
      if(preset.sourceValueSelector != '') {
        if(preset.sourceValueSelector == preset.interactions.interactions_inclusions) {
          sourceElement = $(this);
        }
        else {
          sourceElement = $(this).find(preset.sourceValueSelector);
        }
        // Get each source id
        if(preset.sourceValueAttribute !== '') {
          sourceValue = sourceElement.attr(preset.sourceValueAttribute);
        }
        else {
          sourceValue = sourceElement.html();
        }
        // Hide the source selector. (@TODO, make this an option)
        if(hideSourceValue === true) {
          sourceElement.hide();
        }
        if(sourceValue !== null) {
          // Only add interactive elements if a valid value is present.
          if(preset.activation === true) {
            $(this).addClass(sourceValueMarkupProcessed);
            $(this).prepend(Interact.markup[preset.interactFunction]);
            $(this).find(sourceValueMarkup).addClass(sourceValueMarkupProcessed);
          }
          else{
            $(this).removeClass(sourceValueMarkupProcessed);
            $(this).find(sourceValueMarkup).remove();
          }
        }
      }
      else{
        // Only add interactive elements if a valid value is present.
        if(preset.activation === true) {
          $(this).addClass(sourceValueMarkupProcessed);
          $(this).append(Interact.markup[preset.interactFunction]);
          $(this).find(sourceValueMarkup).addClass(sourceValueMarkupProcessed);
        }
        else{
          $(this).removeClass(sourceValueMarkupProcessed);
          $(this).find(sourceValueMarkup).remove();
        }
      }
      // Add value to input field after input is created
      $(this).find('*.' + sourceValueMarkupProcessed + ' input').val(sourceValue);
      // @TODO add label for activate
    });
  }
  catch(err2) {
    alert(Drupal.t('ListMixer Error: Inclusion & input validation problem. Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
  }
  // ********* Set up Submit button
  var Submit = new Drupal.behaviors.listmixer.submitBehavior();
  Submit.init();
  var submitFunction = preset.behaviors.submit.settings.behavior_function;
  preset.submit = Submit.markup[submitFunction];
  // Add button to form/containter
  // Only add interactive elements if a valid value is present.
  if(preset.activation === true) {
    $('form#' + preset.targetFormId).append(preset.submit);
  }
  else{
    // @TODO test that remove works
    $('form#' + preset.targetFormId).find('div.listmixer-push-submit').remove();
  }

  // ********* Find the button (which might not be a button) and add a click function to it.

  // Set up data object on page load.
  preset.data = {
    'inputArray' : [],
    'input' : '',
    'target_id' : preset.targetId ,
    'target_field' : preset.targetField,
    'interact_function' : preset.interactFunction
    // @TODO Collect other data here if necessary
  };
  // Activate push callback
  $('form#' + preset.targetFormId + ' div.listmixer-push-submit').children(".button").click(function() {
    Drupal.behaviors.listmixer.push(preset); 
    //@TODO make sure target_id is available to push function

    // If page stayed loaded, clear out the data array.
    preset.data = {
    'inputArray' : [],
    'input' : '',
    'target_id' : preset.targetId ,
    'target_field' : preset.targetField,
    'interact_function' : preset.interactFunction
    };
    // @TODO Change input val clearing.
    // $('form.listmixer-target-form div.listmixer-interact-input input').val('');

    // Do not reload page.
    // @TODO... actually the reloading can be nice.
    // return false;
  });
};