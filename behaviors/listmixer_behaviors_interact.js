Drupal.behaviors.listmixer.Interact = function() {
  this.init = function() {
    alert('Interact Library Loaded');
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
    alert('interact checkbox');
  }

}
