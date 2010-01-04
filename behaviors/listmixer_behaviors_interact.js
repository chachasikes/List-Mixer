// $Id$

Drupal.behaviors.listmixer.Interact = function() {
  this.init = function() {
  //alert('Interact Library Loaded');
  }

  /* Library Functions */ 
  
  this.selectInteract = function() {
    alert('interact select');
  }
   
  this.inputInteract = function() {
    alert('interact input');
  }
  
  this.clickInteract = function() {
    alert('interact click');
  }

  this.checkboxInteract = function() {
    alert('interact click');
  }
  // @TODO This could connect with jQuery UI library, or even jQuery selectors. Might need more markup though.
  // @TODO 'Click' will be more like a default, and target whatever the container is.
  this.markup = { 
    clickInteract : '<div class="listmixer-source-value"><div class="listmixer-source-label"><div class="listmixer-source-label">add</div></div>',
    selectInteract : '<div class="listmixer-source-value"><input type="select" class="listmixer-source-value"></input><div class="listmixer-source-label">add</div></div>',
    inputInteract : '<div class="listmixer-source-value"><input type="input" class="listmixer-source-value"></input><div class="listmixer-source-label">add</div></div>',
    checkboxInteract : '<div class="listmixer-source-value"><input type="checkbox" class="listmixer-source-value"></input><div class="listmixer-source-label">add</div></div>',
  };

}
