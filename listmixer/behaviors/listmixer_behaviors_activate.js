// $Id$
Drupal.behaviors.listmixer.activateBehavior = function(preset) {
  this.init = function() {
   // alert('Activate Library Loaded');
  }

  /* Library Functions */  
  this.buttonActivate = function() {
    alert(Drupal.t('activate button'));
  }
  
  this.selectActivate = function(preset) {
    Drupal.behaviors.listmixer.selectable(preset);
    // alert(Drupal.t('activate select'));
  }
    
  this.dragActivate = function() {
    alert(Drupal.t('activate drag'));
  }
  
  this.loadActivate = function() {
    alert(Drupal.t('Activate Load'));
  }
  this.markup = { 
    loadActivate : '',
    buttonActivate : '<div class="listmixer-activate-button"><button class="button"><div class="listmixer-activate-label">Activate</div></button></div><div class="listmixer-deactivate-button"><button class="button"><div class="listmixer-deactivate-label">Deactivate</div></button></div>',
    selectActivate : '',
  };
}

/**
 * Add selectable capabilities to target id
 */
Drupal.behaviors.listmixer.selectable = function(preset) {
  if(preset.activation === false) {
    $(preset.interactions.interactions_target_id).attr("id", "selectable");
    	$(function() {
        	$(preset.interactions.interactions_target_id + "#selectable").selectable({ 
            filter : preset.interactions.interactions_target_id_attr,
            selected: function(event, ui) { 
            // @TODO test the different ways of useing the ui object to figure out the value of what was selected.
            // This will only support paths for the moment.
            if (preset.interactions.interactions_target_id_attr === 'href' ) {
              preset.targetId.push(ui.selected.pathname);
            }
            // @TODO concatenates all the paths/nids of the target nids to a string.
            // @TODO then make all the push methods 
          }
        });
  		  $(preset.interactions.interactions_target_id + "#selectable").disableSelection();
      }); 
  }
  else {
    $(preset.interactions.interactions_target_id + "#selectable").selectable('destroy');
  }
}