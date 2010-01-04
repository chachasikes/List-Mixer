// $Id$

Drupal.behaviors.listmixer.Submit = function() {
  this.init = function() {
   // alert('Submit Library Loaded');
  }

  /* Library Functions */ 
  
  this.buttonSubmit = function() {
    alert('submit button');
  }
   
  this.checkboxSubmit = function() {
    alert('submit checkbox');
  }
  this.markup = { 
    // @TODO checkboxSubmit not quite figured out yet.
    checkboxSubmit : '<div class="listmixer-push-submit"><button class="button">Save</button></div>',
    buttonSubmit : '<div class="listmixer-push-submit"><button class="button">Save</button></div>',
  };
}
