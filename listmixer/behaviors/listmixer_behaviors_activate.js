// $Id$
Drupal.behaviors.listmixer.Activate = function() {
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
  
  this.mousedownActivate = function() {
    alert(Drupal.t('activate mousedown'));
  }

}
