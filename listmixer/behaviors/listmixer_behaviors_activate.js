// $Id$
Drupal.behaviors.listmixer.activateBehavior = function(preset) {
  this.init = function() {
   // alert('Activate Library Loaded');
  }

  /* Library Functions */  
  this.buttonActivate = function() {
    alert(Drupal.t('activate button'));
  }
  
  this.dragActivate = function() {
    alert(Drupal.t('activate drag'));
  }
  
  this.loadActivate = function() {
    alert(Drupal.t('Activate Load'));
  }
  this.markup = { 
    // @TODO checkboxSubmit not quite figured out yet.
    // checkboxActivate : '<div class="listmixer-activate-button"><input type="checkbox" class="listmixer-activate-button"></input><div class="listmixer-activate-label">Activate</div></div>',
    buttonActivate : '<div class="listmixer-activate-button"><button class="button"><div class="listmixer-activate-label">Activate</div></button></div><div class="listmixer-deactivate-button"><button class="button"><div class="listmixer-deactivate-label">Deactivate</div></button></div>',
    loadActivate : ''
  };
}

