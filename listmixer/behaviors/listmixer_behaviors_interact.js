// $Id$
 /*
  // @TODO This should be theme function?
  
  Drupal.theme.prototype.Interact = function(preset) {
    return '<div class="listmixer-source-value"><div class="listmixer-source-label"><div class="listmixer-source-label"></div></div>"';
  }
 */

Drupal.behaviors.listmixer.interactBehavior = function(preset) {
  this.init = function() {
  }

  /* Library Functions */ 
  // @TODO Can't figure out how to call these functions...didn't work as i expected it to
  this.selectInteract = function() {
  }
   
  this.inputInteract = function() {
  }
  
  this.clickInteract = function() {
  }

  this.checkboxInteract = function() {
  }

  this.sortInteract = function(preset) {
    // Find the souce value sort selectors, apply an initial value to them all -10 0 10 style
    // for initial testing, just type in the weight
    // figure out the interaction (based on table drag)
    // let people scramble the order as much as they want
    // and then save it on pushing, so need another function that will read the weights
    // MAYBE weight should have its own js file

    // Get index number for this element.
    // @TODO really this isn't the right index - we want the index for the source id...since it will be some sort of list.
    Drupal.behaviors.listmixer.sortInteract(preset);
  }
  // @TODO This could connect with jQuery UI library, or even jQuery selectors. Might need more markup though.
  // @TODO 'Click' will be more like a default, and target whatever the container is.
  this.markup = function(preset) {
    return { 
      clickInteract : '<div class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"><div class="listmixer-' 
          + preset.containerId + '-source-label listmixer-source-label"><div class="listmixer-' 
          + preset.containerId + '-source-label listmixer-source-label"></div></div>',

      selectInteract : '<div class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"><input type="select" class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"></input><div class="listmixer-'
          + preset.containerId + '-source-label listmixer-source-label"></div></div>',

      inputInteract : '<div class="listmixer-' + preset.containerId 
          + '-source-value listmixer-source-value"><input type="input" class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"></input><div class="listmixer-' 
          + preset.containerId + '-source-label  listmixer-source-label"></div></div>',
      checkboxInteract : '<div class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"><input type="checkbox" class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"></input><div class="listmixer-' 
          + preset.containerId + '-source-label listmixer-source-label"></div></div>',
      sortInteract : '<div class="listmixer-' + preset.containerId 
          + '-source-value listmixer-source-value"><div class="listmixer-' 
          + preset.containerId + '-source-sort-handle listmixer-source-sort-handle"></div><input type="hidden" class="listmixer-' 
          + preset.containerId + '-source-value listmixer-source-value"></input><div class="listmixer-' 
          + preset.containerId + '-source-label listmixer-source-label"></div></div>'
    }
  };
  // @TODO Weight will change to some sort of controls, and it will take the source value and resave it in a certain order, so it's an extended input field.
  this.validation = function(preset) { 
    return {
      clickInteract : 'input.listmixer-' + preset.containerId + '-source-value', // @TODO Won't work yet
      selectInteract : 'input.listmixer-' + preset.containerId + '-source-value:selected',
      inputInteract : 'input.listmixer-' + preset.containerId + '-source-value', // @TODO How to see if it's empty?
      checkboxInteract : 'input.listmixer-' + preset.containerId + '-source-value:checked',
      sortInteract : 'input.listmixer-' + preset.containerId + '-source-value'
    }
  };
}

/**
 * Add sort dragging capabilities to each weighted item on a page (jQuery UI)
 */
Drupal.behaviors.listmixer.sortInteract = function(preset) {
  try {
    if(preset.activation === true) {
      $(preset.interactions.interactions_region).attr("id", "sortable-" + preset.containerId);
      	$(function() {
        	$(preset.interactions.interactions_region + "#sortable-" + preset.containerId).sortable({ items: preset.interactions_inclusions, axis: 'y' });
    		  $(preset.interactions.interactions_region + "#sortable-" + preset.containerId).disableSelection();
      }); 
    }
    else {
      $(preset.interactions.interactions_region + "#sortable-" + preset.containerId).sortable('destroy');
      //$(preset.interactions.interactions_region).removeClass('sortable');
    }
  }
  catch(err3) {
    if(preset.administerSettings === true) {
      alert(Drupal.t("Could not add sort to" + preset.preset_name + "."));
    }  
  }
}

