// $Id$
Drupal.behaviors.listmixer.activateBehavior = function(preset) {
  this.init = function() {
  }

  /* Library Functions */  
  this.buttonActivate = function(preset) {
    Drupal.behaviors.listmixer.addActivateButton(preset);
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
      buttonActivate : '<div class="listmixer-' + preset.targetFormId + '-activate-button listmixer-activate-button"><button class="button"><div class="listmixer-' + preset.targetFormId + '-activate-label listmixer-activate-label">Activate</div></button></div><div class="listmixer-' + preset.targetFormId + '-deactivate-button listmixer-deactivate-button"><button class="button"><div class="listmixer-' + preset.targetFormId + '-deactivate-label listmixer-deactivate-label">Deactivate</div></button></div>',
      selectActivate : '',
      selectPlusButtonActivate : ''
    }
  };
}

/**
 * Add selectable capabilities to target id
 */
Drupal.behaviors.listmixer.selectable = function(preset) {
  if(preset.activation === false) {
    $(preset.interactions.interactions_target_id).attr("id", "selectable-" + preset.targetFormId);
    $(preset.interactions.interactions_target_id).addClass("selectable");
    	$(function() {
        	$(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).selectable({ 
           // filter : preset.interactions.interactions_target_id_element,
            selected: function(event, ui) { 
            // @TODO This could be buggy.
            // Seems like jQuery UI is picky about the target of the selection.
            // @TODO Test the different ways of useing the ui object to figure out the value of what was selected.
            // This will only support paths for the moment.
            //if (preset.interactions.interactions_target_id_attr === 'href' ) {
              if(ui.selected.pathname !== undefined) {
                preset.targetIdArray.push(ui.selected.pathname);
              }
              preset.activation = true;
              Drupal.behaviors.listmixer.listmixerActivate(preset);
              preset.activated = true;
              preset.deactivated = null;
              $(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).selectable('destroy');      
            //}
          }
        });
  		  $(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).disableSelection();
      }); 
  }
  else {
    $(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).selectable('destroy');
  }
}

Drupal.behaviors.listmixer.addActivateButton = function(preset) {
  // Add activate button to form.
console.log(preset);
  $('form#' + preset.targetFormId).append(preset.activateMarkup);
  // Hide deactivate button.
  $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-deactivate-button').hide();
  // On click activation button
  $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-activate-button').children(".button").click(function() { 
  if(preset.activated == null) {
      preset.activation = true;
      preset.activationComplete = false;
      Drupal.behaviors.listmixer.listmixerActivate(preset);
      preset.activated = true;
      preset.deactivated = null;
      $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-deactivate-button').show();
      $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-activate-button').hide();
    }
    return false;
  });
  // Set up deactivate button.
  $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-deactivate-button').children(".button").click(function() {
    if(preset.deactivated == null) {
      preset.activation = false;
      Drupal.behaviors.listmixer.listmixerDeactivate(preset);
      preset.deactivated = true;
      preset.activated = null;
      $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-deactivate-button').hide();
      $('form#' + preset.targetFormId + ' div.listmixer-' + preset.targetFormId + '-activate-button').show();
      return false;
    }
  });
  return false;
}

Drupal.behaviors.listmixer.selectPlusButtonActivate = function(preset) {
  if(preset.activation === false) {
    $(preset.interactions.interactions_target_id).attr("id", "selectable-" + preset.targetFormId);
    $(preset.interactions.interactions_target_id).addClass("selectable");
    	$(function() {
        	$(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).selectable({ 
            // filter : preset.interactions.interactions_target_id_element,
            selected: function(event, ui) {
            // Add activate button.
            Drupal.behaviors.listmixer.addActivateButton(preset);
          }
        });
  		  $(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).disableSelection();
      }); 
  }
  else {
    $(preset.interactions.interactions_target_id + "#selectable-" + preset.targetFormId).selectable('destroy');
  }
}