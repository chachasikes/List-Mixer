// $Id$

Drupal.behaviors.listmixer.submitBehavior = function(preset) {
  this.init = function() {
  }

  /* Library Functions */ 
  
  this.buttonSubmit = function() {  
    if(preset.administerSettings === true) {
      alert(Drupal.t('submit button'));
    }
  }
   
  this.checkboxSubmit = function() {
    if(preset.administerSettings === true) {
      alert(Drupal.t('submit checkbox'));
    }
  }
  this.markup = function(preset) {
    return { 
      // @TODO checkboxSubmit not quite figured out yet.
      // checkboxSubmit : '<div class="listmixer-' + preset.containerId + 'push-submit"><button class="button">Save</button></div>',
      buttonSubmit : '<div class="listmixer-' + preset.containerId + '-push-submit listmixer-push-submit"><button class="button">Save</button></div>'
    }
  };
}
