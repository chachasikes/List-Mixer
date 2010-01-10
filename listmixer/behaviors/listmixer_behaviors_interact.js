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
  // @TODO This could connect with jQuery UI library, or even jQuery selectors. Might need more markup though.
  // @TODO 'Click' will be more like a default, and target whatever the container is.
  this.markup = { 
    clickInteract : '<div class="listmixer-source-value"><div class="listmixer-source-label"><div class="listmixer-source-label"></div></div>',
    selectInteract : '<div class="listmixer-source-value"><input type="select" class="listmixer-source-value"></input><div class="listmixer-source-label"></div></div>',
    inputInteract : '<div class="listmixer-source-value"><input type="input" class="listmixer-source-value"></input><div class="listmixer-source-label"></div></div>',
    checkboxInteract : '<div class="listmixer-source-value"><input type="checkbox" class="listmixer-source-value"></input><div class="listmixer-source-label"></div></div>'
  };

  this.validation = { 
    clickInteract : 'input.listmixer-source-value', // @TODO Won't work yet
    selectInteract : 'input.listmixer-source-value:selected',
    inputInteract : 'input.listmixer-source-value', // @TODO How to see if it's empty?
    checkboxInteract : 'input.listmixer-source-value:checked'
  };

}
