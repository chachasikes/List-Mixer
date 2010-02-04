// $Id$

/**
 * @file
 */

var pageLoaded = 0;

Drupal.behaviors.listmixer = function() {
  if (pageLoaded === 0) {
    $.each(Drupal.settings.listmixer, function() {
      if (this.preset_method == 'listmixer_storage_default') {
        var preset = this;
        var interactionsContainerExists = $.find(this.interactions.interactions_container);
        if (interactionsContainerExists != '') {
          Drupal.behaviors.listmixer.listmixerSetup(preset);
        }
      }
      return false;
    });
  }
  pageLoaded++;
};


Drupal.behaviors.listmixer.listmixerSetup = function(preset) {


  // Set up Interactive container.
  Drupal.behaviors.listmixer.listmixerSetupContainer(preset);

  // Set up target values.
  Drupal.behaviors.listmixer.listmixerSetupTarget(preset);

  // Set up container form. 
  Drupal.behaviors.listmixer.listmixerSetupContainerForm(preset);
  
  // Load up functions and markup for activation.
  Drupal.behaviors.listmixer.activate(preset);

  // Set up activation.
  Drupal.behaviors.listmixer.setupActivateWidget(preset);  
}


Drupal.behaviors.listmixer.listmixerSetupContainer = function(preset) {
  if (preset.interactions.interactions_container === preset.interactions.interactions_region) {
    preset.containerSelector = preset.interactions.interactions_container;
    preset.interactiveElementContainerSelector = preset.interactions.interactions_container;
  }
  // There is some trickiness to how the form container is determined.
  // Currently, the form container is attached to the most external element, if it has the region.
  else{
    preset.containerSelector = preset.interactions.interactions_container + ':has(' + preset.interactions.interactions_region + ')';
    preset.interactiveElementContainerSelector = preset.interactions.interactions_inclusions + ':has(' + preset.interactions.interactions_region + ')';
  }
  // *********** Create interaction form and target classes
  preset.containerId = 'listmixer-main-container-'+ preset.preset_name;
  preset.container = preset.interactions.interactions_container;

};
Drupal.behaviors.listmixer.listmixerSetupTarget = function(preset) {
  // Set up target field (for node save function.)
  preset.targetField = preset.interactions.interactions_target_field;
  // Set up the target value
  preset.targetValueAttribute = preset.interactions.interactions_target_id_attr;
  preset.activationComplete = false;
  preset.targetId = '';
  preset.targetIdArray = [];
};
Drupal.behaviors.listmixer.listmixerSetupContainerForm = function(preset) {
  // Create variables pointing to the main container form for this preset.
  preset.containerFormClass = 'class="' + preset.containerId + '-form listmixer-container-form"';
  preset.containerFormSelector = 'form#' +  preset.containerId;
  preset.containerForm = '<form id="' + preset.containerId + '" ' + preset.containerFormClass + '></form>';
  preset.form = preset.containerForm;

  // Add the form to the interaction.
  $(preset.containerSelector).prepend(preset.form);

  // Add interaction label.
  // @TODO: Wrap label in Drupal.t()? Will be plain markup? CSS is allowed...so see which function is appropriate.
  // Also, users could be encouraged to wrap their text in Drupal.t() and assign it to the preset from a function.
  preset.interactionsLabel = preset.interactions.interactions_label;
  $(preset.containerFormSelector).prepend('<div class="' + preset.interactiveElementContainerId + '-interaction-label listmixer-interaction-label">' + preset.interactionsLabel + '</div>');

  // Add help text.
  // @TODO: Wrap help text in Drupal.t()? Will be plain markup? CSS is allowed...so see which function is appropriate.
  preset.interactionsHelp = preset.interactions.interactions_help;
  $(preset.containerFormSelector).prepend('<div class="' + preset.interactiveElementContainerId + '-interaction-help  listmixer-interaction-help">' + preset.interactionsHelp + '</div>');
};
Drupal.behaviors.listmixer.buildBehavior = function(preset, type) {
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

    if (callback !== null) {
      if (type == 'push') {
        if (preset.data.inputArray.length > 0) {
          preset.data.input = preset.data.inputArray.toString();
        }
        if (preset.targetIdArray.length > 0) {
          preset.targetId = preset.targetIdArray.toString();
          preset.data.target_id = preset.targetIdArray.toString();
        }
      }
      $.ajax({
        type: "POST",
        url: callback,
        data: preset.data,
        complete: Drupal.behaviors.listmixer.redirect(preset, preset.data)
      });
    }
  }
};
Drupal.behaviors.listmixer.activate = function(preset) {
  Drupal.behaviors.listmixer.buildBehavior(preset, 'activate');
  preset.ActivateBehavior = new Drupal.behaviors.listmixer.activateBehavior(preset);
  preset.activateFunction = preset.behaviors.activate.settings.behavior_function;
  preset.activateMarkupArray = preset.ActivateBehavior.markup(preset);
  preset.activateMarkup = preset.activateMarkupArray[preset.activateFunction];
};
Drupal.behaviors.listmixer.setupActivateWidget = function(preset) {
  // Make deactivated by default.
  preset.activation = false;
  preset.ActivateBehavior.init(preset);

  // @TODO Figure out how to trigger these functions automatically.
  if (preset.activateFunction == 'buttonActivate') {
    preset.ActivateBehavior.buttonActivate(preset);
  }
  else if (preset.activateFunction == 'loadActivate') {
    preset.ActivateBehavior.activation = true;
  }
  else if (preset.activateFunction == 'selectActivate') {
    preset.ActivateBehavior.selectActivate(preset);
  }
  else if (preset.activateFunction == 'selectPlusButtonActivate') {
    preset.ActivateBehavior.selectPlusButtonActivate(preset);
  }
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

  // @TODO on deactivate, remove or hide.
  // ********* Load target nid or path.
  try {
    // If an attribute has been set by user, get the value.
    var targetValue;
    if(preset.interactions.interactions_target_id_element !== '') {
      // For multiple targets
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
/*         $(preset.interactions.interactions_target_id).hide(); */
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
  
  // ********* Create the interactive region.
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
  }
  catch(err1) {
    // @TODO If this is set to body, are there any other chances that this would be empty? This check maybe unnecessary for anything except debugging this JS file.
    if(preset.administerSettings === true) {
      alert(Drupal.t('ListMixer Error: Interactive region not found. Did you enter the right CSS Selector for "' + preset.preset_name + '"? Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
    }
  }
  // ******** Activate interaction.
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

      preset.interactFunction = preset.behaviors.interact.settings.behavior_function;
      // @TODO See if there is any possible way to get this function to load.
      // Otherwise, maybe store the function in the php??
      if (preset.interactFunction == 'sortInteract') {
        Interact.sortInteract(preset);
      }
      // ********* Assign source value to each included interaction element.
      $.each($(preset.interactions.interactions_region + ' ' + preset.interactions.interactions_inclusions), function() {
  


        if($(this).attr("id") !== null) {
          preset.currentSelectionId = $(this).attr("id");
        }
        else {
          preset.currentSelectionId = "test";
        }

        preset.interactiveElementContainerId = 'listmixer-container-'+ preset.preset_name + '-' + preset.currentSelectionId;
        preset.interactiveElementContainerFormClass = 'class="' + preset.interactiveElementContainerId + '-' + preset.currentSelectionId + '-form listmixer-selected-container-form"';
        preset.interactiveElementContainerFormSelector = 'form#' +  preset.interactiveElementContainerId;
        preset.interactiveElementContainerForm = '<form id="' + preset.interactiveElementContainerId + '" ' + preset.interactiveElementContainerFormClass + '></form>';

       // Set up interact elements.
        Drupal.behaviors.listmixer.interact(preset);

        // Set up submit elements.
        Drupal.behaviors.listmixer.submit(preset);


        var sourceValue = null;
        var sourceElement = null;
        var Interact = new Drupal.behaviors.listmixer.interactBehavior();
        preset.interactFunction = preset.behaviors.interact.settings.behavior_function;
        preset.interactMarkupArray = Interact.markup(preset);
        preset.interactMarkup = preset.interactMarkupArray[preset.interactFunction];
        Interact.init();


        var sourceValueMarkup = 'div.' + preset.interactiveElementContainerId + '-source-value';
        var sourceValueMarkupProcessed = '' + preset.interactiveElementContainerId + '-processed-value-' + preset.preset_name;
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
            $(this).find(sourceValueMarkup).addClass(sourceValueMarkupProcessed);

            $(this).prepend(preset.interactiveElementContainerForm);
            $(this).append(preset.interactMarkup);
            $(this).append(preset.submitMarkup);
          }
          else{
            $(this).removeClass(sourceValueMarkupProcessed);
            $(this).find(sourceValueMarkup).remove();
            $(preset.interactiveElementContainerFormSelector).remove(); // @TODO Test remove feature.
            $(preset.interactiveElementContainerFormSelector).find('div.' + preset.interactiveElementContainerId + '-push-submit').remove();
          }

        }
        // Add value to input field after input is created
        $(this).find('*.' + sourceValueMarkupProcessed + ' input').val(sourceValue);
        // @TODO add label for activate
      });
    }
    catch(err2) {
      if(preset.administerSettings === true) {
        alert(Drupal.t('ListMixer Error: Inclusion & input validation problem  in preset ' + preset.preset_name + '. Edit preset: admin/build/listmixer/' + preset.preset_id + ''));
      }
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

    $('div.' + preset.interactiveElementContainerId + '-push-submit').children(".button").click(function() {

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
      // $('form.listmixer-container-form div.listmixer-interact-input input').val('');
  
      // Do not reload page.
      // @TODO... actually the reloading can be nice.
      // return false;
    });
  preset.activationComplete = true;
  }
  else {
  }
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
    console.log(preset);
/*     return false; */
  });
  Drupal.behaviors.listmixer.behaviorBuildCallback(preset, 'push');
  // @TODO Check that the callback isn't reloading the page. 
/*   return false; */
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
/*   return false; */
};
/**
 * Do something on redirect (placeholder)
 */
Drupal.behaviors.listmixer.redirect = function(preset, data) { 
  alert("test");
  console.log(preset);
  return false;
};
