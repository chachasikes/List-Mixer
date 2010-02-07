// $Id$
Drupal.behaviors.listmixer.activateBehavior = function(preset) {
  this.init = function() {
  }

  /* Library Functions */  
  this.buttonActivate = function(preset) {
    Drupal.behaviors.listmixer.addActivateButton(preset);
   // Set deactivate on initial load.
   $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-deactivate-button').children(".button").trigger('click');

    return false;
  }
  
  this.selectActivate = function(preset) {
    Drupal.behaviors.listmixer.selectable(preset);
    return false;
  }
    
  this.selectPlusButtonActivate = function(preset) {
    Drupal.behaviors.listmixer.selectPlusButtonActivate(preset);
    return false;
  }

  this.dragActivate = function(preset) {
  }
  
  this.loadActivate = function(preset) {
  }

  this.markup = function(preset) {
    return { 
      loadActivate : '',
      buttonActivate : '<div class="' + preset.interactiveElementContainerId + '-activate-button listmixer-activate-button"><button class="button"><div class="' + preset.interactiveElementContainerId + '-activate-label listmixer-activate-label">Activate</div></button></div><div class="' + preset.interactiveElementContainerId + '-deactivate-button listmixer-deactivate-button"><button class="button"><div class="' + preset.interactiveElementContainerId + '-deactivate-label listmixer-deactivate-label">Deactivate</div></button></div>',
      selectActivate : '',
      dragActivate : '',
      selectPlusButtonActivate : ''
    }
  };
}

/**
 * Add selectable capabilities to target id
 */
Drupal.behaviors.listmixer.selectable = function(preset) {
  if(preset.activation === false) {
    $(preset.interactions.interactions_target_id).attr("id", "selectable-" + preset.containerId);
    $(preset.interactions.interactions_target_id).addClass("selectable");
    	$(function() {
        	$(preset.interactions.interactions_target_id + "#selectable-" + preset.containerId).selectable({ 
            // Filter the selection with the target id element.
            filter : preset.interactions.interactions_target_id_element,
            // On select, set the target id array, and activate the interaction.
            selected: function(event, ui) { 
              if(ui.selected.pathname !== undefined) {
                preset.targetIdArray.push(ui.selected.pathname);
              }
              preset.activation = true;
              Drupal.behaviors.listmixer.activate(preset);
              preset.activated = true;
              preset.deactivated = null;
              $(preset.interactions.interactions_target_id + "#selectable-" + preset.interactiveElementContainerId).selectable('destroy');      
          }
        });
  		  $(preset.interactions.interactions_target_id + "#selectable-" + preset.interactiveElementContainerId).disableSelection();
      }); 
  }
  else {
    $(preset.interactions.interactions_target_id + "#selectable-" + preset.interactiveElementContainerId).selectable('destroy');
  }
}

Drupal.behaviors.listmixer.addActivateButton = function(preset) {
  // Add activate button to form.
  $('form#' + preset.interactiveElementContainerId).append(preset.activateMarkup);
  // Hide deactivate button.
  $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-deactivate-button').hide();
  // On click activation button
  $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-activate-button').children(".button").click(function() { 
  if(preset.activated == null) {
      preset.activation = true;
      preset.activationComplete = false;
      Drupal.behaviors.listmixer.activate(preset);
      preset.activated = true;
      preset.deactivated = null;
      $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-deactivate-button').show();
      $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-activate-button').hide();
    }
    return false;
  });
  // Set up deactivate button.
  $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-deactivate-button').children(".button").click(function() {
    if(preset.deactivated == null) {
      preset.activation = false;
      Drupal.behaviors.listmixer.listmixerDeactivate(preset);
      preset.deactivated = true;
      preset.activated = null;
      $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-deactivate-button').hide();
      $('form#' + preset.interactiveElementContainerId + ' div.' + preset.interactiveElementContainerId + '-activate-button').show();
      return false;
    }
  });
  return false;
}

Drupal.behaviors.listmixer.selectPlusButtonActivate = function(preset) {
  if(preset.activation === false) {
    $(preset.interactions.interactions_target_id).attr("id", "selectable-" + preset.interactiveElementContainerId);
    $(preset.interactions.interactions_target_id).addClass("selectable");
    	$(function() {
        	$(preset.interactions.interactions_target_id + "#selectable-" + preset.interactiveElementContainerId).selectable({ 
            // filter : preset.interactions.interactions_target_id_element,
            selected: function(event, ui) {
            // Add activate button.
            Drupal.behaviors.listmixer.addActivateButton(preset);
          }
        });
  		  $(preset.interactions.interactions_target_id + "#selectable-" + preset.interactiveElementContainerId).disableSelection();
      }); 
  }
  else {
    $(preset.interactions.interactions_target_id + "#selectable-" + preset.interactiveElementContainerId).selectable('destroy');
  }
}