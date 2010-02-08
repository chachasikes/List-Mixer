// $Id$

/**
 * @file
 * This Javascript file is responsible for creatings and applying interactive
 * preset behaviors and elements to the appropriate html elements on a rendered
 * Drupal page.
 *
 * How it works:
 * *_Presets are loaded from an array passed from the Drupal page,
 * in Drupal.settings.listmixer.
 *
 * *_The interaction is set up, and awaits activation from the user.
 * *_Upon activation
 */


var pageLoaded = 0;

Drupal.behaviors.listmixer = function() {
  if (pageLoaded === 0) {
    $.each(Drupal.settings.listmixer, function() {
      if (this.preset_method == 'listmixer_storage_default') {
        var preset = this;
        var interactionsContainerExists = $.find(this.interactions.interactions_container);
        if (interactionsContainerExists !== '') {
          Drupal.behaviors.listmixer.setup(preset);
        }
      }
      return false;
    });
  }
  pageLoaded++;
};
Drupal.behaviors.listmixer.setup = function(preset) {
  // Set up Interactive container.
  Drupal.behaviors.listmixer.setupContainer(preset);

  // Set up form in container.
  Drupal.behaviors.listmixer.setupContainerForm(preset);

  // Load target values.
  Drupal.behaviors.listmixer.activateLoadTarget(preset);

  // Set up functions and markup for activation.
  Drupal.behaviors.listmixer.setupActivate(preset);
};
Drupal.behaviors.listmixer.setupContainer = function(preset) {
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
  preset.containerId = 'listmixer-main-container-' + preset.preset_name;
  preset.container = preset.interactions.interactions_container;
};
Drupal.behaviors.listmixer.setupContainerForm = function(preset) {
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
  $(preset.containerFormSelector).prepend('<div class="' + preset.interactiveElementContainerSelector + '-interaction-label listmixer-interaction-label">' + preset.interactions.interactions_label + '</div>');

  // Add help text.
  // @TODO: Wrap help text in Drupal.t()? Will be plain markup? CSS is allowed...so see which function is appropriate.
  $(preset.containerFormSelector).append('<div class="' + preset.interactiveElementContainerSelector + '-interaction-help  listmixer-interaction-help">' + preset.interactions.interactions_help + '</div>');
};
Drupal.behaviors.listmixer.setupActivate = function(preset) {
  // Make deactivated by default.
  preset.activation = false;
  preset.activateFunction = preset.behaviors.activate.settings.behavior_function;
  preset.ActivateBehavior = new Drupal.behaviors.listmixer.activateBehavior(preset);
  // Load markup.
  preset.activateMarkupArray = preset.ActivateBehavior.markup(preset);
  preset.activateMarkup = preset.activateMarkupArray[preset.activateFunction];

  // Load activate function.
  preset.ActivateBehavior[preset.activateFunction](preset);
};
Drupal.behaviors.listmixer.activateLoadTarget = function(preset) {
  // Set up target field (for node save function.)
  preset.targetField = preset.interactions.interactions_target_field;
  // Set up the target value
  preset.targetValueAttribute = preset.interactions.interactions_target_id_attr;
  preset.presetIsActive = false;
  preset.targetId = '';
  preset.targetIdArray = [];

  var targetValue;
  if(preset.interactions.interactions_target_id_element !== '') {
    // For multiple targets, do nothing.
    // The value must be determined in the activate function.
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
};
Drupal.behaviors.listmixer.deactivate = function(preset) {
  // Set activated/deactivated state.
  preset.activation = false;
  // Only allow 1 activation.
  preset.presetIsActive = false;
  Drupal.behaviors.listmixer.activate(preset);
};
Drupal.behaviors.listmixer.activate = function(preset) {
  // Load interaction region.
  Drupal.behaviors.listmixer.activateLoadInteractionRegion(preset);

  // ********* Assign source value to each included interaction element.
  Drupal.behaviors.listmixer.setupInteract(preset);

  Drupal.behaviors.listmixer.setupInteractionForm(preset);

};
Drupal.behaviors.listmixer.activateLoadInteractionRegion = function(preset) {
  if (preset.interactions.interactions_region === undefined) {
    preset.interactions.interactions_region = 'body';
  }
  preset.interactionsRegion = $(preset.interactions.interactions_region).html();
};
/**
 * For each interactive region, set up the interact elements and buttons.
 *
 * This function does the bulk work of this module. 
 *
 * It looks over each interactive region, these could be single or multiple depending
 * on how the user has configured selectors (to be general, or specific.)
 * 
 * What happens:
 * The interact behaviors are loaded.
 * Source values are found.
 * Markup is created for an individual container form that is attached to the interactive region.
 * 
 *
 */
Drupal.behaviors.listmixer.setupInteract = function(preset) {
  // Process each interactive element.
  $.each($(preset.interactions.interactions_region + ' ' + preset.interactions.interactions_inclusions), function () {
    // Set up the source values to be used with the interactive elements.
    preset.interactFunction = preset.behaviors.interact.settings.behavior_function;
    preset.Interact = new Drupal.behaviors.listmixer.interactBehavior();

    preset.sourceValueSelector = preset.interactions.interactions_source_id;
    preset.sourceValueAttribute = preset.interactions.interactions_source_id_attr;

/*  // @TODO Rarrr. Will ids be set sometimes? Needs research.
    if($(this).attr("id") !== null) {
      preset.currentSelectionId = $(this).attr("id");
    }
    else {
     preset.currentSelectionId = "listmixer-interaction";
    }
*/
    preset.currentSelectionId = "listmixer-interaction";
    preset.interactiveElementContainerId = 'listmixer-container-'+ preset.preset_name + '-' + preset.currentSelectionId;
    preset.interactiveElementContainerFormClass = 'class="' + preset.interactiveElementContainerId + '-' + preset.currentSelectionId + '-form listmixer-selected-container-form"';
    preset.interactiveElementContainerFormSelector = 'form#' +  preset.interactiveElementContainerId;
    preset.interactiveElementContainerForm = '<form id="' + preset.interactiveElementContainerId + '" ' + preset.interactiveElementContainerFormClass + '></form>';
 
   // @TODO Connect to listmixer settings.
    var hideSourceValue = true;
    var sourceValue = null;
    var sourceElement = null;
    var sourceValueMarkup = 'div.' + preset.interactiveElementContainerId + '-source-value';
    var sourceValueMarkupProcessed = '' + preset.interactiveElementContainerId + '-processed-value-' + preset.preset_name;
    // @TODO check sourceValue is numeric
    // The selector might be empty if user enters nothing, if so, just use the default input.

    // If no sourceValueSelector has been set, it means that 
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
      // Each preset can only have one active region at a time, to reduce conflicts.
      if(preset.presetIsActive === false) {
        preset.interactMarkupArray = preset.Interact.markup(preset);
        preset.interactMarkup = preset.interactMarkupArray[preset.interactFunction];
        preset.interactValidationArray = preset.Interact.validation(preset);
        preset.interactValidation = preset.interactValidationArray[preset.interactFunction];
  
        preset.Interact[preset.interactFunction](preset);
        preset.presetIsActive = true;
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
        $(this).append(preset.interactMarkup);
        // Rebuild activate markup.
        preset.activateMarkupArray = preset.ActivateBehavior.markup(preset);
        preset.activateMarkup = preset.activateMarkupArray[preset.activateFunction];
        // Add a form to this interaction element.
      //  $(this).append(preset.interactiveElementContainerForm); 
        // Load activate function and add markup.
        preset.ActivateBehavior[preset.activateFunction](preset);
        $(preset.interactiveElementContainerFormSelector).append(preset.activateMarkup);
      }
      else{
        $(this).removeClass(sourceValueMarkupProcessed);
        $(this).find(sourceValueMarkup).remove();
        $(preset.interactiveElementContainerFormSelector).remove(); // @TODO Test remove feature.
        // @TODO Shouldn't have to remove any specially added buttons anymore, cause they should be in the form. But need to test.
        /*         $(preset.interactiveElementContainerFormSelector).find('div.' + preset.interactiveElementContainerId + '-push-submit').remove(); */
      }
    }
    // Add value to input field after input is created
    $(this).find('*.' + sourceValueMarkupProcessed + ' input').val(sourceValue);
    // @TODO add label for activate
  });
};
/**
 * Add a form to the interaction.
 */
Drupal.behaviors.listmixer.setupInteractionForm = function(preset) {
  // Add activate, submit and the push behavior that is connected to submit.
  if(preset.presetIsActive === true) {    
    // Set up submit elements.
    $(preset.interactions.interactions_region + ' ' + preset.interactions.interactions_inclusions).append(preset.interactiveElementContainerForm);

    Drupal.behaviors.listmixer.setupSubmit(preset);
    $(preset.interactiveElementContainerFormSelector).append(preset.submitMarkup);

    // Set up push callback on submit feature.
    Drupal.behaviors.listmixer.setupPush(preset);
    preset.Submit[preset.submitFunction](preset);
  }
};

/**
 * Submit called when form is created and added to container.
 */
Drupal.behaviors.listmixer.setupSubmit = function(preset) {
  preset.submitFunction = preset.behaviors.submit.settings.behavior_function;
  preset.Submit = new Drupal.behaviors.listmixer.submitBehavior(preset);
  preset.submitMarkupArray = preset.Submit.markup(preset);
  preset.submitMarkup = preset.submitMarkupArray[preset.submitFunction];
};
Drupal.behaviors.listmixer.setupPush = function(preset) {
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
}
/**
 * Push is called when user interacts with submit button.
 */
Drupal.behaviors.listmixer.executePush = function(preset) {
  preset.Push = new Drupal.behaviors.listmixer.pushBehavior(preset);
  // Get value from interact element.
  $.each($(preset.interactions.interactions_region + ' ' + preset.interactValidation), function(){
    // Collect the value from each of the interactive elements.
    // Store values in data object in preset.
     preset.data.inputArray.push($(this).val());
    // Clear out the current value.
    // @TODO Test that this works with all input types.
    $(this).val('');
  });
  Drupal.behaviors.listmixer.buildBehaviorCallback(preset, 'push');
  // @TODO Check that the callback isn't reloading the page.

  // If page stayed loaded, clear out the data array.
  preset.data = {
  'inputArray' : [],
  'input' : '',
  'target_id' : preset.targetId,
  'target_field' : preset.targetField,
  'interact_function' : preset.interactFunction
  };
  return false;
};
Drupal.behaviors.listmixer.buildBehaviorCallback = function(preset, type) {
  var callback;
  var behaviorName;
  var behaviorFunction;
  // Create an array of the settings for the current behavior.
  var behavior = preset.behaviors[type];
  if (behavior.settings !== null) {
    callback = Drupal.settings.basePath + behavior.settings.behavior_callback;
    behaviorFunction = behavior.settings.behavior_function;
    behaviorName = behavior.settings.behavior_name;
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
/**
 * Do something on redirect (placeholder)
 */
Drupal.behaviors.listmixer.redirect = function(preset, data) {
};
Drupal.behaviors.listmixer.reloadPage = function() {
  location.reload(true);
};



/* Testing jQuery Link (local symlink) */
/*

jQuery.LINT.special[4].jQuery = jQuery.LINT.special[4].jQuery || [];
 
// Add check on error-reporting level one.
// Check jQuery method.
jQuery.LINT.special[1].jQuery.push(function(selector, context) {
 
    if (selector === '*') {
        return "Don't use the universal selector!";
    }
 
});
*/