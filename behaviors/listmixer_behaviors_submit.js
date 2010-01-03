// $Id$

Drupal.behaviors.listmixer.Submit = function() {
  this.init = function() {
   // alert('Submit Library Loaded');
  }

  /* Library Functions */ 
  
  this.buttonSubmit= function() {
    alert('submit button');
  }
   
  this.checkboxSubmit= function() {
    alert('submit checkbox');
  }

}
