// $Id$
Drupal.behaviors.listmixer.activateBehavior = function(preset) {
  this.init = function() {
  }

  /* Library Functions */  
  this.buttonActivate = function() {
  }
  
  this.selectActivate = function(preset) {
    Drupal.behaviors.listmixer.selectable(preset);
  }
    
  this.dragActivate = function() {
  }
  
  this.loadActivate = function() {
  }

  this.markup = function(preset) {
    return { 
      loadActivate : '',
      buttonActivate : '<div class="listmixer-' + preset.targetFormId + '-activate-button listmixer-activate-button"><button class="button"><div class="listmixer-' + preset.targetFormId + '-activate-label listmixer-activate-label">Activate</div></button></div><div class="listmixer-' + preset.targetFormId + '-deactivate-button listmixer-deactivate-button"><button class="button"><div class="listmixer-' + preset.targetFormId + '-deactivate-label listmixer-deactivate-label">Deactivate</div></button></div>',
      selectActivate : '',
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