// $Id$
 /*
  // @TODO This should be theme function?
  
  Drupal.theme.prototype.Interact = function(preset) {
    return '<div class="listmixer-source-value"><div class="listmixer-source-label"><div class="listmixer-source-label"></div></div>"';
  }
 */

Drupal.behaviors.listmixer.Interact = function(preset) {
  this.init = function() {
  // alert('Interact Library Loaded');
  }

  /* Library Functions */ 
  // @TODO Can't figure out how to call these functions...didn't work as i expected it to
  this.selectInteract = function() {
    alert(Drupal.t('interact select'));
  }
   
  this.inputInteract = function() {
    alert(Drupal.t('interact input'));
  }
  
  this.clickInteract = function() {
    alert(Drupal.t('interact click'));
  }

  this.checkboxInteract = function() {
    alert(Drupal.t('interact click'));
  }

  this.weightInteract = function(preset, element) {
    // Find the souce value weight selectors, apply an initial value to them all -10 0 10 style
    // for initial testing, just type in the weight
    // figure out the interaction (based on table drag)
    // let people scramble the order as much as they want
    // and then save it on pushing, so need another function that will read the weights
    // MAYBE weight should have its own js file
   // alert(Drupal.t('interact weight'));

    // Get index number for this element.
    // @TODO really this isn't the right index - we want the index for the source id...since it will be some sort of list.
    var weight = $('*').index($(element));
    $(element).find('div.listmixer-source-weight').html(weight);
  
    Drupal.behaviors.listmixer.weightDrag(preset);
  }


  // @TODO This could connect with jQuery UI library, or even jQuery selectors. Might need more markup though.
  // @TODO 'Click' will be more like a default, and target whatever the container is.
  this.markup = { 
    clickInteract : '<div class="listmixer-source-value"><div class="listmixer-source-label"><div class="listmixer-source-label"></div></div>',
    selectInteract : '<div class="listmixer-source-value"><input type="select" class="listmixer-source-value"></input><div class="listmixer-source-label"></div></div>',
    inputInteract : '<div class="listmixer-source-value"><input type="input" class="listmixer-source-value"></input><div class="listmixer-source-label"></div></div>',
    checkboxInteract : '<div class="listmixer-source-value"><input type="checkbox" class="listmixer-source-value"></input><div class="listmixer-source-label"></div></div>',
    weightInteract : '<div class="listmixer-source-value"><input type="input" class="listmixer-source-value"></input><div class="listmixer-source-weight">WEIGHT HERE</div><div class="listmixer-source-label"></div></div>'
  };
  // @TODO Weight will change to some sort of controls, and it will take the source value and resave it in a certain order, so it's an extended input field.
  this.validation = { 
    clickInteract : 'input.listmixer-source-value', // @TODO Won't work yet
    selectInteract : 'input.listmixer-source-value:selected',
    inputInteract : 'input.listmixer-source-value', // @TODO How to see if it's empty?
    checkboxInteract : 'input.listmixer-source-value:checked',
    weightInteract : 'input.listmixer-source-value:checked'
  };

}

// Add weight dragging capabilities to each weighted item on a page (jQuery UI)
Drupal.behaviors.listmixer.weightDrag = function(preset) {
  $(preset.interactions.interactions_restrictions).addClass('sortable');
  	$(function() {
    	$(".sortable").sortable({ items: preset.interactions_inclusions, axis: 'y' });
		  $(".sortable").disableSelection();
  });
}

