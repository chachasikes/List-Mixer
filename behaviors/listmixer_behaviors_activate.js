// $Id$
Drupal.behaviors.listmixer.Activate = function() {
  this.init = function() {
   // alert('Activate Library Loaded');
  }

  /* Library Functions */  
  this.buttonActivate = function() {
    alert('activate button');
  }
  
  this.dragActivate = function() {
    alert('activate drag');
  }
  
  this.mousedownActivate = function() {
    alert('activate mousedown');
  }

}
