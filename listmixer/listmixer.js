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
      // listmixer_storage_default is required even if preset is created
      // programatically. Leaving this in while I think about how that part 
      // will work.
      if (this.preset_method == 'listmixer_storage_default') {
        var preset = this;

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
          // *********** Set up behaviors.
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
  var Activate = new Drupal.behaviors.listmixer.activateBehavior(preset);
  preset.activateFunction = preset.behaviors.activate.settings.behavior_function;
  preset.activateMarkupArray = Activate.markup(preset);
  preset.activateMarkup = preset.activateMarkupArray[preset.activateFunction];
  Activate.init();
};
/**
 * Submit called when form is created and added to container.
 */
Drupal.behaviors.listmixer.submit = function(preset) {
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'submit');
  var Submit = new Drupal.behaviors.listmixer.submitBehavior(preset);
  preset.submitFunction = preset.behaviors.submit.settings.behavior_function;
  preset.submitMarkupArray = Submit.markup(preset);
  preset.submitMarkup = preset.submitMarkupArray[preset.submitFunction];
};
/**
 * Push is called when user interacts with submit button.
 */
Drupal.behaviors.listmixer.push = function(preset) {
  var Push = new Drupal.behaviors.listmixer.pushBehavior(preset);
  Push.init();
  // Load data for interact button validation.
  var Interact = new Drupal.behaviors.listmixer.interactBehavior(preset);
  preset.interactFunction = preset.behaviors.interact.settings.behavior_function;
  preset.interactMarkupArray = Interact.markup(preset);
  preset.interactMarkup = preset.interactMarkupArray[preset.interactFunction];
  preset.interactValidationArray = Interact.validation(preset);
  preset.interactValidation = preset.interactValidationArray[preset.interactFunction];
  Interact.init();

  // Get value from interact element.
  $.each($(preset.interactions.interactions_region + ' ' + preset.interactValidation), function(){
    // Collect the value from each of the interactive elements.
    // Store values in data object in preset.
    preset.data.inputArray.push($(this).val());
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
    callback = Drupal.settings.basePath + behavior.settings.behavior_callback;
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
        if (preset.targetIdArray.length > 0) {
          preset.targetId = preset.targetIdArray.toString();
          preset.data.target_id = preset.targetIdArray.toString();
        }

        // @TODO Temporarily making 'push' the only function that performs callback.
        // Adding to other behaviors will require some more advanced features.
        $.ajax({
          type: "POST",
          url: callback,
          data: preset.data,
          complete: Drupal.behaviors.listmixer.redirect(preset, preset.data)
        });
      }

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
    callback = Drupal.settings.basePath + behavior.settings.behavior_redirect;
    behaviorName =  behavior.settings.behavior_name;

    // Load data from settings array contained in each behavior.
    // @TODO a callback is called. a menu item figures out who the callback is for, looks up the registry and calls the appropriate function.
    // Grab data from somewhere that's stored somewhere else.
    // The data might need to be cleaned up if the funciton is used several times before submitting

    var data = {data_label : ''};
       
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
    preset.activationComplete = false;
    preset.targetId = '';
    preset.targetIdArray = [];

    // *********** Create interaction form and target classes
    preset.targetFormId = 'listmixer-target-'+ preset.preset_name;
    preset.targetFormClass = 'class="listmixer-' + preset.targetFormId + '-target-form listmixer-target-form"';
    // @TODO Should form be a 'wrap()' function?
    // @TODO Should this be available to Drupal theme? It's pretty important and shouldn't be messed with.
    preset.targetForm = '<form id="' + preset.targetFormId + '" ' + preset.targetFormClass + '></form>';
    preset.form = preset.targetForm;
    preset.container = preset.interactions.interactions_container;
    Drupal.behaviors.listmixer.submit(preset);
    Drupal.behaviors.listmixer.interact(preset);
    Drupal.behaviors.listmixer.activate(preset);
    try {
      // If an attribute has been set by user, get the value.
      var targetValue;
      if(preset.interactions.interactions_target_id_element !== '') {
        // @TODO fill in (what?)
      }
      else {
        if(preset.targetValueAttribute !== '') {
          $(preset.interactions.interactions_target_id).each( function() {
            targetValue = $(this).attr(preset.targetValueAttribute);
            if(targetValue !== undefined) {
              preset.targetIdArray.push(targetValue);
            }  
          });
        }
        else {
          $(preset.interactions.interactions_target_id).each( function() { 
            targetValue = $(this).html();
            if(targetValue !== undefined) {
              preset.targetIdArray.push(targetValue);
            }  
          });
          $(preset.interactions.interactions_target_id).hide();
        } 
      }
    }
    catch(err) {
      // @TODO If user has permissions to edit the preset, give them an error.
      if(preset.administerSettings === true) {
        alert(Drupal.t('ListMixer Interaction Preset Error: Target Value "' + preset.interactions.interactions_target_id + '" could not be found. Did you enter the right CSS Selector for "' + preset.preset_name + '"? Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      }
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
      if(preset.administerSettings === true) {
        alert(Drupal.t('ListMixer Error: Interactive region not found. Did you enter the right CSS Selector for "' + preset.preset_name + '"? Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      }
    }

    // Set up interactivity.
    // This is region here. If the user just wants a form field in block,
    // Then they need to set it to just the block. Default is 'body' so 
    // If nothing is entered, it will show up at the top of the page.
    // Only one form is allowed, if the form should be applied to the 
    // region container, but not the container if the container is a 
    // child of the region container.
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
      if(preset.administerSettings === true) {
        alert(Drupal.t('ListMixer Error: Interactive region and main container conflict in preset ' + preset.preset_name + '. Edit: admin/build/listmixer/' + preset.preset_id + ''));
      }
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
  $('form#' + preset.targetFormId).prepend('<div class="listmixer-' + preset.targetFormId + '-interaction-help  listmixer-interaction-help">' + preset.interactionsHelp + '</div>');
  $('form#' + preset.targetFormId).prepend('<div class="listmixer-' + preset.targetFormId + '-interaction-label listmixer-interaction-label">' + preset.interactionsLabel + '</div>');
};
/**
 * Add activate widget.
 */
Drupal.behaviors.listmixer.setupActivateWidget = function(preset) {
  // @TODO Work on declaring decactivated, can't use === operator as is
  // On activate widget click, set up the interaction.
  var Activate = new Drupal.behaviors.listmixer.activateBehavior(preset);
  Activate.init(preset);
  /*
     There are a few kinds of activation.
      * On load: assumes that a valid node id exists already,
       and does not need to be selected.
      * Select: provides a jQuery selectable interface, user must
        select which node will be the target
      * Button: after load or select have been executed,
        an activate/deactivate button will be applied to the current
        node.
      * Select Plus Button: make the page selectable, when an item
        is selected, apply an activate/deactivate button.
      * Other possible types of activations:
        ?? Can't think of any.
  */
  // @TODO Figure out how to trigger these functions automatically.
  if (preset.activateFunction == 'buttonActivate') {
    Activate.buttonActivate(preset);
  }
  else if (preset.activateFunction == 'selectActivate') {
    Activate.selectActivate(preset);
  }
  else if (preset.activateFunction == 'selectPlusButtonActivate') {
    Activate.selectPlusButtonActivate(preset);
  }
  // Set deactivate on initial load.
  $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-deactivate-button').children(".button").trigger('click');
};
/**
 * Deactivate function.
 */
Drupal.behaviors.listmixer.listmixerDeactivate = function(preset) {
  // Set activated/deactivated state.
  preset.activation = false;
  // Only allow 1 activation.
  preset.activationComplete = false;
  Drupal.behaviors.listmixer.listmixerActivate(preset);
};
/**
 *
 */
Drupal.behaviors.listmixer.listmixerActivate = function(preset) {
  // For only 1 activation per preset.
  // Otherwise, all activations/deactivations are handled individually.
  if(preset.activationComplete === false) {
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
        preset.interactFunction = preset.behaviors.interact.settings.behavior_function;
        preset.interactMarkupArray = Interact.markup(preset);
        preset.interactMarkup = preset.interactMarkupArray[preset.interactFunction];
        Interact.init();
        var sourceValueMarkup = 'div.listmixer-' + preset.targetFormId + '-source-value';
        var sourceValueMarkupProcessed = 'listmixer-' + preset.targetFormId + '-processed-value-' + preset.preset_name;
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
              $(this).prepend(preset.interactMarkup);

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
            $(this).prepend(preset.interactMarkup);
            $(this).find(sourceValueMarkup).addClass(sourceValueMarkupProcessed);
          }
          else{
            $(this).removeClass(sourceValueMarkupProcessed);
            $(this).find(sourceValueMarkup).remove();
          }
        }
        // Add value to input field after input is created
console.log("source values");
console.log(sourceValue);
console.log(sourceValueMarkupProcessed);
        $(this).find('*.' + sourceValueMarkupProcessed + ' input').val(sourceValue);
        // @TODO add label for activate
      });
    }
    catch(err2) {
      if(preset.administerSettings === true) {
        alert(Drupal.t('ListMixer Error: Inclusion & input validation problem  in preset ' + preset.preset_name + '. Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      }
    }

    // Add button to form/containter
    // Only add interactive elements if a valid value is present.
    if(preset.activation === true) {
      $('form#' + preset.targetFormId).append(preset.submitMarkup);
    }
    else{
      // @TODO test that remove works
      $('form#' + preset.targetFormId).find('div.listmixer-' + preset.targetFormId + '-push-submit').remove();
    }
  
    // ********* Find the button (which might not be a button) and add a click function to it.
    // Set up data object on page load.
    preset.data = {
      'inputArray' : [],
      'input' : '',
      'target_id' : preset.targetId,
      'target_field' : preset.targetField,
      'interact_function' : preset.interactFunction
      // @TODO Collect other data here if necessary
    };
    // Activate push callback. (For example, click a button.)
    $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-push-submit').children(".button").click(function() {
      Drupal.behaviors.listmixer.push(preset); 
      //@TODO make sure target_id is available to push function

      // If page stayed loaded, clear out the data array.
      preset.data = {
      'inputArray' : [],
      'input' : '',
      'target_id' : preset.targetId,
      'target_field' : preset.targetField,
      'interact_function' : preset.interactFunction
      };

      // @TODO Change input val clearing.
      // $('form.listmixer-target-form div.listmixer-interact-input input').val('');
  
      // Do not reload page.
      // @TODO... actually the reloading can be nice.
      // return false;
    });
  preset.activationComplete = true;
  }
  else {
  }
};